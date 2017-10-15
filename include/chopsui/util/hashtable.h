#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <stdbool.h>
#include <stddef.h>

typedef struct {
	unsigned int key;
	void *value;
	void *next;
} sui_hashtable_entry_t;

typedef struct {
	unsigned int (*hash)(const void *);
	sui_hashtable_entry_t **buckets;
	size_t bucket_count;
} sui_hashtable_t;

sui_hashtable_t *hashtable_create(size_t buckets, unsigned int (*hash_function)(const void *));
void hashtable_free(sui_hashtable_t *table);
void *hashtable_get(sui_hashtable_t *table, const void *key);
void *hashtable_set(sui_hashtable_t *table, const void *key, void *value);
void *hashtable_del(sui_hashtable_t *table, const void *key);
bool hashtable_contains(sui_hashtable_t *table, const void *key);
void hashtable_iter(sui_hashtable_t *table, void (*iter)(void *item, void *state), void *state);

#endif
