#include <stdlib.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include "node.h"

void node_type_remove_impl(struct sui_node *node, const struct sui_type_impl *impl) {
	struct sui_type *type = node->sui_type;
	struct sui_type *prev = NULL;
	while (type) {
		if (type->impl == impl) {
			if (prev) {
				prev->next = type->next;
			}
			if (node->sui_type == type) {
				node->sui_type = type->next;
			}
			free(type);
			break;
		}
		prev = type;
		type = type->next;
	}
}
