#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <chopsui/util/unicode.h>

ssize_t utf8_fread(FILE *f, uint32_t *ch) {
	char buf[UTF8_MAX_SIZE];
	const char *str = buf;
	if (fread(&buf, 1, 1, f) == 0) {
		return -1;
	}
	int size = utf8_size(str);
	if (size < 0) {
		return -1;
	}
	if ((int)fread(&buf[1], size - 1, 1, f) != size - 1) {
		return -1;
	}
	*ch = utf8_decode(&str);
	return size;
}
