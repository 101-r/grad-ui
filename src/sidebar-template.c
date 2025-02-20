/* sidebar-template.c
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

#include "sidebar-template.h"

G_DEFINE_TYPE (SidebarTemplate, sidebar_template, ADW_TYPE_NAVIGATION_PAGE);

SidebarTemplate *
sidebar_template_new (void)
{
  return SIDEBAR_TEMPLATE (g_object_new (SIDEBAR_TYPE_TEMPLATE, NULL));
}

static void
sidebar_add_button (SidebarTemplate *self, const gchar *label, const gchar *icon_name)
{
  GtkWidget *button = generic_button_new (label, icon_name);

  // g_signal_connect (button, "clicked", G_CALLBACK (on_button_clicked), self);

  gtk_box_append (self->list, button);
}

static void
on_search_button_clicked (GtkButton *button, gpointer user_data)
{
  SidebarTemplate *self = SIDEBAR_TEMPLATE (user_data);

  adw_dialog_present (ADW_DIALOG (self->search_template), GTK_WIDGET (self));
}

static void
sidebar_template_dispose (GObject *object)
{
  SidebarTemplate *self = (SidebarTemplate *) object;

  g_clear_object (&self->search_template);

  gtk_widget_dispose_template (GTK_WIDGET (self), SIDEBAR_TYPE_TEMPLATE);

  G_OBJECT_CLASS (sidebar_template_parent_class)->dispose (object);
}

static void
sidebar_template_finalize (GObject *object)
{
  SidebarTemplate *self = (SidebarTemplate *) object;

  g_clear_pointer (&self->search, g_free);
  g_clear_pointer (&self->list, g_free);

  G_OBJECT_CLASS (sidebar_template_parent_class)->finalize (object);
}

static void
sidebar_template_constructed (GObject *object)
{
  SidebarTemplate *self = SIDEBAR_TEMPLATE (object);

  /* Default sidebar buttons */
  sidebar_add_button (self, "Home", "user-home-symbolic");
  sidebar_add_button (self, "Documents", "folder-documents-symbolic");
  sidebar_add_button (self, "Downloads", "folder-download-symbolic");
  sidebar_add_button (self, "Videos", "folder-videos-symbolic");
  sidebar_add_button (self, "Music", "folder-music-symbolic");
  sidebar_add_button (self, "Pictures", "folder-pictures-symbolic");

  g_signal_connect (self->search, "clicked", G_CALLBACK (on_search_button_clicked), self);

  G_OBJECT_CLASS (sidebar_template_parent_class)->constructed (object);
}

static void
sidebar_template_init (SidebarTemplate *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->search_template = search_template_new ();
  self->file_list_ref = get_file_list_template_instance ();

  // Increase the reference count to ensure the instance is not disposed prematurely
  g_object_ref (self->search_template);

  gtk_widget_set_name (GTK_WIDGET (self), "SidebarTemplate");
}

static void
sidebar_template_class_init (SidebarTemplateClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_layout_manager_type (widget_class, GTK_TYPE_BIN_LAYOUT);

  object_class->dispose = sidebar_template_dispose;
  object_class->finalize = sidebar_template_finalize;
  object_class->constructed = sidebar_template_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/com/github/com/sidebar-template.ui");
  gtk_widget_class_bind_template_child (widget_class, SidebarTemplate, search);
  gtk_widget_class_bind_template_child (widget_class, SidebarTemplate, list);
}

