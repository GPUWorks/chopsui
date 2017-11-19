#include <stdlib.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include "node.h"

void node_type_add_impl(struct sui_node *node, const struct sui_type_impl *impl) {
	struct sui_type *type = node->sui_type;
	if (!type) {
		node->sui_type = type = calloc(1, sizeof(struct sui_type));
	} else {
		while (type->next) {
			type = type->next;
		}
		type->next = calloc(1, sizeof(struct sui_type));
		type = type->next;
	}
	type->impl = impl;
	// TODO: apply attributes
}
