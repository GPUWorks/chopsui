#include <chopsui/css.h>
#include <chopsui/node.h>
#include <chopsui/scalars.h>
#include <chopsui/util/hashtable.h>
#include <string.h>
// TODO: gross
#include "../node/node.h"
#include "css.h"

#include <stdio.h>

struct candidate_rule {
	const struct style_rule *rule;
	const char *value;
	int specificity;
};

bool style_get_attr(struct sui_node *node,
		const char *key, struct sui_scalar *out) {
	struct style_context *ctx = style_get_context(node);
	const struct sui_scalar *value = node_get_attr(node, key);
	if (value) {
		memcpy(out, value, sizeof(struct sui_scalar));
		return true;
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
				char *svalue = hashtable_get(rule->properties, key);
				if (!svalue) {
					continue;
				}
				candidate.rule = rule;
				candidate.specificity = s->specificity;
				candidate.value = svalue;
			}
		}
		ctx = ctx->parent;
	}
	if (candidate.value) {
		struct sui_type *type = node->sui_type;
		if (!type) {
			return false; // wat
		}
		uint64_t spec;
		while (type) {
			if (type->impl->attr_spec) {
				spec |= type->impl->attr_spec(key);
			}
			type = type->next;
		}
		// TODO: Cache the parsed scalar for this node?
		return scalar_parse(candidate.value, out, spec);
	}
	return false;
}
