#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <wayland-client.h>
#include <chopsui/host.h>
#include <chopsui/type.h>
#include <chopsui/node.h>
#include <chopsui/util/log.h>
#include "gfx/egl.h"
#include "wayland.h"

static void window_init(struct sui_node *node) {
	struct sui_wayland_window *state =
		calloc(1, sizeof(struct sui_wayland_window));
	state->node = node;
	struct sui_scalar scalar = {
		.type = SCALAR_VOID,
		.data = state,
	};
	node_set_attr(node, "chopsui::window::`wayland_window_state`", &scalar);
	
	// TODO: Create wayland surface et al
}

struct sui_type_impl wayland_native_window_type = {
	.init = window_init
};
