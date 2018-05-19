#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/util/hashtable.h>
#include "css.h"

struct candidate_rule {
	const struct style_rule *rule;
	const struct sui_scalar *value;
	int specificity;
};

const struct sui_scalar *style_get_attr(
		struct sui_node *node, const char *key) {
	struct style_context *ctx = style_get_context(node);
	const struct sui_scalar *value = node_get_attr(node, key);
	if (value) {
		return value;
	}
	struct candidate_rule candidate = {
		.rule = NULL,
		.specificity = -1,
		.value = NULL,
	};
	while (ctx) {
		for (size_t i = 0; i < ctx->stylesheet->rules->length; ++i) {
			const struct style_rule *rule = ctx->stylesheet->rules->items[i];
			for (size_t j = 0; j < rule->selectors->length; ++j) {
				const struct selector *s = rule->selectors->items[i];
				if (s->specificity < candidate.specificity) {
					continue;
				}
				if (!node_matches_selector(node, s)) {
					continue;
				}
				value = hashtable_get(rule->properties, key);
				if (!value) {
					continue;
				}
				candidate.rule = rule;
				candidate.specificity = s->specificity;
				candidate.value = value;
			}
		}
		ctx = ctx->parent;
	}
	return candidate.value;
}
