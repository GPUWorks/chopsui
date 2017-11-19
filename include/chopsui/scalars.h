#ifndef _SUI_SCALARS_H
#define _SUI_SCALARS_H
#include <stdint.h>
#include <stdbool.h>

// Note: a scalar cannot be multiple types. This is a bitfield for the purpose
// of expressing a set of valid types.
enum scalar_type {
	SCALAR_EMPTY   = 0,
	SCALAR_INT     = 1 << 1,
	SCALAR_FLOAT   = 1 << 2,
	SCALAR_DPI     = 1 << 3,
	SCALAR_EM      = 1 << 4,
	SCALAR_REM     = 1 << 5,
	SCALAR_PX      = 1 << 6,
	SCALAR_PERCENT = 1 << 7,
	SCALAR_DEG     = 1 << 8,
	SCALAR_RAD     = 1 << 9,
	SCALAR_GRAD    = 1 << 10,
	SCALAR_MS      = 1 << 11,
	SCALAR_S       = 1 << 12,
	SCALAR_HZ      = 1 << 13,
	SCALAR_KHZ     = 1 << 14,
	SCALAR_COLOR   = 1 << 15,
	SCALAR_BOOL    = 1 << 16,
	SCALAR_STR     = 1 << 17,
	SCALAR_VOID    = 1 << 18,

	SCALAR_LENGTH =
		SCALAR_INT | SCALAR_FLOAT | SCALAR_EM | SCALAR_REM | SCALAR_PX, 
	SCALAR_ROTATION = SCALAR_DEG | SCALAR_RAD | SCALAR_GRAD,
	SCALAR_TIME = SCALAR_S | SCALAR_MS,
	SCALAR_FREQ = SCALAR_HZ | SCALAR_KHZ,
	SCALAR_ANY     = -1,
};

struct sui_scalar {
	enum scalar_type type;
	union {
		bool bval;
		double fval;
		long ival;
		unsigned long uval;
		struct {
			uint8_t a, b, g, r;
		};
		char *str;
		void *data;
	};
};

/**
 * Parses a CSS scalar string into a sui_scalar_t. Note that this does NOT
 * handle SCALAR_STR or SCALAR_VOID.
 */
bool scalar_parse(const char *s, struct sui_scalar *scalar);

/**
 * Parses a CSS color string into a uint32_t
 */
bool color_parse(const char *str, uint32_t *val);

struct display_info {
	double font_size;
	double root_font_size;
};

/**
 * Normalizes the units of a sui_scalar, optionally normalizing pixels with
 * the provided display information.
 *
 * The provided scalar will be reduced to the following units:
 *
 * - SCALAR_INT
 * - SCALAR_FLOAT
 * - SCALAR_DPI
 * - SCALAR_PX
 * - SCALAR_PERCENT
 * - SCALAR_RAD
 * - SCALAR_S
 * - SCALAR_HZ
 * - SCALAR_COLOR
 */
void scalar_normalize(struct sui_scalar *scalar, struct display_info *info);

#endif
