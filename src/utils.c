#include "utils.h"

#include <glib.h>
#include <gtk/gtk.h>

GList *
list_directory_contents (const char *path)
{
  GDir *dir;
  const char *filename;
  GList *file_list = NULL;

  g_print ("Attempting to open directory: %s\n", path);

  // Open the directory
  dir = g_dir_open (path, 0, NULL);
  if (dir == NULL)
    {
      g_print ("Failed to open directory: %s\n", path);
      return NULL;
    }

  // Loop through the directory entries and add them to the list
  while ((filename = g_dir_read_name (dir)) != NULL)
    {
      file_list = g_list_append (file_list, g_strdup (filename)); // Duplicate the filename
    }

  // Close the directory when done
  g_dir_close (dir);

  return file_list;
}

