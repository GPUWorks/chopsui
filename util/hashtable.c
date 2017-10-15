#include <stdbool.h>
#include <stdlib.h>
#include <chopsui/util/hashtable.h>

sui_hashtable_t *hashtable_create(size_t buckets, unsigned int (*hash_function)(const void *)) {
	sui_hashtable_t *table = malloc(sizeof(sui_hashtable_t));
	table->hash = hash_function;
	table->bucket_count = buckets;
	table->buckets = calloc(buckets, sizeof(sui_hashtable_entry_t));
	return table;
}

static void free_bucket(sui_hashtable_entry_t *bucket) {
	if (bucket) {
		free_bucket(bucket->next);
		free(bucket);
	}
}

void hashtable_free(sui_hashtable_t *table) {
	for (size_t i = 0; i < table->bucket_count; ++i) {
		free_bucket(table->buckets[i]);
	}
	free(table);
}

bool hashtable_contains(sui_hashtable_t *table, const void *key) {
	unsigned int hash = table->hash(key);
	unsigned int bucket = hash % table->bucket_count;
	sui_hashtable_entry_t *entry = table->buckets[bucket];
	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	} else {
		return false;
	}
	return true;
}

void *hashtable_get(sui_hashtable_t *table, const void *key) {
	unsigned int hash = table->hash(key);
	unsigned int bucket = hash % table->bucket_count;
	sui_hashtable_entry_t *entry = table->buckets[bucket];
	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	} else {
		return NULL;
	}
	return entry->value;
}

void *hashtable_set(sui_hashtable_t *table, const void *key, void *value) {
	unsigned int hash = table->hash(key);
	unsigned int bucket = hash % table->bucket_count;
	sui_hashtable_entry_t *entry = table->buckets[bucket];
	sui_hashtable_entry_t *previous = NULL;

	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				previous = entry;
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	}

	if (entry == NULL) {
		entry = calloc(1, sizeof(sui_hashtable_entry_t));
		entry->key = hash;
		table->buckets[bucket] = entry;
		if (previous) {
			previous->next = entry;
		}
	}

	void *old = entry->value;
	entry->value = value;
	return old;
}

void *hashtable_del(sui_hashtable_t *table, const void *key) {
	unsigned int hash = table->hash(key);
	unsigned int bucket = hash % table->bucket_count;
	sui_hashtable_entry_t *entry = table->buckets[bucket];
	sui_hashtable_entry_t *previous = NULL;

	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				previous = entry;
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	}

	if (entry == NULL) {
		return NULL;
	} else {
		void *old = entry->value;
		if (previous) {
			previous->next = entry->next;
		} else {
			table->buckets[bucket] = NULL;
		}
		free(entry);
		return old;
	}
}

void hashtable_iter(sui_hashtable_t *table, void (*iter)(void *item, void *state), void *state) {
	for (size_t i = 0; i < table->bucket_count; ++i) {
		sui_hashtable_entry_t *entry = table->buckets[i];
		while (entry) {
			iter(entry->value, state);
			entry = entry->next;
		}
	}
}
