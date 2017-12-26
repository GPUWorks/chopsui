#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <chopsui/util/log.h>
#include "test.h"

static void log_noop(log_importance_t importance,
		const char *fmt, va_list args) {
	// This space intentionally left blank
}

int main(int argc, char **argv) {
	if (!getenv("SUI_LOG")) {
		sui_log_init(log_noop);
	}
	printf("%s", test_name);
	int dots = 50 - strlen(test_name);
	while (dots--) putchar('.');
	int ret = test_main();
	if (ret) {
		printf("\033[31mFAIL\033[0m\n");
	} else {
		printf("\033[32mPASS\033[0m\n");
	}
	return ret;
}
