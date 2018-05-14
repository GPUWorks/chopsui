#ifndef _SUI_CSS_H
#define _SUI_CSS_H
#include <stdio.h>
#include <chopsui/util/list.h>
#include <chopsui/util/hashtable.h>
#include <chopsui/util/errors.h>
#include <chopsui/scalars.h>

// TODO: A fair bit of this state should be made internal

enum selector_type {
	SELECTOR_ANY,          // *
	SELECTOR_TYPE,         // type
	SELECTOR_ID,           // #id
	SELECTOR_CLASS,        // .class
	SELECTOR_ATTRIBUTE,    // [...]
	SELECTOR_DESCENDANT,   // (whitespace)
	SELECTOR_CHILD,        // >
	SELECTOR_SIBLING,      // ~
	SELECTOR_NEXT_SIBLING, // +
};

enum attribute_comparison {
	ATTR_EXISTS,         // [attr] matches attr="*"
	ATTR_EQUALS,         // [attr=value] matches attr="word"
	ATTR_WORD,           // [attr~=word] matches attr="x x word x x"
	ATTR_EQUALS_OR_DASH, // [attr|=word] matches attr="word" or attr="word-*"
	ATTR_PREFIX,         // [attr^=prefix] matches attr="prefix*"
	ATTR_SUFFIX,         // [attr$=suffix] matches attr="*suffix"
	ATTR_CONTAINS,       // [attr*=match] matches attr="*match*"
};

struct selector {
	// Note: the most significant selector is the first. In other words, for:
	//
	//   foo .bar #baz
	//
	// The first selector in the linked list is #baz, and #baz->next is .bar.
	struct selector *next;
	struct selector *prev;

	enum selector_type type;
	char *value;
	int specificity;

	// Used for attribute selectors
	enum attribute_comparison comparison;
	char *attr_value;
};

/**
 * Parses a selector string and returns a new selector. Returns NULL on error.
 */
struct selector *selector_parse(const char *source);

/**
 * Frees a selector.
 */
void selector_free(struct selector *selector);

/**
 * Prints a selector.
 */
void selector_print(struct selector *selector, bool pretty,
		void (*putch)(uint32_t ch));

struct style_rule {
	sui_list_t *selectors;
	sui_hashtable_t *properties;
};

void style_rule_free(struct style_rule *style_rule);

enum media_rule_feature {
	MEDIA_FEAT_WIDTH,
	MEDIA_FEAT_HEIGHT,
	MEDIA_FEAT_ASPECT_RATIO,
	MEDIA_FEAT_ORIENTATION,
	MEDIA_FEAT_RESOLUTION,
	MEDIA_FEAT_HOVER,
};

enum media_rule_type {
	MEDIA_TYPE_MIN,
	MEDIA_TYPE_MAX,
};

enum media_rule_operator {
	MEDIA_OP_OR,
	MEDIA_OP_AND,
	MEDIA_OP_NOT,
	MEDIA_OP_ONLY,
};

struct media_rule {
	enum media_rule_feature feature;
	enum media_rule_type type;
	enum media_rule_operator operator;
	struct sui_scalar scalar;
	struct media_rule *next;
};

void media_rule_free(struct media_rule *media_rule);

struct keyframe {
	struct sui_scalar at;
	sui_list_t *rules;
};

struct keyframes {
	char *identifier;
	sui_list_t *keys;
};

void keyframes_free(struct keyframes *keyframes);

struct stylesheet {
	sui_list_t *rules;
	sui_list_t *media_rules;
	sui_list_t *keyframes;
};

struct stylesheet *css_parse(const char *source, errors_t **errs);
struct stylesheet *css_load(FILE *source, errors_t **errs);
void stylesheet_free(struct stylesheet *stylesheet);

struct style_context;
struct sui_node;

struct style_context *style_get_context(struct sui_node *node);
const struct sui_scalar *style_get_attr(struct style_context *ctx,
		struct sui_node *node, const char *key);

#endif
