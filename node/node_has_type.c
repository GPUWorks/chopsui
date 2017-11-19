#include <stdbool.h>
#include <stdlib.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include "node.h"

bool node_has_type(struct sui_node *node, const struct sui_type_impl *impl) {
	struct sui_type *type = node->sui_type;
	while (type) {
		if (type->impl == impl) {
			return true;
		}
		type = type->next;
	}
	return false;
}
