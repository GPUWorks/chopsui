#ifndef _SUI_WINDOW_WAYLAND_H
#define _SUI_WINDOW_WAYLAND_H
#include <wayland-client.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include "xdg-shell-unstable-v6-client-protocol.h"
#include "gfx/egl.h"

struct wayland_window_state {
	struct sui_node *node;

	struct wl_display *wl_display;
	struct wl_registry *wl_registry;
	struct wl_compositor *wl_compositor;
	struct wl_shm *wl_shm;
	struct wl_seat *wl_seat;
	struct zxdg_shell_v6 *xdg_shell;

	struct sui_egl egl;
};

extern struct sui_type_impl wayland_native_window_type;

void wayland_native_registry_poll(struct wayland_window_state *state);

#endif
