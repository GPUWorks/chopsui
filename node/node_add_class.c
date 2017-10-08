#include <stdbool.h>
#include "chopsui/util/set.h"
#include "chopsui/node.h"

void node_add_class(struct sui_node *node, const char *name) {
	set_add(node->classes, name);
}
