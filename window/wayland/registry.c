#include <assert.h>
#include <wayland-client.h>
#include <chopsui/util/log.h>
#include "wayland.h"
#include "xdg-shell-unstable-v6-client-protocol.h"

static void xdg_shell_handle_ping(void *data, struct zxdg_shell_v6 *shell,
		uint32_t serial) {
	zxdg_shell_v6_pong(shell, serial);
}

static const struct zxdg_shell_v6_listener xdg_shell_listener = {
	xdg_shell_handle_ping,
};

static void registry_global(void *data, struct wl_registry *registry,
		uint32_t name, const char *interface, uint32_t version) {
	sui_log(L_DEBUG, "Global add: %d %s version %d",
			name, interface, version);
	struct wayland_window_state *state = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		state->wl_compositor = wl_registry_bind(registry, name,
				&wl_compositor_interface, version);
	} else if (strcmp(interface, zxdg_shell_v6_interface.name) == 0) {
		state->xdg_shell = wl_registry_bind(registry, name,
				&zxdg_shell_v6_interface, version);
		zxdg_shell_v6_add_listener(state->xdg_shell, &xdg_shell_listener, NULL);
	} else if (strcmp(interface, wl_shm_interface.name) == 0) {
		state->wl_shm = wl_registry_bind(registry, name,
				&wl_shm_interface, version);
	} else if (strcmp(interface, wl_seat_interface.name) == 0) {
		state->wl_seat = wl_registry_bind(registry, name,
				&wl_seat_interface, version);
	}
}

static void registry_global_remove(void *data, struct wl_registry *registry,
		uint32_t name) {
	sui_log(L_DEBUG, "Global remove: %d", name);
}

static const struct wl_registry_listener registry_listener = {
	.global = registry_global,
	.global_remove = registry_global_remove
};

void wayland_native_registry_poll(struct wayland_window_state *state) {
	assert(state->wl_registry = wl_display_get_registry(state->wl_display));
	wl_registry_add_listener(state->wl_registry, &registry_listener, state);
	wl_display_dispatch(state->wl_display);
	wl_display_roundtrip(state->wl_display);
}
