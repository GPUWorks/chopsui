#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "chopsui/css.h"
#include "chopsui/parser.h"
#include "chopsui/util/list.h"
#include "chopsui/util/unicode.h"
#include "chopsui/util/errors.h"
#include "subparser.h"

struct stylesheet *css_parse(const char *source, errors_t **errs) {
	struct stylesheet *css = calloc(1, sizeof(struct stylesheet));
	css->rules = list_create();
	css->media_rules = list_create();
	css->keyframes = list_create();

	struct parser_state state;
	memset(&state, 0, sizeof(state));
	state.errs = errs;
	state.data = css;
	parser_init(&state, css_parse_ch);
	parser_push(&state, parse_document, "css:document");

	while (*source) {
		uint32_t ch = utf8_decode(&source);
		parse_ch(&state, ch);
	}

	parser_cleanup(&state);
	return css;
}
