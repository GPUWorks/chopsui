#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <chopsui/host.h>
#include <chopsui/node.h>
#include <chopsui/scalars.h>
#include <chopsui/render_node.h>
#include <chopsui/type.h>
#include <chopsui/util/log.h>
#include "wayland.h"

struct attr_spec spec[] = {
	{
		.key = "title",
		.spec = SCALAR_STR,
		.value = { .type = SCALAR_STR, .str = "chopsui window" }
	},
	{
		// TODO: Invalidate children when these change
		.key = "width",
		.spec = SCALAR_INT,
		.value = { .type = SCALAR_INT, .ival = 640 }
	},
	{
		.key = "height",
		.spec = SCALAR_INT,
		.value = { .type = SCALAR_INT, .ival = 480 }
	},
};

static uint64_t native_attr_spec(const char *key) {
	return attr_spec_attr_spec(&spec, key);
}

static bool native_attr_default(const char *key, struct sui_scalar *value) {
	return attr_spec_attr_default(&spec, key, value);
}

const char *window_renderable_child_attr =
	"chopsui::window::`renderable_child`";

static bool render_child(struct sui_node *parent, struct sui_node *child) {
	const struct sui_scalar *attr =
		node_get_attr(parent, window_renderable_child_attr);
	if (attr) {
		return false;
	}
	struct sui_scalar new_attr = {
		.type = SCALAR_VOID,
		.data = child,
	};
	node_set_attr(parent, window_renderable_child_attr, &new_attr);
	return true;
}

static void render_child_removed(
		struct sui_node *parent, struct sui_node *child) {
	const struct sui_scalar *attr =
		node_get_attr(parent, window_renderable_child_attr);
	if (!attr) {
		return;
	}
	node_set_attr(child, window_renderable_child_attr, NULL);
}

static struct render_node_impl render_impl = {
	.child = render_child,
	.child_removed = render_child_removed,
};

static void native_init(struct sui_node *node) {
	render_node_init(node, &render_impl);
}

struct sui_type_impl native_window_type = {
	.attr_spec = native_attr_spec,
	.attr_default = native_attr_default,
	.init = native_init,
};
