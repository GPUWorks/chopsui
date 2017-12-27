#include <stdio.h>
#include <chopsui/host.h>
#include <chopsui/sui.h>

int main() {
	struct sui_host *host = sui_host_initialize();
	// TODO: We probably want a window_show or something so we can have windows
	// in memory that are not running on the host
	sui_parse("window title='sui demo'", NULL);
	sui_host_run(host);
	return 0;
}
