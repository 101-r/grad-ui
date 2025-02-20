grad_ui_dev_sources = [
  'main.c',
  'grad-ui-dev-application.c',
  'grad-ui-dev-window.c',
  'file-list-template.c',
  'sidebar-template.c',
  'search-template.c',
  'generic-button.c',
  'utils/directory-content.c',
  'utils/utils.c',
]

grad_ui_dev_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

grad_ui_dev_sources += gnome.compile_resources('grad-ui-dev-resources',
  'grad-ui-dev.gresource.xml',
  c_name: 'grad_ui_dev'
)

executable('grad-ui-dev', grad_ui_dev_sources,
  dependencies: grad_ui_dev_deps,
       install: true,
)
