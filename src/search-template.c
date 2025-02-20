/* search-template.c
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

#include "search-template.h"

G_DEFINE_TYPE (SearchTemplate, search_template, ADW_TYPE_DIALOG);

SearchTemplate *
search_template_new (void)
{
  return g_object_new (SEARCH_TYPE_TEMPLATE, NULL);
}

static void
search_template_dispose (GObject *object)
{
  SearchTemplate *self = (SearchTemplate *) object;

  gtk_widget_dispose_template (GTK_WIDGET (self), SEARCH_TYPE_TEMPLATE);

  G_OBJECT_CLASS (search_template_parent_class)->dispose (object);
}

static void
search_template_finalize (GObject *object)
{
  SearchTemplate *self = (SearchTemplate *) object;

  g_clear_pointer (&self->search_entry, g_free);
  g_clear_pointer (&self->list, g_free);

  G_OBJECT_CLASS (search_template_parent_class)->finalize (object);
}

static void
search_template_constructed (GObject *object)
{
  // SearchTemplate *self = SEARCH_TEMPLATE (object);

  G_OBJECT_CLASS (search_template_parent_class)->constructed (object);
}

static void
search_template_init (SearchTemplate *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_widget_set_name (GTK_WIDGET (self), "SearchTemplate");
}

static void
search_template_class_init (SearchTemplateClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_layout_manager_type (widget_class, GTK_TYPE_BIN_LAYOUT);

  object_class->dispose = search_template_dispose;
  object_class->finalize = search_template_finalize;
  object_class->constructed = search_template_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/com/github/com/search-template.ui");
  gtk_widget_class_bind_template_child (widget_class, SearchTemplate, search_entry);
  gtk_widget_class_bind_template_child (widget_class, SearchTemplate, list);
}

