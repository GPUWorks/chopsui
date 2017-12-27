subdir('wayland')

lib_sui_host = static_library(
	'sui_host',
	files(
		'host.c',
		'window.c',
		# TODO: Configure windowing backends at build-time
		'wayland/host.c',
		'wayland/window.c',
		'wayland/registry.c',
	),
	include_directories: [
		sui_inc,
		include_directories([
			'../gfx', # TODO: non-ideal
			'wayland',
		])
	],
	dependencies: [sui_protos]
)
