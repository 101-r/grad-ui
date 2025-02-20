/* file-list-template.h
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

#include "generic-button.h"
#include "utils/directory-content.h"

G_BEGIN_DECLS

#define FILE_LIST_TYPE_TEMPLATE (file_list_template_get_type ())

G_DECLARE_FINAL_TYPE (FileListTemplate, file_list_template, FILE_LIST, TEMPLATE, AdwNavigationPage)

struct _FileListTemplate
{
  AdwNavigationPage parent_instance;
  GtkBox *list;
};

FileListTemplate *file_list_template_new (void);
FileListTemplate *get_file_list_template_instance (void);
void update_file_list (FileListTemplate *self, GList *content);

G_END_DECLS

