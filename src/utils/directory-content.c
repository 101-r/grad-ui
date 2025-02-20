/* directory-content.c
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

#include <dirent.h>
#include <sys/stat.h>

#include "directory-content.h"

static DirectoryInfo *
create_directory_info (const gchar *path, const gchar *previous, const gchar *name)
{
  DirectoryInfo *dir_info = g_new0 (DirectoryInfo, 1);
  dir_info->type = DIRECTORY_TYPE;
  dir_info->path = g_strdup (path);
  dir_info->previous = g_strdup (previous);
  dir_info->name = g_strdup (name);
  return dir_info;
}

static FileInfo *
create_file_info (const gchar *path, const gchar *name, gboolean executable)
{
  FileInfo *file_info = g_new0 (FileInfo, 1);
  file_info->type = FILE_TYPE;
  file_info->path = g_strdup (path);
  file_info->name = g_strdup (name);
  file_info->executable = executable;
  return file_info;
}

static void
free_directory_info (DirectoryInfo *dir_info)
{
  g_free (dir_info->path);
  g_free (dir_info->previous);
  g_free (dir_info->name);
  g_free (dir_info);
}

static void
free_file_info (FileInfo *file_info)
{
  g_free (file_info->path);
  g_free (file_info->name);
  g_free (file_info);
}

void
free_directory_content (GList *content)
{
  for (GList *f = content; f != NULL; f = f->next)
    {
      if (IS_DIRECTORY_INFO (f->data))
        {
          free_directory_info ((DirectoryInfo *) f->data);
        }
      if (IS_FILE_INFO (f->data))
        {
          free_file_info ((FileInfo *) f->data);
        }
    }
  g_list_free (content);
}

GList *
get_directory_content (const gchar *path)
{
  DIR *dir;
  struct dirent *entry;
  struct stat info;
  GList *list = NULL;
  gchar *full_path;

  dir = opendir (path);
  if (!dir)
    {
      perror ("opendir");
      return NULL;
    }

  while ((entry = readdir (dir)) != NULL)
    {
      // Skip the special directories "." and ".."
      if (strcmp (entry->d_name, ".") == 0 || strcmp (entry->d_name, "..") == 0)
        {
          continue;
        }

      // Build the full path for the current entry
      full_path = g_build_filename (path, entry->d_name, NULL);

      if (stat (full_path, &info) == -1)
        {
          perror ("stat");
          g_free (full_path);
          continue;
        }

      // Check if the entry is a directory
      if (S_ISDIR (info.st_mode))
        {
          DirectoryInfo *dir_info = create_directory_info (full_path, path, entry->d_name);
          list = g_list_append (list, dir_info);
        }
      // Check if the entry is a regular file
      else if (S_ISREG (info.st_mode))
        {
          gboolean executable = (info.st_mode & S_IXUSR) != 0;
          FileInfo *file_info = create_file_info (full_path, entry->d_name, executable);
          list = g_list_append (list, file_info);
        }

      g_free (full_path);
    }

  closedir (dir);

  return list;
}

