#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include "css.h"

extern const char *ctx_attr_name;
extern const struct sui_type_impl style_context_type_impl;

struct style_context *style_get_context(struct sui_node *node) {
	if (!node_has_type(node, &style_context_type_impl)) {
		return NULL;
	}
	const struct sui_scalar *scalar = node_get_attr(node, ctx_attr_name);
	return scalar ? (struct style_context *)scalar->data : NULL;
}
