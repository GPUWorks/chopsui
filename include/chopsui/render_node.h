#ifndef _CHOPSUI_RENDER_NODE_H
#define _CHOPSUI_RENDER_NODE_H
#include <stdbool.h>
#include <stdint.h>

extern struct sui_type_impl render_node_impl;

/**
 * The render node interface is a subset of the general node interface which
 * provides tree operations which are scoped to subset of the tree which is
 * renderable.
 */
struct render_node_impl {
	/**
	 * When a descendant of a renderable node is added, this function is called
	 * on the first ancestor of that child which implements render_node.
	 *
	 * Return false to prevent the child from being added and raise an error.
	 */
	bool (*child)(struct sui_node *node, struct sui_node *child);
	/**
	 * Invoked when a renderable child is removed from this node.
	 */
	void (*child_removed)(struct sui_node *node, struct sui_node *child);
	/**
	 * When this is called, the GL context has been made current and you are
	 * expected to render your node and any of your renderable children.
	 */
	void (*render)(struct sui_node *node, uint32_t width, uint32_t height);
};

/**
 * Initializes a render node and adds it to the render tree.
 */
void render_node_init(struct sui_node *node, struct render_node_impl *impl);

/**
 * Returns the first ancestor which implements render_node.
 */
struct sui_node *render_node_get_renderable_ancestor(struct sui_node *node);

/**
 * Invokes the `render` function on a renderable node's render_node_impl.
 *
 * Aborts if the specified node is not a render node.
 */
void render_node_render(struct sui_node *node, uint32_t width, uint32_t height);

#endif
