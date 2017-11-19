#ifndef _SUI_WINDOW_H
#define _SUI_WINDOW_H
#include <chopsui/node.h>

struct native_window_impl {
	void (*run)(struct sui_node *window);
};

/**
 * Call this before using native windows. Note that stdui will call this
 * automatically on initialization if you intend to use stdui.
 */
void register_window_types();
/**
 * Runs this window. Returns when the window is closed.
 */
void window_run(struct sui_node *node);

/** Built-in native window implementations */
extern struct sui_type_impl wayland_native_window_type;

#endif
