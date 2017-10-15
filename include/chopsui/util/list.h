#ifndef _LIST_H
#define _LIST_H
#include <stddef.h>

typedef struct {
	size_t capacity;
	size_t length;
	void **items;
} sui_list_t;

sui_list_t *list_create(void);
void list_free(sui_list_t *list);
void list_foreach(sui_list_t *list, void (*callback)(void* item));
void list_add(sui_list_t *list, void *item);
void list_push(sui_list_t *list, void *item);
void list_insert(sui_list_t *list, size_t index, void *item);
void list_del(sui_list_t *list, size_t index);
void *list_pop(sui_list_t *list);
void *list_peek(sui_list_t *list);
void list_cat(sui_list_t *list, sui_list_t *source);
// See qsort. Remember to use *_qsort functions as compare functions,
// because they dereference the left and right arguments first!
void list_qsort(sui_list_t *list, int compare(const void *left, const void *right));
// Return index for first item in list that returns 0 for given compare
// function or -1 if none matches.
int list_seq_find(sui_list_t *list,
		int compare(const void *item, const void *cmp_to),
		const void *cmp_to);

#endif
