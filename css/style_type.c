#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/scalars.h>
#include <chopsui/type.h>
#include <chopsui/util/errors.h>

static bool style_node_attr(struct sui_node *node, const char *key,
			const struct sui_scalar *value) {
	// TODO: bubble up errors
	if (strcmp(key, "src") == 0) {
		if (value->type != SCALAR_STR) {
			return false;
		}
		errors_t *errs;
		FILE *f = fopen(value->str, "r");
		if (!f) {
			return false;
		}
		struct stylesheet *css = css_load(f, &errs);
		if (!css || errs) {
			return false;
		}
		const struct sui_scalar *old_value =
			node_get_attr(node, "chopsui::style::`stylesheet`");
		assert(old_value->type == SCALAR_VOID);
		if (old_value) {
			struct stylesheet *old_css = old_value->data;
			stylesheet_free(old_css);
		}
		struct sui_scalar css_value = {
			.type = SCALAR_VOID,
			.data = css,
		};
		node_set_attr(node, "chopsui::style::`stylesheet`", &css_value);
	}
	return true;
}

static const struct sui_type_impl style_type_impl = {
	.attr = style_node_attr,
};

void style_type_register() {
	type_impl_register("style", &style_type_impl);
}
