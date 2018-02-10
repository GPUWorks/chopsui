#ifndef _SUI_WINDOW_WAYLAND_H
#define _SUI_WINDOW_WAYLAND_H
#include <chopsui/host.h>
#include <chopsui/node.h>
#include <chopsui/type.h>
#include <time.h>
#include <wayland-client.h>
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
	struct sui_wayland_host *host;
	struct wl_surface *wl_surface;
	struct zxdg_surface_v6 *xdg_surface;
	struct zxdg_toplevel_v6 *xdg_toplevel;
	struct wl_egl_window *egl_window;
	void *egl_surface;
	struct wl_callback *frame_callback;
	struct timespec last_frame;
	float color[3]; // TEMPORARY
	int dec;
};

extern struct sui_type_impl wayland_native_window_type;

struct sui_host *wayland_host_initialize();
void wayland_host_registry_poll(struct sui_wayland_host *host);

#endif
