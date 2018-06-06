demos = [
    'basic'
]

foreach d : demos
	executable(d, [d + '.c'],
		link_with: [lib_chopsui],
		include_directories: sui_inc,
		dependencies: [glesv2]
	)
endforeach
