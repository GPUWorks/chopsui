#include <chopsui/css.h>
#include <chopsui/node.h>
#include "node.h"

static bool _node_find_descendants(struct sui_node *node,
		struct selector *selector,
		bool (*iter)(struct sui_node *node, void *data), void *data) {
	for (size_t i = 0; i < node->children->length; ++i) {
		struct sui_node *candidate = node->children->items[i];
		if (node_matches_selector(candidate, selector)) {
			if (!iter(candidate, data)) {
				return false;
			}
		}
		if (!_node_find_descendants(candidate, selector, iter, data)) {
			return false;
		}
	}
	return true;
}

void node_find_descendants(struct sui_node *node, struct selector *selector,
		bool (*iter)(struct sui_node *node, void *data), void *data) {
	_node_find_descendants(node, selector, iter, data);
}
