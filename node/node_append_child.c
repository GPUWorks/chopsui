#include <chopsui/util/list.h>
#include <chopsui/node.h>
#include "node.h"

int node_append_child(struct sui_node *parent, struct sui_node *child) {
	if (!child || !parent || child->parent != NULL) {
		return 0;
	}
	struct sui_type *type = parent->sui_type;
	while (type) {
		if (type->impl->child) {
			if (!type->impl->child(parent, child)) {
				// TODO: bubble up better errors
				return 0;
			}
		}
		type = type->next;
	}
	list_add(parent->children, child);
	child->parent = parent;
	return 1;
}
