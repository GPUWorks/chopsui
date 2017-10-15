#ifndef _SUI_STRING_H
#define _SUI_STRING_H

struct str {
	char *str;
	size_t len, size;
};

typedef struct str sui_str_t;

sui_str_t *str_create();
void str_free(sui_str_t *str);
void str_append_ch(sui_str_t *str, uint32_t ch);

#endif
