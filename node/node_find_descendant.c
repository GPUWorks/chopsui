#include <chopsui/css.h>
#include <chopsui/node.h>
#include "node.h"

struct sui_node *node_find_descendant(struct sui_node *node,
		struct selector *selector) {
	for (size_t i = 0; i < node->children->length; ++i) {
		struct sui_node *candidate = node->children->items[i];
		if (node_matches_selector(candidate, selector)) {
			return candidate;
		}
		candidate = node_find_descendant(candidate, selector);
		if (candidate) {
			return candidate;
		}
	}
	return NULL;
}
