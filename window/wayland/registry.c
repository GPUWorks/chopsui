#include <assert.h>
#include <wayland-client.h>
#include <chopsui/util/log.h>
#include "wayland.h"

static void registry_global(void *data, struct wl_registry *registry,
		uint32_t name, const char *interface, uint32_t version) {
	sui_log(L_DEBUG, "Global add: %d %s version %d",
			name, interface, version);
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
