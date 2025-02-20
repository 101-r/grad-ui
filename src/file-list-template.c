/* file-list-template.c
 *
 * Copyright 2024 Ravshan Zaripov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "file-list-template.h"

G_DEFINE_TYPE (FileListTemplate, file_list_template, ADW_TYPE_NAVIGATION_PAGE);

static FileListTemplate *file_list_template_instance = NULL;

FileListTemplate *
file_list_template_new (void)
{
  return FILE_LIST_TEMPLATE (g_object_new (FILE_LIST_TYPE_TEMPLATE, NULL));
}

FileListTemplate *
get_file_list_template_instance (void)
{
  return file_list_template_instance;
}

void
update_file_list (FileListTemplate *self, GList *content)
{
  DirectoryInfo *dir_info;
  FileInfo *file_info;
  GtkWidget *child;
  GtkWidget *button;

  while ((child = gtk_widget_get_last_child (GTK_WIDGET (self->list))) != NULL)
    {
      gtk_box_remove (self->list, child);
    }

  for (GList *f = content; f != NULL; f = f->next)
    {
      if (IS_DIRECTORY_INFO (f->data))
        {
          dir_info = (DirectoryInfo *) f->data;
          button = generic_button_new (dir_info->name, "folder-symbolic");
          gtk_box_append (self->list, button);
        }
      if (IS_FILE_INFO (f->data))
        {
          file_info = (FileInfo *) f->data;
          button = generic_button_new (file_info->name, "text-x-generic-symbolic");
          gtk_box_append (self->list, button);
        }
    }

  free_directory_content (content);
}

static void
file_list_template_dispose (GObject *object)
{
  FileListTemplate *self = (FileListTemplate *) object;

  gtk_widget_dispose_template (GTK_WIDGET (self), FILE_LIST_TYPE_TEMPLATE);

  G_OBJECT_CLASS (file_list_template_parent_class)->dispose (object);
}

static void
file_list_template_finalize (GObject *object)
{
  FileListTemplate *self = (FileListTemplate *) object;

  g_clear_pointer (&self->list, g_free);

  G_OBJECT_CLASS (file_list_template_parent_class)->finalize (object);
}

static void
file_list_template_constructed (GObject *object)
{
  FileListTemplate *self = FILE_LIST_TEMPLATE (object);

  file_list_template_instance = self;

  update_file_list (self, get_directory_content ("/home/fedora-r"));

  G_OBJECT_CLASS (file_list_template_parent_class)->constructed (object);
}

static void
file_list_template_init (FileListTemplate *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_widget_set_name (GTK_WIDGET (self), "FileListTemplate");
}

static void
file_list_template_class_init (FileListTemplateClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_layout_manager_type (widget_class, GTK_TYPE_BIN_LAYOUT);

  object_class->dispose = file_list_template_dispose;
  object_class->finalize = file_list_template_finalize;
  object_class->constructed = file_list_template_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/com/github/com/file-list-template.ui");
  gtk_widget_class_bind_template_child (widget_class, FileListTemplate, list);
}

