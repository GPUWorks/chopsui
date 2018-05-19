#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/scalars.h>
#include <chopsui/type.h>
#include <chopsui/util/errors.h>
#include <chopsui/util/log.h>
#include "css.h"

static const char *stylesheet_attr_name = "chopsui::style::`stylesheet`";

static struct stylesheet *get_stylesheet_attr(struct sui_node *node) {
	const struct sui_scalar *scalar = node_get_attr(node, stylesheet_attr_name);
	return scalar ? (struct stylesheet *)scalar->data : NULL;
}

static bool style_attr(struct sui_node *node, const char *key,
			const struct sui_scalar *value) {
	// TODO: bubble up errors
	if (strcmp(key, "src") == 0) {
		if (value->type != SCALAR_STR) {
			// TODO: Enforce this via attr_spec
			return false;
		}
		errors_t *errs;
		FILE *f = fopen(value->str, "r");
		if (!f) {
			sui_log(L_ERROR, "style node: Failed to open %s", value->str);
			return false;
		}
		struct stylesheet *css = css_load(f, &errs);
		if (!css || errs) {
			sui_log(L_ERROR, "style node: error parsing CSS");
			return false;
		}
		const struct sui_scalar *old_value =
			node_get_attr(node, stylesheet_attr_name);
		if (old_value) {
			struct stylesheet *old_css = old_value->data;
			stylesheet_free(old_css);
		}
		struct sui_scalar css_value = {
			.type = SCALAR_VOID,
			.data = css,
		};
		node_set_attr(node, stylesheet_attr_name, &css_value);
	}
	return true;
}

static bool style_child(struct sui_node *node, struct sui_node *child) {
	struct stylesheet *css = get_stylesheet_attr(node);
	add_style_context(child, css);
	return true;
}

static void style_child_removed(
		struct sui_node *node, struct sui_node *child) {
	remove_style_context(child);
}

static void style_init(struct sui_node *node) {
	sui_log(L_DEBUG, "init");
}

static const struct sui_type_impl style_type_impl = {
	.attr = style_attr,
	.child = style_child,
	.child_removed = style_child_removed,
	.init = style_init,
};

void style_type_register() {
	type_impl_register("style", &style_type_impl);
}
