#include <chopsui/css.h>
#include <chopsui/node.h>
#include "node.h"

void node_find_ancestors(struct sui_node *node, struct selector *selector,
		bool (*iter)(struct sui_node *node, void *data), void *data) {
	while (node->parent) {
		node = node->parent;
		if (node_matches_selector(node, selector)) {
			if (!iter(node, data)) {
				break;
			}
		}
	}
	return;
}
