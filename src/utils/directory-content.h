/* directory-content.h
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

#include <gtk/gtk.h>

#define IS_DIRECTORY_INFO(data) (((DirectoryInfo *) (data))->type == DIRECTORY_TYPE)
#define IS_FILE_INFO(data) (((FileInfo *) (data))->type == FILE_TYPE)

typedef enum
{
  DIRECTORY_TYPE,
  FILE_TYPE,
} FileType;

typedef struct
{
  FileType type;
  gchar *path;
  gchar *previous;
  gchar *name;
} DirectoryInfo;

typedef struct
{
  FileType type;
  gchar *path;
  gchar *name;
  gboolean executable;
} FileInfo;

GList *get_directory_content (const gchar *path);
void free_directory_content (GList *content);

