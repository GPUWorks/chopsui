#define _POSIX_C_SOURCE 200112L
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <chopsui/host.h>
#include <chopsui/type.h>
#include <chopsui/node.h>
#include <chopsui/util/log.h>
#include <GLES2/gl2.h>
#include "gfx/egl.h"
#include "wayland.h"

static struct wl_callback_listener frame_listener;

static void surface_frame_callback(void *data, struct wl_callback *cb,
		uint32_t time) {
	struct sui_wayland_window *state = data;
	assert(state);
	wl_callback_destroy(cb);
	state->frame_callback = NULL;

	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	// TEMPORARY: TODO Render children
	long ms = (now.tv_sec - state->last_frame.tv_sec) * 1000 +
		(now.tv_nsec - state->last_frame.tv_nsec) / 1000000;
	glClearColor(state->color[0], state->color[1], state->color[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	int inc = (state->dec + 1) % 3;
	state->color[inc] += ms / 2000.0f;
	state->color[state->dec] -= ms / 2000.0f;
	if (state->color[state->dec] < 0.0f) {
		state->color[inc] = 1.0f;
		state->color[state->dec] = 0.0f;
		state->dec = inc;
	}
	// /TEMPORARY

	state->frame_callback = wl_surface_frame(state->wl_surface);
	wl_callback_add_listener(state->frame_callback, &frame_listener, state);

	assert(eglSwapBuffers(state->host->egl.display, state->egl_surface));

	state->last_frame = now;
}

static struct wl_callback_listener frame_listener = {
	.done = surface_frame_callback
};

static void xdg_surface_handle_configure(void *data, struct zxdg_surface_v6 *xdg_surface,
		uint32_t serial) {
	struct sui_wayland_window *state = data;
	assert(state && state->xdg_surface == xdg_surface);

	zxdg_surface_v6_ack_configure(xdg_surface, serial);
	// nothing else?
}

static struct zxdg_surface_v6_listener xdg_surface_listener = {
	.configure = xdg_surface_handle_configure,
};

static void xdg_toplevel_handle_configure(void *data, struct zxdg_toplevel_v6 *xdg_toplevel,
		int32_t width, int32_t height, struct wl_array *states) {
	struct sui_wayland_window *state = data;
	assert(state && state->xdg_toplevel == xdg_toplevel);
	if (width == 0 && height == 0) {
		return;
	}
	// loop over states for maximized etc?
	wl_egl_window_resize(state->egl_window, width, height, 0, 0);
	struct sui_scalar dim = {
		.type = SCALAR_INT,
		.ival = width,
	};
	node_set_attr(state->node, "width", &dim);
	dim.ival = height;
	node_set_attr(state->node, "height", &dim);
}

static void xdg_toplevel_handle_close(void *data,
		struct zxdg_toplevel_v6 *xdg_toplevel) {
	sui_log(L_DEBUG, "xdg toplevel close");
	// TODO
}

static struct zxdg_toplevel_v6_listener xdg_toplevel_listener = {
	.configure = xdg_toplevel_handle_configure,
	.close = xdg_toplevel_handle_close,
};

static void window_show(struct sui_host *_host, struct sui_node *node) {
	struct sui_wayland_host *host = (struct sui_wayland_host *)_host;
	assert(node && node_has_type(node, &wayland_native_window_type));
	struct sui_wayland_window *state =
		node_get_attr(node, "chopsui::window::`wayland_window_state`")->data;
	state->host = host;
	assert(state->wl_surface =
			wl_compositor_create_surface(host->wl_compositor));
	assert(state->xdg_surface = zxdg_shell_v6_get_xdg_surface(
			host->xdg_shell, state->wl_surface));
	assert(state->xdg_toplevel = zxdg_surface_v6_get_toplevel(
			state->xdg_surface));

	// TODO: Make app_id configurable
	zxdg_toplevel_v6_set_app_id(state->xdg_toplevel, "chopsui");
	zxdg_toplevel_v6_set_title(state->xdg_toplevel,
			node_get_attr(node, "title")->str);

	zxdg_surface_v6_add_listener(
			state->xdg_surface, &xdg_surface_listener, state);
	zxdg_toplevel_v6_add_listener(
			state->xdg_toplevel, &xdg_toplevel_listener, state);

	wl_surface_commit(state->wl_surface);

	assert(state->egl_window = wl_egl_window_create(state->wl_surface,
			node_get_attr(node, "width")->ival,
			node_get_attr(node, "height")->ival));
	assert(state->egl_surface = sui_egl_create_surface(
			&host->egl, state->egl_window));

	wl_display_roundtrip(host->wl_display);

	assert(eglMakeCurrent(
				host->egl.display,
				state->egl_surface,
				state->egl_surface,
				host->egl.context));

	glViewport(0, 0, node_get_attr(node, "width")->ival,
			node_get_attr(node, "height")->ival);
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	state->color[0] = 1.0;
	state->color[1] = 0;
	state->color[2] = 0;

	state->frame_callback = wl_surface_frame(state->wl_surface);
	wl_callback_add_listener(state->frame_callback, &frame_listener, state);

	assert(eglSwapBuffers(host->egl.display, state->egl_surface));
}

static struct sui_window_impl wayland_window_impl = {
	.show = window_show
};

static void window_init(struct sui_node *node) {
	struct sui_wayland_window *state =
		calloc(1, sizeof(struct sui_wayland_window));
	state->node = node;
	struct sui_scalar scalar = {
		.type = SCALAR_VOID,
		.data = state,
	};
	node_set_attr(node, "chopsui::window::`wayland_window_state`", &scalar);
	scalar.data = &wayland_window_impl;
	node_set_attr(node, "chopsui::window::`window_impl`", &scalar);
}

struct sui_type_impl wayland_native_window_type = {
	.init = window_init
};
