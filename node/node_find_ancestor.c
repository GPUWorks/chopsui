#include <stdbool.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include "node.h"

static bool ancestor_iter(struct sui_node *node, void *data) {
	// Stop on the first match
	struct sui_node **match = data;
	*match = node;
	return false;
}

struct sui_node *node_find_ancestor(struct sui_node *node,
		struct selector *selector) {
	struct sui_node *match = NULL;
	node_find_ancestors(node, selector, ancestor_iter, &match);
	return match;
}
