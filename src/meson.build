grad_sources = [
  'main.c',
  'grad-application.c',
  'grad-window.c',
]

grad_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

grad_sources += gnome.compile_resources('grad-resources',
  'grad.gresource.xml',
  c_name: 'grad'
)

executable('grad', grad_sources,
  dependencies: grad_deps,
       install: true,
)
