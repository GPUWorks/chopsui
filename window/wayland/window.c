#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <wayland-client.h>
#include <chopsui/type.h>
#include <chopsui/node.h>
#include <chopsui/util/log.h>
#include <chopsui/window.h>
#include "wayland.h"

static void wayland_window_run(struct sui_node *node) {
	assert(node_has_type(node, &wayland_native_window_type));
	struct wayland_window_state *state =
		node_get_attr(node, "chopsui::window::`wayland_window_state`")->data;
	assert(state->wl_display = wl_display_connect(NULL));
	wayland_native_registry_poll(state);
}

struct native_window_impl native_window_impl = {
	.run = wayland_window_run
};

static void window_init(struct sui_node *node) {
	struct sui_scalar scalar = {
		.type = SCALAR_VOID,
		.data = &native_window_impl
	};
	sui_log(L_DEBUG, "Initializing Wayland window");
	node_set_attr(node, "chopsui::window::`native_window_impl`", &scalar);

	struct wayland_window_state *state =
		calloc(1, sizeof(struct wayland_window_state));
	scalar.data = state;
	node_set_attr(node, "chopsui::window::`wayland_window_state`", &scalar);
}

struct sui_type_impl wayland_native_window_type = {
	.init = window_init,
};
