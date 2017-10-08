#ifndef _SUI_SUI_H
#define _SUI_SUI_H
#include <stdio.h>
#include "chopsui/node.h"
#include "chopsui/util/errors.h"

struct sui_node *sui_parse(const char *source, errors_t **errs);
struct sui_node *sui_load(FILE *source, errors_t **errs);

#endif
