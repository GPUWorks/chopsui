#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <chopsui/util/unicode.h>

ssize_t utf8_read(int fd, uint32_t *ch) {
	char buf[UTF8_MAX_SIZE];
	const char *str = buf;
	if (read(fd, &buf, 1) < 0) {
		return -1;
	}
	int size = utf8_size(str);
	if (size < 0) {
		return -1;
	}
	if (read(fd, &buf[1], size - 1) != size - 1) {
		return -1;
	}
	*ch = utf8_decode(&str);
	return size;
}
