#include <stdint.h>
#include <chopsui/parser.h>

void parser_push_ch(struct parser_state *state, uint32_t ch) {
	state->pending[state->pending_head++] = ch;
	state->pending_head %= sizeof(state->pending) / sizeof(uint32_t);
	if (ch == '\n') {
		--state->lineno;
		state->colno = 1;
	} else {
		--state->colno;
	}
}
