glgen = find_program('../glgen.sh')

glapi = custom_target('glapi',
	input: 'glapi.txt',
	output: ['@BASENAME@.c', '@BASENAME@.h'],
	command: [glgen, '@INPUT@', '@OUTPUT0@', '@OUTPUT1@'],
)

lib_sui_gfx = static_library(
	'sui_gfx',
	files(
		'egl.c',
		'render_node.c',
	),
	glapi[0],
	glapi[1],
	include_directories: sui_inc,
	dependencies: [glesv2, egl]
)

sui_gfx = declare_dependency(
	link_with: lib_sui_gfx,
	sources: glapi[1],
)
