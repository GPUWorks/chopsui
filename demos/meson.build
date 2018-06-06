koio_tool = find_program('koio', required: true)

basic_bundle = custom_target('basic_bundle.c',
	build_by_default: true,
	input: [
		'basic/style.css',
		'basic/window.sui'
	],
	output: 'basic_bundle.c',
	command: [
		koio_tool,
		'-o', '@OUTPUT@',
		'@INPUT0@://style.css',
		'@INPUT1@://window.sui'
	]
)

basic = executable('basic', [
		'basic/main.c',
		basic_bundle,
	],
	dependencies: [glesv2, chopsui]
)
