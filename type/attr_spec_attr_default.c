#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <chopsui/scalars.h>
#include <chopsui/type.h>

bool _attr_spec_attr_default(const struct attr_spec (*spec)[], size_t len,
		const char *key, struct sui_scalar *value) {
	for (size_t i = 0; i < len; ++i) {
		const struct attr_spec *_spec = &(*spec)[i];
		if (strcmp(_spec->key, key) == 0) {
			memcpy(value, &_spec->value, sizeof(struct sui_scalar));
			if (_spec->spec == SCALAR_STR) {
				value->str = strdup(_spec->value.str);
			}
			return true;
		}
	}
	return false;
}
