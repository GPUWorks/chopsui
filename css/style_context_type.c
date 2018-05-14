#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/scalars.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include <stdlib.h>
#include "css.h"

const char *ctx_attr_name = "chopsui::style_context::`context`";
const struct sui_type_impl style_context_type_impl;

static bool context_child(struct sui_node *node, struct sui_node *child) {
	struct style_context *ctx = style_get_context(node);
	struct sui_scalar ctx_scalar = {
		.type = SCALAR_VOID,
		.data = ctx,
	};
	node_set_attr(child, ctx_attr_name, &ctx_scalar);
	node_type_add_impl(child, &style_context_type_impl);
	return true;
}

static void context_child_removed(struct sui_node *node,
		struct sui_node *child) {
	remove_style_context(child);
}

const struct sui_type_impl style_context_type_impl = {
	.child = context_child,
	.child_removed = context_child_removed,
};

void add_style_context(struct sui_node *node, struct stylesheet *stylesheet) {
	struct style_context *ctx = calloc(1, sizeof(struct style_context));
	ctx->stylesheet = stylesheet;
	ctx->parent = style_get_context(node);
	ctx->refs = 1;

	struct sui_scalar ctx_scalar = {
		.type = SCALAR_VOID,
		.data = ctx,
	};
	node_set_attr(node, ctx_attr_name, &ctx_scalar);

	node_type_add_impl(node, &style_context_type_impl);
}

void remove_style_context(struct sui_node *node) {
	struct style_context *ctx = style_get_context(node);
	if (!ctx) {
		return;
	}

	node_set_attr(node, ctx_attr_name, NULL);
	node_type_remove_impl(node, &style_context_type_impl);

	for (size_t i = 0; i < node->children->length; ++i) {
		struct sui_node *child = node->children->items[i];
		struct style_context *child_ctx = style_get_context(child);
		if (child_ctx == ctx) {
			remove_style_context(child);
		} else if (child_ctx->parent == ctx) {
			child_ctx->parent = NULL;
			break;
		} else {
			assert(0);
		}
	}
}
