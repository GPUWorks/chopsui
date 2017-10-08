#include <stdlib.h>
#include <chopsui/util/list.h>
#include <chopsui/css.h>

static void style_property_free_iter(void *prop, void *_) {
	free(prop);
}

void style_rule_free(struct style_rule *rule) {
	if (!rule) return;
	for (size_t i = 0; rule->selectors && i < rule->selectors->length; ++i) {
		struct selector *s = rule->selectors->items[i];
		selector_free(s);
	}
	list_free(rule->selectors);
	if (rule->properties) {
		hashtable_iter(rule->properties, style_property_free_iter, NULL);
		hashtable_free(rule->properties);
	}
}
