#include <string.h>
#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/sui.h>
#include "test.h"

char *test_name = "node/node_find_descendant";

static void init_test_types() {
	static struct sui_type_impl impl = { 0 };
	set_impl_for_type("foo", &impl);
	set_impl_for_type("bar", &impl);
	set_impl_for_type("baz", &impl);
}

static int test_simple() {
	struct sui_node *node = sui_parse(
		"foo\n"
		"\tbar\n"
		"\tbaz .test", NULL);
	struct sui_node *target = node;      // foo
	target = target->children->items[1]; // baz.test
	struct selector *selector = selector_parse(".test");
	assert(node_find_descendant(node, selector) == target);
	return 0;
}

static int test_depth_first() {
	struct sui_node *node = sui_parse(
		"foo\n"
		"\tbar\n"
		"\t\tbaz .test\n"
		"\tbaz .test", NULL);
	struct sui_node *target = node;      // foo
	target = target->children->items[0]; // bar
	target = target->children->items[0]; // baz.test #1
	struct selector *selector = selector_parse(".test");
	assert(node_find_descendant(node, selector) == target);
	return 0;
}

static int test_not_found() {
	struct sui_node *node = sui_parse(
		"foo\n"
		"\tbar\n"
		"\t\tbaz", NULL);
	struct selector *selector = selector_parse(".test");
	assert(node_find_descendant(node, selector) == NULL);
	return 0;
}

int test_main() {
	init_test_types();
	return test_simple()
		|| test_depth_first()
		|| test_not_found()
	;
}
