#ifndef _SUI_NODE_H
#define _SUI_NODE_H
#include <stdbool.h>
#include <chopsui/util/hashtable.h>
#include <chopsui/util/list.h>
#include <chopsui/util/set.h>
#include <chopsui/scalars.h>
#include <chopsui/type.h>
#include <chopsui/css.h>

struct sui_node {
	struct sui_node *parent;

	char *type;
	char *id;
	set_t *classes;          // char *
	list_t *children;        // struct sui_node
	hashtable_t *attributes; // char *, char *

	void *impl_state;
	struct sui_type_impl *impl;
};

/**
 * Returns the value of the specified attribute.
 */
const struct sui_scalar *node_get_attr(struct sui_node *node, const char *key);
/**
 * Sets the specified attribute to the specified value.
 */
void node_set_attr(struct sui_node *node, const char *key,
		const struct sui_scalar *value);

/**
 * Checks if the specified node has the specified class.
 */
bool node_has_class(struct sui_node *node, const char *name);
/**
 * Adds the specified class to the specified node.
 */
void node_add_class(struct sui_node *node, const char *name);
/**
 * Removes the specified class to the specified node.
 */
void node_remove_class(struct sui_node *node, const char *name);

/**
 * Frees this node and all of its children. Detaches it from the parent first if
 * necessary.
 */
void node_free(struct sui_node *node);

/**
 * Finds the first ancestor of node that matches the provided CSS selector.
 */
struct sui_node node_find_ancestor(struct sui_node *node, struct selector *selector);
/**
 * Invokes the provided iter function with each anscestor of the node that
 * matches the provided CSS selector.
 */
void node_iter_ancestors(struct sui_node *node, struct selector *selector,
		void (*iter)(struct sui_node *node));

/**
 * Finds the first descendant of node that matches the provided CSS selector.
 * Depth first.
 */
struct sui_node *node_find_descendant(struct sui_node *node, struct selector *selector);
/**
 * Invokes the provided iter function with each descendant of node that matches
 * the provided CSS selector, depth first.
 */
void node_iter_descendants(struct sui_node *node, struct selector *selector,
		void (*iter)(struct sui_node *node));

/**
 * Adds the node to the end of the parent's children. Returns the number of
 * nodes inserted - could be 0 if the child already has a parent, or is NULL.
 */
int node_append_child(struct sui_node *parent, struct sui_node *child);
/**
 * Inserts the node in the parent's children at the specified index. Returns the
 * number of nodes inserted - could be 0 if the child already has a parent, or
 * is NULL.
 */
int node_insert_child(struct sui_node *parent, struct sui_node *child, size_t index);

/**
 * Detaches this node from its parent.
 */
void node_detach(struct sui_node *child);

#endif
