#include <stdio.h>
#include <chopsui/window.h>
#include <chopsui/sui.h>

int main() {
	register_window_types();
	struct sui_node *win = sui_parse("window title='sui demo'", NULL);
	window_run(win);
	return 0;
}
