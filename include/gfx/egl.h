#ifndef SUI_EGL_H
#define SUI_EGL_H
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <stdbool.h>
#include <wayland-client.h>

struct sui_egl {
	EGLDisplay display;
	EGLConfig config;
	EGLContext context;

	const char *egl_exts;
	const char *gl_exts;

	struct wl_display *wl_display;
};

/**
 *  Initializes an egl context for the given platform and remote display.
 * Will attempt to load all possibly required api functions.
 */
bool sui_egl_init(struct sui_egl *egl, EGLenum platform, void *remote_display,
	EGLint *config_attribs, EGLint visual_id);

/**
 * Frees all related egl resources, makes the context not-current and
 * unbinds a bound wayland display.
 */
void sui_egl_finish(struct sui_egl *egl);

/**
 * Returns a surface for the given native window
 * The window must match the remote display the sui_egl was created with.
 */
EGLSurface sui_egl_create_surface(struct sui_egl *egl, void *window);

/**
 * Binds the given display to the egl instance.
 * This will allow clients to create egl surfaces from wayland ones and render to it.
 */
bool sui_egl_bind_display(struct sui_egl *egl, struct wl_display *local_display);

/**
 * Returns a string for the last error ocurred with egl.
 */
const char *egl_error(void);

#endif
