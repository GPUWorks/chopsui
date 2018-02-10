#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <chopsui/host.h>
#include <chopsui/node.h>
#include <chopsui/scalars.h>
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

static uint64_t native_attr_spec(struct sui_node *node, const char *key) {
	return attr_spec_attr_spec(&spec, key);
}

static bool native_attr_default(const char *key, struct sui_scalar *value) {
	return attr_spec_attr_default(&spec, key, value);
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
