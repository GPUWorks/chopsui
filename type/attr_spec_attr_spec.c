#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <chopsui/type.h>

uint64_t _attr_spec_attr_spec(const struct attr_spec (*spec)[], size_t len,
		const char *key) {
	for (size_t i = 0; i < len; ++i) {
		if (strcmp((*spec)[i].key, key) == 0) {
			return (*spec)[i].spec;
		}
	}
	return 0;
}
