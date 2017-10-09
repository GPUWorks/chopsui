#include <assert.h>
#include <stdbool.h>
#include <strings.h>
#include <chopsui/node.h>
#include <chopsui/css.h>
#include "node.h"

bool node_matches_selector(struct sui_node *node, struct selector *selector) {
	assert(node && selector);
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
		default:
			// TODO: more selector types
			return false;
		}
		selector = selector->next;
	}
	return true;
}
