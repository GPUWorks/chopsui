#include <chopsui/util/list.h>
#include <chopsui/node.h>
#include <chopsui/tree.h>

int node_append_child(struct sui_node *parent, struct sui_node *child) {
	if (!child || !parent || child->parent != NULL) {
		return 0;
	}
	list_add(parent->children, child);
	child->parent = parent;
	return 1;
}
