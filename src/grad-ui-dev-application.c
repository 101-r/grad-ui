/* grad-ui-dev-application.c
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
#include <glib/gi18n.h>

#include "grad-ui-dev-application.h"
#include "grad-ui-dev-window.h"

struct _GradUiDevApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (GradUiDevApplication, grad_ui_dev_application, ADW_TYPE_APPLICATION);

GradUiDevApplication *
grad_ui_dev_application_new (const char *application_id,
                             GApplicationFlags flags)
{
  g_return_val_if_fail (application_id != NULL, NULL);

  return g_object_new (GRAD_UI_DEV_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);
}

static void
grad_ui_dev_application_activate (GApplication *app)
{
  GtkWindow *window;

  g_assert (GRAD_UI_DEV_IS_APPLICATION (app));

  window = gtk_application_get_active_window (GTK_APPLICATION (app));

  if (window == NULL)
    window = g_object_new (GRAD_UI_DEV_TYPE_WINDOW,
                           "application", app,
                           NULL);

  gtk_window_present (window);
}

static void
grad_ui_dev_application_startup (GApplication *app)
{
  GtkCssProvider *css_provider;

  G_APPLICATION_CLASS (grad_ui_dev_application_parent_class)->startup (app);

  css_provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_resource (css_provider, "/com/github/com/style.css");

  gtk_style_context_add_provider_for_display (
      gdk_display_get_default (),
      GTK_STYLE_PROVIDER (css_provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  g_object_unref (css_provider);
}

static void
grad_ui_dev_application_class_init (GradUiDevApplicationClass *klass)
{
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  app_class->activate = grad_ui_dev_application_activate;
  app_class->startup = grad_ui_dev_application_startup;
}

static void
grad_ui_dev_application_about_action (GSimpleAction *action,
                                      GVariant *parameter,
                                      gpointer user_data)
{
  static const char *developers[] = { "Ravshan Zaripov", NULL };
  GradUiDevApplication *self = user_data;
  GtkWindow *window = NULL;

  g_assert (GRAD_UI_DEV_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  adw_show_about_dialog (GTK_WIDGET (window),
                         "application-name", "grad-ui-dev",
                         "application-icon", "com.github.com",
                         "developer-name", "Ravshan Zaripov",
                         "translator-credits", _ ("translator-credits"),
                         "version", "0.1.0",
                         "developers", developers,
                         "copyright", "© 2024 Ravshan Zaripov",
                         NULL);
}

static void
grad_ui_dev_application_quit_action (GSimpleAction *action,
                                     GVariant *parameter,
                                     gpointer user_data)
{
  GradUiDevApplication *self = user_data;

  g_assert (GRAD_UI_DEV_IS_APPLICATION (self));

  g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
  { "quit", grad_ui_dev_application_quit_action },
  { "about", grad_ui_dev_application_about_action },
};

static void
grad_ui_dev_application_init (GradUiDevApplication *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   app_actions,
                                   G_N_ELEMENTS (app_actions),
                                   self);
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "app.quit",
                                         (const char *[]){ "<primary>q", NULL });
}

