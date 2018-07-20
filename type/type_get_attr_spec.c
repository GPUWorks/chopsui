#include <stdint.h>
#include <chopsui/type.h>

struct iter_data {
	const char *key;
	uint32_t spec;
};

static bool iter(const struct sui_type_impl *impl, void *data) {
	struct iter_data *iter_data = data;
	if (impl->attr_spec) {
		iter_data->spec |= impl->attr_spec(iter_data->key);
	}
	return true;
}

uint32_t type_get_attr_spec(const char *type, const char *key) {
	struct iter_data data = { key, 0 };
	type_impls_map(type, iter, &data);
	return data.spec;
}
