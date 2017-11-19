#include <stdbool.h>
#include <stdlib.h>
#include <chopsui/util/hashtable.h>
#include <chopsui/type.h>
#include "type.h"

bool type_impls_map(const char *type,
		bool (*iter)(const struct sui_type_impl *, void *), void *data) {
	struct sui_auto_impl *impl = hashtable_get(type_impl_map, type);
	if (!impl) {
		return false;
	}
	while (impl) {
		if (!iter(impl->impl, data)) {
			return false;
		}
		impl = impl->next;
	}
	return true;
}
