#ifndef _SUI_LOG_H
#define _SUI_LOG_H
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

typedef enum {
	L_SILENT = 0,
	L_ERROR = 1,
	L_INFO = 2,
	L_DEBUG = 3,
	L_LAST,
} log_importance_t;

typedef void (*log_callback_t)(log_importance_t importance, const char *fmt, va_list args);

void sui_log_init(log_callback_t callback);

#ifdef __GNUC__
#define ATTRIB_PRINTF(start, end) __attribute__((format(printf, start, end)))
#else
#define ATTRIB_PRINTF(start, end)
#endif

void _sui_log(log_importance_t verbosity, const char *format, ...) ATTRIB_PRINTF(2, 3);
void _sui_vlog(log_importance_t verbosity, const char *format, va_list args) ATTRIB_PRINTF(2, 0);
const char *_strip_path(const char *filepath);

#define sui_log(verb, fmt, ...) \
	_sui_log(verb, "[%s:%d] " fmt, _strip_path(__FILE__), __LINE__, ##__VA_ARGS__)

#define sui_vlog(verb, fmt, args) \
	_sui_vlog(verb, "[%s:%d] " fmt, _strip_path(__FILE__), __LINE__, args)

#define sui_log_errno(verb, fmt, ...) \
	sui_log(verb, fmt ": %s", ##__VA_ARGS__, strerror(errno))

#endif
