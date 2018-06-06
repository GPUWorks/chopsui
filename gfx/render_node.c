#include <assert.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/render_node.h>
#include <chopsui/scalars.h>
#include <chopsui/util/log.h>

static const char *render_attr_name = "chopsui::render_node::`impl`";
struct sui_type_impl render_context_impl;

static bool anscestor_iter(struct sui_node *node, void *data) {
	struct sui_node **target = data;
	if (node_has_type(node, &render_node_impl)) {
		*target = node;
		return false;
	}
	return true;
}

struct sui_node *render_node_get_renderable_ancestor(struct sui_node *node) {
	static struct selector *select_all = NULL;
	if (!select_all) {
		select_all = selector_parse("*");
		assert(select_all);
	}
	struct sui_node *ancestor = NULL;
	node_find_ancestors(node, select_all, anscestor_iter, &ancestor);
	return ancestor;
}

static struct render_node_impl *get_render_node_impl(struct sui_node *node) {
	assert(node_has_type(node, &render_node_impl));
	const struct sui_scalar *impl = node_get_attr(node, render_attr_name);
	assert(impl);
	return impl->data;
}

void render_node_render(
		struct sui_node *node, uint32_t width, uint32_t height) {
	struct render_node_impl *impl = get_render_node_impl(node);
	impl->render(node, width, height);
}

static bool context_child(struct sui_node *node, struct sui_node *child) {
	node_type_add_impl(child, &render_context_impl);
	if (!node_has_type(child, &render_node_impl)) {
		return true;
	}
	struct sui_node *renderable_ancestor =
		render_node_get_renderable_ancestor(node);
	if (renderable_ancestor) {
		struct render_node_impl *impl =
			get_render_node_impl(renderable_ancestor);
		return impl->child(renderable_ancestor, child);
	}
	return true;
}

static void context_child_removed(struct sui_node *node,
		struct sui_node *child) {
	node_type_remove_impl(child, &render_context_impl);
	struct sui_node *renderable_ancestor =
		render_node_get_renderable_ancestor(node);
	if (renderable_ancestor) {
		struct render_node_impl *impl =
			get_render_node_impl(renderable_ancestor);
		impl->child_removed(node, child);
	}
}

struct sui_type_impl render_context_impl = {
	.child = context_child,
	.child_removed = context_child_removed,
};

void render_node_init(struct sui_node *node, struct render_node_impl *impl) {
	struct sui_scalar render_impl = {
		.type = SCALAR_VOID,
		.data = impl,
	};
	assert(!node_get_attr(node, render_attr_name));
	node_set_attr(node, render_attr_name, &render_impl);
}

bool render_node_child(struct sui_node *node, struct sui_node *child) {
	node_type_add_impl(child, &render_context_impl);
	return true;
}

void render_node_child_removed(struct sui_node *node, struct sui_node *child) {
	node_type_remove_impl(child, &render_context_impl);
}

struct sui_type_impl render_node_impl = {
	.child = render_node_child,
	.child_removed = render_node_child_removed,
};
