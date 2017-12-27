#ifndef _SUI_WINDOW_WAYLAND_H
#define _SUI_WINDOW_WAYLAND_H
#include <wayland-client.h>
#include <chopsui/host.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include "xdg-shell-unstable-v6-client-protocol.h"
#include "gfx/egl.h"
#include "host.h"

struct sui_wayland_host {
	struct sui_host host;
	struct wl_display *wl_display;
	struct wl_registry *wl_registry;
	struct wl_compositor *wl_compositor;
	struct wl_shm *wl_shm;
	struct wl_seat *wl_seat;
	struct zxdg_shell_v6 *xdg_shell;
	struct sui_egl egl;
};

struct sui_wayland_window {
	struct sui_node *node;
	struct wl_surface *wl_surface;
	struct xdg_shell_v6_surface *xdg_surface;
	struct xdg_shell_v6_toplevel *xdg_toplevel;
};

extern struct sui_type_impl wayland_native_window_type;

struct sui_host *wayland_host_initialize();
void wayland_host_registry_poll(struct sui_wayland_host *host);

#endif
