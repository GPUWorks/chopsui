#ifndef _SET_H
#define _SET_H
#include <stdbool.h>
#include <stddef.h>

typedef struct {
	unsigned int key;
	void *next;
} sui_set_entry_t;

typedef struct {
	unsigned int (*hash)(const void *);
	sui_set_entry_t **buckets;
	size_t bucket_count;
} sui_set_t;

sui_set_t *set_create(size_t buckets, unsigned int (*hash_function)(const void *));
void set_free(sui_set_t *set);
void set_add(sui_set_t *set, const void *key);
void set_del(sui_set_t *set, const void *key);
bool set_contains(sui_set_t *set, const void *key);

#endif
