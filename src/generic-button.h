/* generic-button.h
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

#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GENERIC_BUTTON_TYPE (generic_button_get_type ())

G_DECLARE_FINAL_TYPE (GenericButton, generic_button, GENERIC_BUTTON, GENERIC_BUTTON, GtkButton)

struct _GenericButton
{
  GtkButton parent_instance;
  GtkWidget *content;
};

GtkWidget *generic_button_new (const gchar *label, const gchar *icon_name);

G_END_DECLS

