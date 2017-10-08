#include <stdbool.h>
#include <chopsui/util/set.h>
#include <chopsui/node.h>

void node_remove_class(struct sui_node *node, const char *name) {
	set_del(node->classes, name);
}
