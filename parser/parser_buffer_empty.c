#include <stdint.h>
#include <chopsui/parser.h>

bool parser_buffer_empty(struct parser_state *state) {
	return state->pending_tail == state->pending_head;
}
