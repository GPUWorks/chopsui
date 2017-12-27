#include <chopsui/util/hashtable.h>
#include <chopsui/scalars.h>
#include <chopsui/node.h>

struct iter_data {
	const char *key;
	bool provided;
	struct sui_scalar value;
};

bool type_impls_map(const char *type,
		bool (*iter)(const struct sui_type_impl *, void *), void *data);

static bool iter(const struct sui_type_impl *impl, void *_data) {
	struct iter_data *data = _data;
	if (impl->attr_default) {
		if (impl->attr_default(data->key, &data->value)) {
			data->provided = true;
			return false;
		}
	}
	return true;
}

const struct sui_scalar *node_get_attr(struct sui_node *node, const char *key) {
	const struct sui_scalar *value = hashtable_get(node->attributes, key);
	if (!value) {
		static struct iter_data data;
		data.key = key;
		data.provided = false,
		type_impls_map(node->type, iter, &data);
		if (data.provided) {
			return &data.value;
		}
		return NULL;
	}
	return value;
}
