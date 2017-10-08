#include <stdint.h>
#include <chopsui/parser.h>

uint32_t parser_pop_ch(struct parser_state *state) {
	uint32_t ch = state->pending[state->pending_tail++];
	state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
	return ch;
}
