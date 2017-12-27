#ifndef _SUI_HOST_INTERNAL_H
#define _SUI_HOST_INTERNAL_H
#include <chopsui/node.h>

struct native_host_impl {
	void (*run)(struct sui_host *host);
};

struct sui_host {
	struct native_host_impl *impl;
};

extern struct sui_host *active_host;

extern struct sui_type_impl native_window_type;

#endif
