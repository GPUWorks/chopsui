#include <assert.h>
#include <chopsui/host.h>
#include <chopsui/render_node.h>
#include <chopsui/type.h>
#include <stdlib.h>
#include <koio.h>
#include "wayland/wayland.h"
#include "host.h"

struct sui_host *active_host;

typedef struct sui_host *(*host_init_func_t)();

static host_init_func_t detect_native_host() {
	if (getenv("WAYLAND_DISPLAY")) {
		type_impl_register("window", &wayland_native_window_type);
		return wayland_host_initialize;
	} else {
		fprintf(stderr, "Unable to choose a suitable host.\n");
		assert(0);
	}
}

struct sui_host *sui_host_initialize(const char *argv_0) {
	type_impl_register("window", &native_window_type);
	type_impl_register("window", &render_node_impl);
	host_init_func_t init_host = detect_native_host();

	const char *config_home = getenv("XDG_CONFIG_HOME");
	const char *home = getenv("HOME");
	if (!config_home && home) {
		size_t l = snprintf(NULL, 0,
				"%s/.config/chopsui/%s/koio", home, argv_0);
		char *path = malloc(l + 1);
		if (path) {
			snprintf(path, l + 1,
					"%s/.config/chopsui/%s/koio", home, argv_0);
			ko_add_alias("//", path);
		}
		free(path);
	} else if (config_home) {
		size_t l = snprintf(NULL, 0,
				"%s/chopsui/%s/koio", config_home, argv_0);
		char *path = malloc(l + 1);
		if (path) {
			snprintf(path, l + 1,
					"%s/chopsui/%s/koio", config_home, argv_0);
			ko_add_alias("//", path);
		}
		free(path);
	}

	style_type_register();
	
	return active_host = init_host();
}

void sui_host_run(struct sui_host *host) {
	host->impl->run(host);
}

void sui_host_show(struct sui_host *host, struct sui_node *window) {
	const struct sui_scalar *_impl = node_get_attr(window,
			"chopsui::window::`window_impl`");
	struct sui_window_impl *impl = _impl->data;
	impl->show(host, window);
}
