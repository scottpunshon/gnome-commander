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
#ifndef __GNOME_CMD_CMDLINE_H__
#define __GNOME_CMD_CMDLINE_H__


#define GNOME_CMD_CMDLINE(obj) \
	GTK_CHECK_CAST (obj, gnome_cmd_cmdline_get_type (), GnomeCmdCmdline)
#define GNOME_CMD_CMDLINE_CLASS(klass) \
	GTK_CHECK_CLASS_CAST (klass, gnome_cmd_cmdline_get_type (), GnomeCmdCmdlineClass)
#define GNOME_CMD_IS_CMDLINE(obj) \
	GTK_CHECK_TYPE (obj, gnome_cmd_cmdline_get_type ())


typedef struct _GnomeCmdCmdline GnomeCmdCmdline;
typedef struct _GnomeCmdCmdlinePrivate GnomeCmdCmdlinePrivate;
typedef struct _GnomeCmdCmdlineClass GnomeCmdCmdlineClass;



struct _GnomeCmdCmdline
{
	GtkHBox parent;
	GnomeCmdCmdlinePrivate *priv;
};


struct _GnomeCmdCmdlineClass
{
	GtkHBoxClass parent_class;
};


GtkWidget*
gnome_cmd_cmdline_new         (void);

GtkType
gnome_cmd_cmdline_get_type    (void);

void
gnome_cmd_cmdline_set_dir     (GnomeCmdCmdline *cmdline, const gchar *cwd);

void
gnome_cmd_cmdline_append_text (GnomeCmdCmdline *cmdline, const gchar *text);

void
gnome_cmd_cmdline_insert_text (GnomeCmdCmdline *cmdline, const gchar *text);

void
gnome_cmd_cmdline_set_text    (GnomeCmdCmdline *cmdline, const gchar *text);

gboolean
gnome_cmd_cmdline_is_empty    (GnomeCmdCmdline *cmdline);

void
gnome_cmd_cmdline_exec        (GnomeCmdCmdline *cmdline);

void
gnome_cmd_cmdline_focus       (GnomeCmdCmdline *cmdline);

void
gnome_cmd_cmdline_update_style (GnomeCmdCmdline *cmdline);

void
gnome_cmd_cmdline_show_history (GnomeCmdCmdline *cmdline);

GList *
gnome_cmd_cmdline_get_history  (GnomeCmdCmdline *cmdline);

void
gnome_cmd_cmdline_set_history  (GnomeCmdCmdline *cmdline, GList *history);

GtkWidget *
gnome_cmd_cmdline_get_entry    (GnomeCmdCmdline *cmdline);

gboolean
gnome_cmd_cmdline_keypressed   (GnomeCmdCmdline *cmdline,
								GdkEventKey *event);

#endif //__GNOME_CMD_CMDLINE_H__
