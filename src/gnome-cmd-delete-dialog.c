/*
    GNOME Commander - A GNOME based file manager 
    Copyright (C) 2001-2005 Marcus Bjurman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/ 
#include <config.h>
#include "gnome-cmd-includes.h"
#include "gnome-cmd-data.h"
#include "gnome-cmd-dir.h"
#include "gnome-cmd-delete-dialog.h"
#include "gnome-cmd-file-list.h"
#include "gnome-cmd-main-win.h"
#include "utils.h"

typedef struct {
	GtkWidget *progbar;
	GtkWidget *proglabel;
	GtkWidget *progwin;

	// Signals to the main thread that the work thread is waiting for an answer on what to do
	gboolean problem;

	// where the answer is delivered
	gint problem_action;

	// the filename of the file that cant be deleted
	gchar *problem_file;

	// the cause that the file cant be deleted
	GnomeVFSResult vfs_status;

	// the work thread
	GThread *thread;

	// the files that should be deleted
	GList *files;

	// tells the work thread to stop working
	gboolean stop;

	// tells the main thread that the work thread is done
	gboolean delete_done;

	// a message descriping the current status of the delete operation
	gchar *msg;

	// a float values between 0 and 1 representing the progress of the whole operation
	gfloat progress;

	// used to sync the main and worker thread
	GMutex *mutex;
} DeleteData;


static void
cleanup (DeleteData *data)
{
	gnome_cmd_file_list_free (data->files);
	g_free (data);
}


static gint
delete_progress_callback (GnomeVFSXferProgressInfo *info, DeleteData *data)
{
	gint ret = 0;
	
	g_mutex_lock (data->mutex);	
	
	if (info->status == GNOME_VFS_XFER_PROGRESS_STATUS_VFSERROR) {
		data->vfs_status = info->vfs_status;
		data->problem_file = info->source_name;
		data->problem = TRUE;
		
		g_mutex_unlock (data->mutex);
		while (data->problem_action == -1)
			g_thread_yield ();
		g_mutex_lock (data->mutex);	
		ret = data->problem_action;
		data->problem_action = -1;
		data->problem_file = NULL;
		data->vfs_status = GNOME_VFS_OK;
	}
	else if (info->status == GNOME_VFS_XFER_PROGRESS_STATUS_OK) {
		if (info->file_index >= 0 && info->files_total > 0) {
			gfloat f = (gfloat)info->file_index/(gfloat)info->files_total;
			if (data->msg) g_free (data->msg);
			data->msg = g_strdup_printf ("[%ld of %ld] Files deleted",
										 info->file_index, info->files_total);
			if (f < 0.001f) f = 0.001f;
			if (f > 0.999f) f = 0.999f;
			data->progress = f;
		}
		
		ret = !data->stop;
	}
	else {
		data->vfs_status = info->vfs_status;
	}
	
	g_mutex_unlock (data->mutex);
	
	return ret;
}


static void
on_cancel (GtkButton *btn, DeleteData *data)
{
	data->stop = TRUE;
	gtk_widget_set_sensitive (GTK_WIDGET (data->progwin), FALSE);
}

static gboolean
on_progwin_destroy (GtkWidget *win, DeleteData *data)
{
	data->stop = TRUE;
	return FALSE;
}


static void
create_delete_progress_win (DeleteData *data)
{
	GtkWidget *vbox;
	GtkWidget *bbox;
	GtkWidget *button;
	
	data->progwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (data->progwin), _("Deleting..."));
	gtk_window_set_policy (GTK_WINDOW (data->progwin), FALSE, FALSE, FALSE);
	gtk_widget_set_usize (GTK_WIDGET (data->progwin), 300, -1);
	gtk_signal_connect (
		GTK_OBJECT (data->progwin), "destroy-event",
		(GtkSignalFunc)on_progwin_destroy, data);

	vbox = create_vbox (data->progwin, FALSE, 6);
	gtk_container_add (GTK_CONTAINER (data->progwin), vbox);
	gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);

	data->proglabel = create_label (data->progwin, "");
	gtk_container_add (GTK_CONTAINER (vbox), data->proglabel);
	
	data->progbar = create_progress_bar (data->progwin);
	gtk_container_add (GTK_CONTAINER (vbox), data->progbar);

	bbox = create_hbuttonbox (data->progwin);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);

	button = create_stock_button_with_data (
		data->progwin, GNOME_STOCK_BUTTON_CANCEL, GTK_SIGNAL_FUNC (on_cancel), data);
	GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
	gtk_container_add (GTK_CONTAINER (bbox), button);

	gtk_widget_ref (data->progwin);
	gtk_widget_show (data->progwin);
}


static void
perform_delete_operation (DeleteData *data)
{
	int i;
	GnomeVFSResult result;
	GList *uri_list = NULL;
	GnomeVFSXferOptions xferOptions = GNOME_VFS_XFER_DEFAULT;
	GnomeVFSXferErrorMode xferErrorMode = GNOME_VFS_XFER_ERROR_MODE_QUERY;
	gint num_files = g_list_length (data->files);

	/* Go through all files and add the uri of the appropriate ones to a list */
	for ( i=0 ; i<num_files; i++ ) {
		GnomeVFSURI *uri;		
		GnomeCmdFile *finfo = (GnomeCmdFile*)g_list_nth_data (data->files, i);

		if (g_strcasecmp(finfo->info->name, "..") == 0
			|| g_strcasecmp(finfo->info->name, ".") == 0) continue;
		
		uri = gnome_cmd_file_get_uri (finfo);
		if (!uri) continue;
		
		gnome_vfs_uri_ref (uri);
		uri_list = g_list_append (uri_list, uri);
	}

	if (uri_list != NULL) {
		result = gnome_vfs_xfer_delete_list (
			uri_list,
			xferErrorMode,
			xferOptions,
			(GnomeVFSXferProgressCallback)delete_progress_callback,
			data);

		g_list_foreach (uri_list, (GFunc)gnome_vfs_uri_unref, NULL);
		g_list_free (uri_list);
	}

	data->delete_done = TRUE;
}


static gboolean
update_delete_status_widgets (DeleteData *data)
{
	g_mutex_lock (data->mutex);
	
	gtk_label_set_text (GTK_LABEL (data->proglabel), data->msg);
	gtk_progress_set_percentage (GTK_PROGRESS (data->progbar), data->progress);
			
	if (data->problem) {
		const gchar *error = gnome_vfs_result_to_string (data->vfs_status);
		gchar *msg = g_strdup_printf (
			_("Error while deleting %s\n\n%s"),
			data->problem_file, error);
		data->problem_action = run_simple_dialog (
			GTK_WIDGET (main_win), TRUE, GTK_MESSAGE_ERROR, msg, _("Delete problem"),
			_("Abort"), _("Retry"), _("Skip"), NULL);
		g_free (msg);
		
		data->problem = FALSE;
	}

	g_mutex_unlock (data->mutex);

	
	if (data->delete_done) {
		if (data->vfs_status != GNOME_VFS_OK)
			create_error_dialog (gnome_vfs_result_to_string (data->vfs_status));

		if (data->files) {
			GList *tmp = data->files;
			while (tmp) {
				GnomeCmdFile *finfo = GNOME_CMD_FILE (tmp->data);
				GnomeVFSURI *uri = gnome_cmd_file_get_uri (finfo);
				if (!gnome_vfs_uri_exists (uri))
					gnome_cmd_file_is_deleted (finfo);
				tmp = tmp->next;
			}
		}
		
		gtk_widget_destroy (data->progwin);

		cleanup (data);
		
		/* Returning FALSE here stops the timeout callbacks */
		return FALSE;		
	}

	return TRUE;
}


static void
do_delete (DeleteData *data)
{
	data->mutex = g_mutex_new ();
	data->delete_done = FALSE;
	data->vfs_status = GNOME_VFS_OK;
	data->problem_action = -1;
	create_delete_progress_win (data);
		
	data->thread = g_thread_create ((GThreadFunc)perform_delete_operation, data, FALSE, NULL);
	gtk_timeout_add (gnome_cmd_data_get_gui_update_rate (),
					 (GtkFunction)update_delete_status_widgets,
					 data);
}


void
gnome_cmd_delete_dialog_show (GList *files)
{
	DeleteData *data;
	GnomeCmdFile *finfo;
	gint ret, num_files;
	gchar *msg;

	data = g_new (DeleteData, 1);
	data->files = gnome_cmd_file_list_copy (files);
	data->stop = FALSE;
	data->problem = FALSE;
	data->delete_done = FALSE;
	data->mutex = NULL;
	data->msg = NULL;
	
	num_files = g_list_length (data->files);

	if (num_files == 1) {
		gchar *fname;
		finfo = (GnomeCmdFile*)g_list_nth_data (data->files, 0);
		if (g_strcasecmp(finfo->info->name, "..") == 0) {
			g_free (data);
			return;
		}
		fname = get_utf8 (finfo->info->name);
		msg = g_strdup_printf (_("Do you want to delete \"%s\"?"), fname);
		g_free (fname);
	}
	else
		msg = g_strdup_printf (
			ngettext("Do you want to delete the selected file?",
					 "Do you want to delete the %d selected files?",
					 num_files),
			num_files);

	if (gnome_cmd_data_get_confirm_delete ())
		ret = run_simple_dialog (
			GTK_WIDGET (main_win), FALSE,
			GTK_MESSAGE_QUESTION, msg, _("Delete"), _("Cancel"), _("OK"), NULL);
	else
		ret = 1;

	if (ret == 1)
		do_delete (data);
	
	g_free (msg);
}
