#include <stdlib.h>
#include <chopsui/util/hashtable.h>
#include <chopsui/util/hash.h>
#include <chopsui/util/log.h>
#include <chopsui/type.h>
#include "type.h"

sui_hashtable_t *type_impl_map = NULL;

static void impl_map_init() {
	if (type_impl_map) {
		return;
	}
	type_impl_map = hashtable_create(256, hash);
}

void type_impl_register(const char *type, const struct sui_type_impl *impl) {
	impl_map_init();
	sui_log(L_DEBUG, "Registering type impl %p for %s", impl, type);
	struct sui_auto_impl *_impl = hashtable_get(type_impl_map, type);
	if (!_impl) {
		_impl = calloc(1, sizeof(struct sui_auto_impl));
		_impl->impl = impl;
		hashtable_set(type_impl_map, type, _impl);
	} else {
		while (_impl->next) {
			_impl = _impl->next;
		}
		_impl->next = calloc(1, sizeof(struct sui_auto_impl));
		_impl->next->impl = impl;
	}
}
