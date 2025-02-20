/* generic-button.c
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

#include "generic-button.h"

G_DEFINE_TYPE (GenericButton, generic_button, GTK_TYPE_BUTTON);

GtkWidget *
generic_button_new (const gchar *label, const gchar *icon_name)
{
  GenericButton *button = g_object_new (GENERIC_BUTTON_TYPE, NULL);

  adw_button_content_set_label (ADW_BUTTON_CONTENT (button->content), label);

  adw_button_content_set_icon_name (ADW_BUTTON_CONTENT (button->content), icon_name);

  gtk_widget_add_css_class (GTK_WIDGET (button), "grey-button");

  return GTK_WIDGET (button);
}

static void
generic_button_init (GenericButton *self)
{
  gtk_button_set_has_frame (GTK_BUTTON (self), FALSE);

  self->content = adw_button_content_new ();
  gtk_button_set_child (GTK_BUTTON (self), GTK_WIDGET (self->content));

  gtk_widget_set_halign (GTK_WIDGET (self->content), 1);
  gtk_widget_set_margin_start (GTK_WIDGET (self->content), 5);

  gtk_widget_add_css_class (GTK_WIDGET (self), "custom-button");
}

static void
generic_button_class_init (GenericButtonClass *klass)
{
}

