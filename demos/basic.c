#include <assert.h>
#include <stdio.h>
#include <chopsui/css.h>
#include <chopsui/host.h>
#include <chopsui/node.h>
#include <chopsui/sui.h>
#include <chopsui/util/errors.h>

int main() {
	struct sui_host *host = sui_host_initialize();
	struct sui_node *window = sui_parse(
			"window title='sui demo'\n"
			"\tstyle src='style.css'\n"
			"\t\tbox", NULL);
	struct sui_node *box = node_find_descendant(
			window, selector_parse("box"));
	assert(box);
	struct style_context *ctx = style_get_context(box);
	assert(ctx);
	sui_host_show(host, window);
	sui_host_run(host);
	return 0;
}
