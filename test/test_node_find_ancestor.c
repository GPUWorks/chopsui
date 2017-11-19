#include <string.h>
#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/sui.h>
#include "test.h"

char *test_name = "node/node_find_ancestor(s)";

static void init_test_types() {
	static struct sui_type_impl impl = { 0 };
	type_impl_register("foo", &impl);
	type_impl_register("bar", &impl);
	type_impl_register("baz", &impl);
	type_impl_register("zab", &impl);
}

static int test_simple() {
	struct sui_node *node = sui_parse(
		"foo .test\n"
		"\tbar\n"
		"\t\tbaz", NULL);
	struct sui_node *target = node;      // foo
	target = target->children->items[0]; // bar
	target = target->children->items[0]; // baz
	struct selector *selector = selector_parse(".test");
	assert(node_find_ancestor(target, selector) == node);
	return 0;
}

static bool test_ancestors_iter(struct sui_node *node, void *data) {
	int *count = data;
	++(*count);
	assert(node_has_class(node, "test"));
	return true;
}

static int test_ancestors() {
	struct sui_node *node = sui_parse(
		"foo .test\n"
		"\tbar\n"
		"\t\tbaz .test\n"
		"\t\t\tzab", NULL);
	struct sui_node *target = node;      // foo
	target = target->children->items[0]; // bar
	target = target->children->items[0]; // baz
	target = target->children->items[0]; // zab
	struct selector *selector = selector_parse(".test");
	int count = 0;
	node_find_ancestors(target, selector, test_ancestors_iter, &count);
	assert(count == 2);
	return 0;
}

int test_main() {
	init_test_types();
	return test_simple()
		|| test_ancestors()
	;
}
