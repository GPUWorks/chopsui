#define _XOPEN_SOURCE 500
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <chopsui/util/string.h>
#include <chopsui/node.h>
#include <chopsui/parser.h>
#include <chopsui/scalars.h>
#include "subparser.h"

struct attr_state {
	char *key;
	struct sui_scalar *val;
	void (*commit)(void *, const char *, void *);
	void *state;
	struct parser_state *pstate;
};

static void commit_key(void *_state, const char *str, enum string_type t) {
	// TODO: validate characters used
	struct attr_state *state = _state;
	if (str) {
		parser_log(state->pstate, "key: '%s'", str);
		state->key = strdup(str);
	}
}

static void commit_val(void *_state, const char *str, enum string_type type) {
	struct attr_state *state = _state;
	assert(!state->val);
	if (!str) {
		parser_error(state->pstate, "Unspecified attribute value");
	}
	parser_log(state->pstate, "value: '%s'", str);
	struct sui_scalar value;
	if (type == STRING_LITERAL) {
		if (!scalar_parse(str, &value)) {
			parser_error(state->pstate, "Unable to parse attribute value");
		}
	} else {
		value.type = SCALAR_STR;
		value.str = strdup(str);
	}
	state->val = malloc(sizeof(struct sui_scalar));
	memcpy(state->val, &value, sizeof(struct sui_scalar));
	parser_pop(state->pstate);
	// TODO: validate scalar type is acceptable (and normalize?)
}

static void attr_state_free(void *_state) {
	struct attr_state *state = _state;
	if (!state) return;
	if (state->key && state->commit) {
		if (!state->val) {
			state->val = calloc(1, sizeof(struct sui_scalar));
			state->val->type = SCALAR_EMPTY;
		}
		parser_log(state->pstate, "commit attr %s", state->key);
		state->commit(state->state, state->key, state->val);
	}
	free(state->key);
	free(state);
}

void parse_attr(struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct attr_state *state = subparser->state;

	if (isspace(ch) && ch != '\n') {
		return;
	} else if (ch == '=') {
		if (!state->key) {
			parser_error(pstate, "Cannot specify attribute without key");
		} else {
			push_string_parser(pstate, state, commit_val);
		}
	} else if (!state->key) {
		push_string_parser(pstate, state, commit_key);
		parser_push_ch(pstate, ch);
	} else {
		parser_push_ch(pstate, ch);
		parser_pop(pstate);
	}
}

struct subparser_state *push_attr_parser(struct parser_state *pstate,
		void *state, void (*commit)(void *, const char *, void *)) {
	struct subparser_state *subparser = parser_push(
			pstate, parse_attr, "sui:attr");
	subparser->destructor = attr_state_free;
	struct attr_state *sstate = calloc(sizeof(struct attr_state), 1);
	sstate->state = state;
	sstate->pstate = pstate;
	sstate->commit = commit;
	subparser->state = sstate;
	return subparser;
}
