#ifndef _SUI_HOST_H
#define _SUI_HOST_H

struct sui_host;

/**
 * Initializes and returns a platform-specific chopsui host. This will register
 * a number of type, notably `window`, which is backed by the most appropriate
 * native window implementation.
 *
 * The host is a global, you cannot have several of them at once.
 */ // TODO: Do we want to make the type system host-local? Food for thought...
struct sui_host *sui_host_initialize();

/**
 * Runs the host. This does not return until you call sui_host_terminate.
 */
void sui_host_run(struct sui_host *host);

/**
 * Terminates the host. This closes any open resources, destroys native windows
 * (and their children), etc. sui_host_run will return after this is called and
 * the host will no longer be valid.
 */
void sui_host_terminate(struct sui_host *host);

#endif
