#include <string.h>
#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/sui.h>
#include "../test.h"

bool node_matches_selector(struct sui_node *node, struct selector *selector);

char *test_name = "node/node_matches_selector";

struct sui_node *single_node;

static void init_test_types() {
	static struct sui_type_impl impl = { 0 };
	set_impl_for_type("test", &impl);
	set_impl_for_type("foo", &impl);
	set_impl_for_type("bar", &impl);
	set_impl_for_type("baz", &impl);
	set_impl_for_type("zab", &impl);
	set_impl_for_type("rab", &impl);
	single_node = sui_parse("test .class @id foo=bar", NULL);
}

static int test_type() {
	struct selector *matches = selector_parse("test");
	struct selector *invalid = selector_parse("foo");
	assert(node_matches_selector(single_node, matches));
	assert(!node_matches_selector(single_node, invalid));
	return 0;
}

static int test_class() {
	struct selector *matches = selector_parse(".class");
	struct selector *invalid = selector_parse(".another-class");
	assert(node_matches_selector(single_node, matches));
	assert(!node_matches_selector(single_node, invalid));
	return 0;
}

static int test_id() {
	struct selector *matches = selector_parse("#id");
	struct selector *invalid = selector_parse("#another-id");
	assert(node_matches_selector(single_node, matches));
	assert(!node_matches_selector(single_node, invalid));
	return 0;
}

int test_main() {
	init_test_types();
	return test_type()
		|| test_class()
		|| test_id()
	;
}
