#ifndef _SUI_TYPE_INTERNAL_H
#define _SUI_TYPE_INTERNAL_H
#include <chopsui/util/hashtable.h>

extern sui_hashtable_t *type_impl_map;

struct sui_type_impl;

struct sui_auto_impl {
	const struct sui_type_impl *impl;
	struct sui_auto_impl *next;
};

#endif
