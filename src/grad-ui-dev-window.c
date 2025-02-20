/* grad-ui-dev-window.c
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
#include "grad-ui-dev-window.h"

G_DEFINE_TYPE (GradUiDevWindow, grad_ui_dev_window, ADW_TYPE_APPLICATION_WINDOW);

static void
grad_ui_dev_window_class_dispose (GObject *object)
{
  GradUiDevWindow *self = (GradUiDevWindow *) object;

  gtk_widget_dispose_template (GTK_WIDGET (self), GRAD_UI_DEV_TYPE_WINDOW);

  G_OBJECT_CLASS (grad_ui_dev_window_parent_class)->dispose (object);
}

static void
grad_ui_dev_window_finalize (GObject *object)
{
  GradUiDevWindow *self = (GradUiDevWindow *) object;

  g_clear_pointer (&self->file_list, g_free);
  g_clear_pointer (&self->sidebar, g_free);

  G_OBJECT_CLASS (grad_ui_dev_window_parent_class)->finalize (object);
}

static void
grad_ui_dev_window_constructed (GObject *object)
{
  // GradUiDevWindow *self = GRAD_UI_DEV_WINDOW (object);

  G_OBJECT_CLASS (grad_ui_dev_window_parent_class)->constructed (object);
}

static void
grad_ui_dev_window_init (GradUiDevWindow *self)
{
  g_type_ensure (FILE_LIST_TYPE_TEMPLATE);
  g_type_ensure (SIDEBAR_TYPE_TEMPLATE);

  gtk_widget_init_template (GTK_WIDGET (self));
}

static void
grad_ui_dev_window_class_init (GradUiDevWindowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = grad_ui_dev_window_class_dispose;
  object_class->finalize = grad_ui_dev_window_finalize;
  object_class->constructed = grad_ui_dev_window_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/com/github/com/grad-ui-dev-window.ui");
  gtk_widget_class_bind_template_child (widget_class, GradUiDevWindow, file_list);
  gtk_widget_class_bind_template_child (widget_class, GradUiDevWindow, sidebar);
}

