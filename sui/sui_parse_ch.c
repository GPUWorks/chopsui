#include <stdint.h>
#include <ctype.h>
#include <chopsui/parser.h>
#include <chopsui/util/list.h>
#include "subparser.h"

int sui_parse_ch(struct parser_state *state, uint32_t ch) {
	struct subparser_state *subp;
	subp = list_peek(state->parsers);

	if ((subp->flags & FLAG_WAIT)) {
		if (ch == subp->wait) {
			subp->flags &= ~FLAG_WAIT;
		}
		return PARSER_SKIP;
	}

	if ((subp->flags & FLAG_WHITESPACE)) {
		if (!isspace(ch) || ch == '\n') {
			subp->flags &= ~FLAG_WHITESPACE;
			return PARSER_CONTINUE;
		}
		return PARSER_SKIP;
	}

	if (!(subp->flags & FLAG_COMMENTS) && ch == '#') {
		subp->wait = '\n';
		subp->flags |= FLAG_WAIT;
		return PARSER_SKIP;
	}

	return PARSER_CONTINUE;
}
