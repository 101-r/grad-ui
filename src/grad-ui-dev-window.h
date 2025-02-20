/* grad-ui-dev-window.h
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

#include "file-list-template.h"
#include "sidebar-template.h"

G_BEGIN_DECLS

#define GRAD_UI_DEV_TYPE_WINDOW (grad_ui_dev_window_get_type ())

G_DECLARE_FINAL_TYPE (GradUiDevWindow, grad_ui_dev_window, GRAD_UI_DEV, WINDOW, AdwApplicationWindow)

struct _GradUiDevWindow
{
  AdwApplicationWindow parent_instance;
  FileListTemplate *file_list;
  SidebarTemplate *sidebar;
};

G_END_DECLS

