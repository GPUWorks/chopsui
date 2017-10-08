#include <chopsui/util/hashtable.h>
#include <chopsui/scalars.h>
#include <chopsui/node.h>

const struct sui_scalar *node_get_attr(struct sui_node *node, const char *key) {
	return (const struct sui_scalar *)hashtable_get(node->attributes, key);
}
