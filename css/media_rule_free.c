#include <stdlib.h>
#include <chopsui/util/list.h>
#include <chopsui/css.h>

void media_rule_free(struct media_rule *rule) {
	while (rule) {
		struct media_rule *next = rule->next;
		free(rule);
		rule = next;
	}
}
