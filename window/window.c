#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <chopsui/scalars.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include <chopsui/window.h>

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
		.value = { .type = SCALAR_INT, .ival = -1 }
	},
	{
		.key = "height",
		.spec = SCALAR_INT,
		.value = { .type = SCALAR_INT, .ival = -1 }
	},
};

static uint64_t native_attr_spec(struct sui_node *node, const char *key) {
	return attr_spec_attr_spec(&spec, key);
}

static void native_attr_default(const char *key, struct sui_scalar *value) {
	attr_spec_attr_default(&spec, key, value);
}

static bool native_child(struct sui_node *parent, struct sui_node *child) {
	// TODO: ensure child has gl_aware type
	return true;
}

struct sui_type_impl native_window_type = {
	.attr_spec = native_attr_spec,
	.attr_default = native_attr_default,
	.child = native_child,
};

// TODO: Figure out a design that allows for multiple windows in one process
// Probably via a "host" interface of some sort

void register_window_types() {
	type_impl_register("window", &native_window_type);
	// TODO: detect platform and register appropriate native window type
	type_impl_register("window", &wayland_native_window_type);
}

void window_run(struct sui_node *node) {
	assert(node_has_type(node, &native_window_type));
	struct native_window_impl *impl =
		node_get_attr(node, "chopsui::window::`native_window_impl`")->data;
	impl->run(node);
}
