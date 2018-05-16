tests = [
		'test_css_parse',
		'test_node_find_ancestor',
		'test_node_find_descendant',
		'test_node_matches_selector',
		'test_scalar_parse',
		'test_selector_parse',
		'test_sui_parse',
		'test_unicode',
]

foreach t : tests
	_test = executable(
		t,
		['main.c', t + '.c'],
		link_with: [lib_chopsui],
		include_directories: sui_inc,
		c_args: ['-Wno-unused-function'],
	)
	test(t, _test)
endforeach
