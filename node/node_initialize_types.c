#include <assert.h>
#include <stdbool.h>
#include <chopsui/util/list.h>
#include <chopsui/node.h>
#include <chopsui/type.h>

static bool iter(const struct sui_type_impl *impl, void *data) {
	struct sui_node *node = data;
	node_type_add_impl(node, impl);
	if (impl->init) {
		impl->init(node);
	}
	return true;
}

bool node_initialize_types(struct sui_node *node) {
	assert(node);
	return type_impls_map(node->type, iter, node);
}
