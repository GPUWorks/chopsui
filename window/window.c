#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <chopsui/scalars.h>
#include <chopsui/type.h>

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

struct sui_type_impl native_window_impl = {
	.attr_spec = native_attr_spec,
	.attr_default = native_attr_default,
	.child = native_child,
};

void register_window_type() {
	type_impl_register("window", &native_window_impl);
	// TODO: detect platform and use appropriate native window
	//type_impl_register("window", &wayland_native_window_impl);
}
