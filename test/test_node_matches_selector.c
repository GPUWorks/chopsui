#include <string.h>
#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/sui.h>
#include "test.h"

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

static int test_descendant() {
	struct sui_node *root = sui_parse(
		"test\n"
		"\tfoo\n"
		"\t\tbar\n"
		"\t\t\tbaz"
	, NULL);
	struct sui_node *node = root;
	node = node->children->items[0]; // foo
	node = node->children->items[0]; // bar
	node = node->children->items[0]; // baz

	struct selector *matches = selector_parse("foo bar baz");
	struct selector *missing_middle = selector_parse("foo baz");
	struct selector *no_match = selector_parse("foo bar");
	struct selector *no_match_2 = selector_parse("tim");
	assert(node_matches_selector(node, matches));
	assert(node_matches_selector(node, missing_middle));
	assert(!node_matches_selector(node, no_match));
	assert(!node_matches_selector(node, no_match_2));
	return 0;
}

static int test_child() {
	struct sui_node *root = sui_parse(
		"test\n"
		"\tfoo\n"
		"\t\tbar\n"
		"\t\t\tbaz"
	, NULL);
	struct sui_node *node = root;
	node = node->children->items[0]; // foo
	node = node->children->items[0]; // bar
	node = node->children->items[0]; // baz

	struct selector *matches = selector_parse("foo bar > baz");
	struct selector *missing_middle = selector_parse("foo > baz");
	struct selector *no_match = selector_parse("foo > bar");
	struct selector *no_match_2 = selector_parse("tim");
	assert(node_matches_selector(node, matches));
	assert(!node_matches_selector(node, missing_middle));
	assert(!node_matches_selector(node, no_match));
	assert(!node_matches_selector(node, no_match_2));
	assert(!node_matches_selector(root, no_match));
	return 0;
}

static int test_sibling() {
	struct sui_node *root = sui_parse(
		"test\n"
		"\tfoo\n"
		"\tbar\n"
		"\tbaz"
	, NULL);
	struct sui_node *baz = root->children->items[2];

	struct selector *matches = selector_parse("foo ~ baz");
	struct selector *matches_2 = selector_parse("bar ~ baz");
	struct selector *no_match = selector_parse("baz ~ bar");
	struct selector *no_match_2 = selector_parse("tim ~ bar");
	assert(node_matches_selector(baz, matches));
	assert(node_matches_selector(baz, matches_2));
	assert(!node_matches_selector(baz, no_match));
	assert(!node_matches_selector(baz, no_match_2));
	return 0;
}

static int test_adjacent_sibling() {
	struct sui_node *root = sui_parse(
		"test\n"
		"\tfoo\n"
		"\tbar\n"
		"\tbaz"
	, NULL);
	struct sui_node *baz = root->children->items[2];

	struct selector *matches = selector_parse("bar + baz");
	struct selector *no_match = selector_parse("foo + baz");
	assert(node_matches_selector(baz, matches));
	assert(!node_matches_selector(baz, no_match));
	return 0;
}

int test_main() {
	init_test_types();
	return test_type()
		|| test_class()
		|| test_id()
		|| test_descendant()
		|| test_child()
		|| test_sibling()
		|| test_adjacent_sibling()
	;
}
