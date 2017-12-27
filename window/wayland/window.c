#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <wayland-client.h>
#include <chopsui/type.h>
#include <chopsui/node.h>
#include <chopsui/util/log.h>
#include <chopsui/window.h>
#include "gfx/egl.h"
#include "wayland.h"

static void native_window_create(struct wayland_window_state *state) {
	sui_log(L_DEBUG, "title=%s width=%ld height=%ld",
			node_get_attr(state->node, "title")->str,
			node_get_attr(state->node, "width")->ival,
			node_get_attr(state->node, "height")->ival);
}

static void wayland_window_run(struct sui_node *node) {
	assert(node_has_type(node, &wayland_native_window_type));
	// TODO: Move most of this code into the native host abstraction
	struct wayland_window_state *state =
		node_get_attr(node, "chopsui::window::`wayland_window_state`")->data;
	assert(state->wl_display = wl_display_connect(NULL));
	wayland_native_registry_poll(state);
	sui_egl_init(&state->egl, EGL_PLATFORM_WAYLAND_EXT,
		state->wl_display, NULL, WL_SHM_FORMAT_ARGB8888);
	assert(state->wl_compositor && state->xdg_shell);
	native_window_create(state);
	sui_log(L_DEBUG, "Entering Wayland event loop");
	while (wl_display_dispatch(state->wl_display) != -1) {
		// no-op
	}
	sui_log(L_DEBUG, "Wayland event loop exited");
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
	state->node = node;
	node_set_attr(node, "chopsui::window::`wayland_window_state`", &scalar);
}

struct sui_type_impl wayland_native_window_type = {
	.init = window_init
};
