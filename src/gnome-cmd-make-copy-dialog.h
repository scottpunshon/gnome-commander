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
#ifndef __GNOME_CMD_MAKE_COPY_DIALOG_H__
#define __GNOME_CMD_MAKE_COPY_DIALOG_H__

#include "gnome-cmd-file.h"

#define GNOME_CMD_MAKE_COPY_DIALOG(obj) \
	GTK_CHECK_CAST (obj, gnome_cmd_make_copy_dialog_get_type (), GnomeCmdMakeCopyDialog)
#define GNOME_CMD_MAKE_COPY_DIALOG_CLASS(klass) \
	GTK_CHECK_CLASS_CAST (klass, gnome_cmd_make_copy_dialog_get_type (), GnomeCmdMakeCopyDialogClass)
#define GNOME_CMD_IS_MAKE_COPY_DIALOG(obj) \
	GTK_CHECK_TYPE (obj, gnome_cmd_make_copy_dialog_get_type ())


typedef struct _GnomeCmdMakeCopyDialog GnomeCmdMakeCopyDialog;
typedef struct _GnomeCmdMakeCopyDialogPrivate GnomeCmdMakeCopyDialogPrivate;
typedef struct _GnomeCmdMakeCopyDialogClass GnomeCmdMakeCopyDialogClass;



struct _GnomeCmdMakeCopyDialog
{
	GnomeCmdStringDialog parent;
	GnomeCmdMakeCopyDialogPrivate *priv;
};


struct _GnomeCmdMakeCopyDialogClass
{
	GnomeCmdStringDialogClass parent_class;
};


GtkWidget*
gnome_cmd_make_copy_dialog_new (GnomeCmdFile *finfo, GnomeCmdDir *dir);

GtkType
gnome_cmd_make_copy_dialog_get_type (void);




#endif //__GNOME_CMD_MAKE_COPY_DIALOG_H__


