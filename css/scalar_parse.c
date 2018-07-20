#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <chopsui/scalars.h>

bool scalar_parse(const char *s, struct sui_scalar *scalar, uint32_t types) {
	if ((types & SCALAR_BOOL) && strcmp(s, "true") == 0) {
		scalar->type = SCALAR_BOOL;
		scalar->bval = true;
		return true;
	}
	if ((types & SCALAR_BOOL) && strcmp(s, "false") == 0) {
		scalar->type = SCALAR_BOOL;
		scalar->bval = false;
		return true;
	}

	char *unit;
	if (strchr(s, '.')) {
		scalar->fval = strtod(s, &unit);
		scalar->type = SCALAR_FLOAT;
	} else {
		scalar->ival = strtol(s, &unit, 10);
		scalar->type = SCALAR_INT;
	}
	if (unit == s) {
		if ((types & SCALAR_COLOR)) {
			uint32_t color;
			bool valid = color_parse(s, &color);
			scalar->uval = color;
			scalar->type = SCALAR_COLOR;
			return valid;
		}
		if ((types & SCALAR_STR) && *s) {
			scalar->str = strdup(s);
			scalar->type = SCALAR_STR;
			return true;
		}
		return false;
	}
	if (!*unit) {
		// Is an int or a float with no unit
		return !!((types & (SCALAR_FLOAT | SCALAR_INT)));
	}
	struct type_map {
		char *str;
		enum scalar_type base;
		enum scalar_type type;
	};
	struct type_map maps[] = {
		{ "dpi", SCALAR_FLOAT, SCALAR_DPI },
		{ "em", SCALAR_FLOAT, SCALAR_EM },
		{ "rem", SCALAR_FLOAT, SCALAR_REM },
		{ "px", SCALAR_INT, SCALAR_PX },
		{ "%", SCALAR_FLOAT, SCALAR_PERCENT },
		{ "deg", SCALAR_FLOAT, SCALAR_DEG },
		{ "rad", SCALAR_FLOAT, SCALAR_RAD },
		{ "grad", SCALAR_FLOAT, SCALAR_GRAD },
		{ "ms", SCALAR_FLOAT, SCALAR_MS },
		{ "s", SCALAR_FLOAT, SCALAR_S },
		{ "hz", SCALAR_FLOAT, SCALAR_HZ },
		{ "khz", SCALAR_FLOAT, SCALAR_KHZ },
	};
	for (size_t i = 0; i < sizeof(maps) / sizeof(struct type_map); ++i) {
		if (strcasecmp(maps[i].str, unit) == 0) {
			if (scalar->type == SCALAR_FLOAT && maps[i].base == SCALAR_INT) {
				// Not allowed to demote float to int
				return false;
			}
			if (scalar->type == SCALAR_INT && maps[i].base == SCALAR_FLOAT) {
				// Promote int to float
				scalar->fval = (float)scalar->ival;
			}
			scalar->type = maps[i].type;
			return !!(scalar->type & types);
		}
	}
	// Invalid unit
	return false;
}
