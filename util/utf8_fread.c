#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <chopsui/util/unicode.h>

ssize_t utf8_fread(FILE *f, uint32_t *ch) {
	return utf8_read(fileno(f), ch);
}
