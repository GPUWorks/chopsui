#include <stdbool.h>
#include <chopsui/util/unicode.h>
#include <chopsui/css.h>

static void sputs(void (*putch)(uint32_t ch), const char *s) {
	while (*s) {
		uint32_t ch = utf8_decode(&s);
		putch(ch);
	}
}

void selector_print(struct selector *s, bool pretty,
		void (*putch)(uint32_t ch)) {
	while (s->next) {
		s = s->next;
	}
	while (s) {
		switch (s->type) {
		case SELECTOR_TYPE:
			sputs(putch, s->value);
			break;
		case SELECTOR_ID:
			putch('#');
			sputs(putch, s->value);
			break;
		case SELECTOR_CLASS:
			putch('.');
			sputs(putch, s->value);
			break;
		case SELECTOR_ANY:
			putch('*');
			break;
		case SELECTOR_ATTRIBUTE:
			putch('[');
			sputs(putch, s->value);
			sputs(putch, "TODO: attribute selectors");
			/*
			switch (s->comparison) {
			}
			*/
			putch(']');
			break;
		case SELECTOR_DESCENDANT:
			putch(' ');
			break;
		case SELECTOR_CHILD:
			if (pretty) {
				sputs(putch, " > ");
			} else {
				putch('>');
			}
			break;
		case SELECTOR_SIBLING:
			if (pretty) {
				sputs(putch, " ~ ");
			} else {
				putch('~');
			}
			break;
		case SELECTOR_NEXT_SIBLING:
			if (pretty) {
				sputs(putch, " + ");
			} else {
				putch('+');
			}
			break;
		}
		s = s->prev;
	}
}
