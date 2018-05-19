#include <assert.h>
#include <stdbool.h>
#include <strings.h>
#include <chopsui/node.h>
#include <chopsui/css.h>
#include "node.h"

bool node_matches_selector(const struct sui_node *node,
		const struct selector *selector) {
	assert(node && selector);
	struct sui_node *parent;
	while (selector) {
		switch (selector->type) {
		case SELECTOR_ANY:
			return true;
		case SELECTOR_ID:
			// TODO: we probably want to meander up to the parent and do a
			// hashtable lookup here
			if (strcasecmp(node->id, selector->value) != 0) {
				return false;
			}
			break;
		case SELECTOR_TYPE:
			if (strcasecmp(node->type, selector->value) != 0) {
				return false;
			}
			break;
		case SELECTOR_CLASS:
			// TODO: This is case insensitive per the spec
			if (!set_contains(node->classes, selector->value)) {
				return false;
			}
			break;
		case SELECTOR_DESCENDANT:
			while (node->parent) {
				if (node_matches_selector(node->parent, selector->next)) {
					return true;
				}
				node = node->parent;
			}
			return false;
		case SELECTOR_CHILD:
			return node->parent && node_matches_selector(
					node->parent, selector->next);
		case SELECTOR_SIBLING:
			// TODO: this could probably be more effecient in a broader context
			parent = node->parent;
			for (size_t i = 0; parent && i < parent->children->length; ++i) {
				struct sui_node *test = parent->children->items[i];
				if (node_matches_selector(test, selector->next)) {
					return true;
				}
				if (test == node) {
					break;
				}
			}
			return false;
		case SELECTOR_NEXT_SIBLING:
			parent = node->parent;
			for (size_t i = 0; i < parent->children->length; ++i) {
				struct sui_node *test = parent->children->items[i];
				if (test == node) {
					if (i == 0) {
						return false;
					}
					test = parent->children->items[i - 1];
					return node_matches_selector(test, selector->next);
				}
			}
			return false;
		case SELECTOR_ATTRIBUTE:
			// TODO: CSS parser doesn't do these yet anyway
			return false;
		}
		selector = selector->next;
	}
	return true;
}
