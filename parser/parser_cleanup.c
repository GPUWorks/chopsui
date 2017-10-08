#include <stddef.h>
#include <stdlib.h>
#include "chopsui/util/list.h"
#include "chopsui/parser.h"

void parser_cleanup(struct parser_state *state) {
	parser_log(state, "Terminating parser via parser_cleanup");
	if (!state->parsers) {
		return;
	}
	while (state->parsers->length) {
		parser_pop(state);
	}
	list_free(state->parsers);
}
