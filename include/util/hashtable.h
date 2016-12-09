#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdbool.h>

typedef struct {
	unsigned int key;
	void *value;
	void *next;
} hashtable_entry_t;

typedef struct {
	unsigned int (*hash)(const void *);
	hashtable_entry_t **buckets;
	size_t bucket_count;
} hashtable_t;

hashtable_t *hashtable_create(size_t buckets, unsigned int (*hash_function)(const void *));
void hashtable_destroy(hashtable_t *table);
void *hashtable_get(hashtable_t *table, const void *key);
void *hashtable_set(hashtable_t *table, const void *key, void *value);
void *hashtable_del(hashtable_t *table, const void *key);
bool hashtable_contains(hashtable_t *table, const void *key);

#endif
