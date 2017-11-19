#ifndef _SUI_NODE_H
#define _SUI_NODE_H
#include <stdbool.h>
#include <chopsui/util/hashtable.h>
#include <chopsui/util/list.h>
#include <chopsui/util/set.h>
#include <chopsui/scalars.h>
#include <chopsui/type.h>
#include <chopsui/css.h>

struct sui_type;

struct sui_node {
	struct sui_node *parent;
	struct sui_type *sui_type;
	char *type;
	char *id;
	sui_set_t *classes;          // char *
	sui_list_t *children;        // struct sui_node
	sui_hashtable_t *attributes; // char *, char *
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
struct sui_node *node_find_ancestor(struct sui_node *node,
		struct selector *selector);
/**
 * Invokes the provided iter function with each anscestor of the node that
 * matches the provided CSS selector. Return false to stop.
 */
void node_find_ancestors(struct sui_node *node, struct selector *selector,
		bool (*iter)(struct sui_node *node, void *data), void *data);

/**
 * Finds the first descendant of node that matches the provided CSS selector.
 * Depth first.
 */
struct sui_node *node_find_descendant(struct sui_node *node,
		struct selector *selector);
/**
 * Invokes the provided iter function with each descendant of node that matches
 * the provided CSS selector, depth first. Return false to stop.
 */
void node_find_descendants(struct sui_node *node, struct selector *selector,
		bool (*iter)(struct sui_node *node, void *data), void *data);

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

/**
 * Adds the given sui_type_impl to the node's type. An example of where this is
 * appropriate could be when a node is added to a container; the container might
 * add a container-specific sui_type_impl that provides attributes used by the
 * container to lay out its children. Situations where a particular kind of node
 * will always have some types is better suited to type_impl_add (see type.h).
 */
void node_type_add_impl(struct sui_node *node, const struct sui_type_impl *impl);

/**
 * Removes the given sui_type_impl from the node's type. This would be
 * appropriate, for example, when removing a type from a container implementing
 * the pattern described in the documentation of node_type_add_impl.
 */
void node_type_remove_impl(struct sui_node *node, const struct sui_type_impl *impl);

/**
 * Returns true if this node implements the given type.
 */
bool node_has_type(struct sui_node *node, const struct sui_type_impl *impl);

#endif
