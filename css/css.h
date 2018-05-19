#ifndef _CSS_PRIVATE_H
#define _CSS_PRIVATE_H

struct style_context {
	struct stylesheet *stylesheet;
	struct style_context *parent;
	size_t refs;
};

struct style_context *style_get_context(struct sui_node *node);
void add_style_context(struct sui_node *node, struct stylesheet *stylesheet);
void remove_style_context(struct sui_node *node);

#endif
