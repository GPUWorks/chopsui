#include <stdio.h>
#include <chopsui/host.h>
#include <chopsui/sui.h>

int main() {
	struct sui_host *host = sui_host_initialize();
	struct sui_node *window = sui_parse("window title='sui demo'", NULL);
	sui_host_show(host, window);
	sui_host_run(host);
	return 0;
}
