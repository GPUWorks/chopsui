#include <assert.h>
#include <stdlib.h>
#include <chopsui/host.h>
#include <chopsui/util/log.h>
#include <wayland-client.h>
#include "wayland.h"
#include "gfx/egl.h"

static void wayland_host_run(struct sui_host *_host) {
	struct sui_wayland_host *host = (struct sui_wayland_host *)_host;
	sui_log(L_DEBUG, "Starting Wayland event loop");
	while (wl_display_dispatch(host->wl_display) != -1) {
		// no-op
	}
	sui_log(L_DEBUG, "Wayland event loop exited");
	wl_display_disconnect(host->wl_display);
	free(host);
}

static struct native_host_impl host_impl = {
	.run = wayland_host_run
};

struct sui_host *wayland_host_initialize() {
	sui_log(L_DEBUG, "Initializing Wayland host");
	struct sui_wayland_host *host = calloc(1, sizeof(struct sui_wayland_host));
	host->host.impl = &host_impl;
	assert(host->wl_display = wl_display_connect(NULL));
	wayland_host_registry_poll(host);
	sui_egl_init(&host->egl, EGL_PLATFORM_WAYLAND_EXT,
		host->wl_display, NULL, WL_SHM_FORMAT_ARGB8888);
	assert(host->wl_compositor && host->xdg_shell);
	return (struct sui_host *)host;
}
