/* grad-window.c
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

#include "config.h"

#include "file-list-template.h"
#include "grad-window.h"

struct _GradWindow
{
  AdwApplicationWindow parent_instance;

  /* Template widgets */
  AdwToolbarView *content;
  GtkButton *home_button;

  FileListTemplate *file_list_template;
};

G_DEFINE_FINAL_TYPE (GradWindow, grad_window, ADW_TYPE_APPLICATION_WINDOW)

static void
grad_window_class_init (GradWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/com/github/grad/grad-window.ui");
  gtk_widget_class_bind_template_child (widget_class, GradWindow, content);
  gtk_widget_class_bind_template_child (widget_class, GradWindow, home_button);
}

static void
grad_window_init (GradWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_widget_realize (GTK_WIDGET (self->content));
  gtk_widget_realize (GTK_WIDGET (self->home_button));

  self->file_list_template = file_list_template_new ();

  adw_toolbar_view_set_content (self->content, GTK_WIDGET (self->file_list_template));

  FileButtonData *data = g_new (FileButtonData, 1);
  data->template = self->file_list_template;
  data->full_path = (gchar *) "/home/fedora-r";

  g_signal_connect (self->home_button, "clicked", G_CALLBACK (on_file_button_clicked), data);
}

