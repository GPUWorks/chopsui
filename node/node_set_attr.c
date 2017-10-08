#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <string.h>
#include <chopsui/util/hashtable.h>
#include <chopsui/scalars.h>
#include <chopsui/node.h>

void node_set_attr(struct sui_node *node, const char *key,
		const struct sui_scalar *value) {
	if (node->impl && node->impl->attr) {
		if (!node->impl->attr(node, key, value)) {
			return;
		}
	}
	struct sui_scalar *_value = malloc(sizeof(struct sui_scalar));
	memcpy(_value, value, sizeof(struct sui_scalar));
	free(hashtable_set(node->attributes, key, _value));
}
