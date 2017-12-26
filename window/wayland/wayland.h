#ifndef _SUI_WINDOW_WAYLAND_H
#define _SUI_WINDOW_WAYLAND_H
#include <wayland-client.h>
#include <chopsui/node.h>
#include <chopsui/type.h>

struct wayland_window_state {
	struct sui_node *node;
	struct wl_display *wl_display;
	struct wl_registry *wl_registry;
};

extern struct sui_type_impl wayland_native_window_type;

void wayland_native_registry_poll(struct wayland_window_state *state);

#endif
