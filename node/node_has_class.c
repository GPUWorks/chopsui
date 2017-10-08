#include <stdbool.h>
#include <chopsui/util/set.h>
#include <chopsui/node.h>

bool node_has_class(struct sui_node *node, const char *name) {
	return set_contains(node->classes, name);
}
