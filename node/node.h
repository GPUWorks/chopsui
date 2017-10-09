#ifndef _NODE_INTERNAL_H
#define _NODE_INTERNAL_H
#include <stdbool.h>
#include <chopsui/node.h>
#include <chopsui/css.h>

bool node_matches_selector(struct sui_node *node, struct selector *selector);

#endif
