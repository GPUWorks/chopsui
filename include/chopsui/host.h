#ifndef _SUI_HOST_H
#define _SUI_HOST_H

struct sui_host;
struct sui_node;

/**
 * Initializes and returns a platform-specific chopsui host. This will register
 * a number of type, notably `window`, which is backed by the most appropriate
 * native window implementation.
 *
 * The host is a global, you cannot have several of them at once.
 *
 * `name` should be the name of your application, suitable for filesystem paths.
 * This is used for config files, etc.
 */
struct sui_host *sui_host_initialize(const char *name);

/**
 * Runs the host. This does not return until you call sui_host_terminate.
 */
void sui_host_run(struct sui_host *host);

/**
 * Shows a window on a host.
 */
void sui_host_show(struct sui_host *host, struct sui_node *window);

/**
 * Terminates the host. This closes any open resources, destroys native windows
 * (and their children), etc. sui_host_run will return after this is called and
 * the host will no longer be valid.
 */
void sui_host_terminate(struct sui_host *host);

#endif
