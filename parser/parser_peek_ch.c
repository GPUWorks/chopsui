#include <stdint.h>
#include <chopsui/parser.h>

uint32_t parser_peek_ch(struct parser_state *state) {
	return state->pending[state->pending_tail];
}
