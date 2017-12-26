lib_sui_window = static_library(
	'sui_window',
	files(
		'window.c',
		# TODO: Configure windowing backends at build-time
		'wayland/window.c',
		'wayland/registry.c',
	),
	include_directories: [
		sui_inc,
		include_directories(['wayland/'])
	]
)
