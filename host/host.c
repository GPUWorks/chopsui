#include <chopsui/host.h>
#include <chopsui/type.h>
#include "wayland/wayland.h"
#include "host.h"

// Active host global
struct sui_host *active_host;

struct sui_host *sui_host_initialize() {
	type_impl_register("window", &native_window_type);
	// TODO: detect platform and register only the most appropriate native
	// window type
	type_impl_register("window", &wayland_native_window_type);
	return active_host = wayland_host_initialize();
}

void sui_host_run(struct sui_host *host) {
	host->impl->run(host);
}
