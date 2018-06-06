project(
	'chopsui',
	'c',
	license: 'MIT',
	default_options: [
		'c_std=c11',
		'warning_level=2',
		'werror=true',
	],
)

add_project_arguments('-Wno-unused-parameter', language: 'c')
add_project_arguments(
	'-DSUI_SRC_DIR="@0@"'.format(meson.source_root()),
	language: 'c'
)
add_project_arguments(
	'-I@0@'.format(meson.build_root()),
	language: 'c',
)

cc = meson.get_compiler('c')
# Clang complains about some zeroed initialiser lists (= {0}), even though they
# are valid
if cc.get_id() == 'clang'
	add_project_arguments('-Wno-missing-field-initializers', language: 'c')
	add_project_arguments('-Wno-missing-braces', language: 'c')
endif

sui_inc = include_directories('include')

egl = dependency('egl')
glesv2 = dependency('glesv2')
koio = dependency('koio')
# TODO: Wayland stuff should be optional
xkbcommon = dependency('xkbcommon')
wayland_client = dependency('wayland-client')
wayland_egl = dependency('wayland-egl')
wayland_protos = dependency('wayland-protocols')

sui_deps = [
	egl,
	glesv2,
	koio,
	xkbcommon,
	wayland_client,
	wayland_egl,
	wayland_protos
]

subdir('css')
subdir('gfx')
subdir('host')
subdir('node')
subdir('parser')
subdir('sui')
subdir('type')
subdir('util')

sui_libs = [
	lib_sui_css,
	lib_sui_gfx,
	lib_sui_host,
	lib_sui_node,
	lib_sui_parser,
	lib_sui_sui,
	lib_sui_type,
	lib_sui_util,
]

lib_chopsui = library(
	'chopsui',
	link_whole: sui_libs,
	dependencies: [wayland_client],
	include_directories: sui_inc,
	install: true,
)

chopsui = declare_dependency(
	link_with: lib_chopsui,
	dependencies: sui_deps,
	include_directories: sui_inc,
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
	libraries: lib_chopsui,
	version: '0.0.1',
	filebase: 'chopsui',
	name: 'chopsui',
	description: 'chopsui UI toolkit',
)

subdir('test')
subdir('demos')
