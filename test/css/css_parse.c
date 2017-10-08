#include <string.h>
#include <assert.h>
#include "chopsui/util/hashtable.h"
#include "chopsui/css.h"
#include "test.h"

char *test_name = "css/css_parse";

static int test_comments() {
	struct stylesheet *ss = css_parse("/* this should cause\n"
			"a syntax error if comments aren't being handled\n"
			"correctly. */", NULL);
	stylesheet_free(ss);
	return 0;
}

static int test_selector() {
	struct stylesheet *ss = css_parse("foo .bar { }", NULL);
	assert(ss->rules->length == 1);
	struct style_rule *rule = ss->rules->items[0];
	assert(rule && rule->selectors->length == 1);
	struct selector *selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);
	selector = selector->next;
	assert(selector && selector->type == SELECTOR_DESCENDANT);
	selector = selector->next;
	assert(selector && selector->type == SELECTOR_CLASS);
	assert(!selector->next);
	stylesheet_free(ss);
	return 0;
}

static int test_multiple_rules() {
	struct stylesheet *ss = css_parse("foo { } bar { }", NULL);
	assert(ss->rules->length == 2);

	struct style_rule *rule = ss->rules->items[0];
	assert(rule && rule->selectors->length == 1);
	struct selector *selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);

	rule = ss->rules->items[1];
	assert(rule && rule->selectors->length == 1);
	selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);

	stylesheet_free(ss);
	return 0;
}

static int test_multiple_selectors() {
	struct stylesheet *ss = css_parse("foo, bar { }", NULL);
	assert(ss->rules->length == 1);

	struct style_rule *rule = ss->rules->items[0];
	assert(rule && rule->selectors->length == 2);
	struct selector *selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(!selector->next);

	selector = rule->selectors->items[1];
	assert(selector && selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "bar") == 0);
	assert(!selector->next);

	stylesheet_free(ss);
	return 0;
}

static int test_properties() {
	struct stylesheet *ss = css_parse("foo { background: red; }", NULL);
	assert(ss->rules->length == 1);

	struct style_rule *rule = ss->rules->items[0];
	assert(rule);

	char *value = hashtable_get(rule->properties, "background");
	assert(value && strcmp(value, "red") == 0);

	stylesheet_free(ss);
	return 0;
}

static int test_multi_properties() {
	struct stylesheet *ss = css_parse("foo { \n"
			"\tbackground: red;\n"
			"\tfont-weight: bold;\n"
			"}", NULL);
	assert(ss->rules->length == 1);

	struct style_rule *rule = ss->rules->items[0];
	assert(rule);

	char *value = hashtable_get(rule->properties, "background");
	assert(value && strcmp(value, "red") == 0);

	value = hashtable_get(rule->properties, "font-weight");
	assert(value && strcmp(value, "bold") == 0);

	stylesheet_free(ss);
	return 0;
}

static int test_quoted_properties() {
	struct stylesheet *ss = css_parse("foo { \n"
			"\ttext: \"hello: {world};!\";\n"
			"\theader: '/*hello*/: \\'world\\';!';\n"
			"}", NULL);
	assert(ss->rules->length == 1);

	struct style_rule *rule = ss->rules->items[0];
	assert(rule);

	char *value = hashtable_get(rule->properties, "text");
	assert(value && strcmp(value, "hello: {world};!") == 0);

	value = hashtable_get(rule->properties, "header");
	assert(value && strcmp(value, "/*hello*/: \'world\';!") == 0);

	stylesheet_free(ss);
	return 0;
}

static int test_errors() {
	errors_t *errors = NULL;
	struct stylesheet *ss = css_parse("\n{ test }", &errors);
	assert(errors);
	assert(errors->length == 1);
	assert(strcmp((char *)errors->items[0],
		"[2:1] Expected selector before properties") == 0);
	errors_free(errors);
	stylesheet_free(ss);
	return 0;
}

int test_main() {
	return test_comments()
		|| test_selector()
		|| test_multiple_rules()
		|| test_multiple_selectors()
		|| test_properties()
		|| test_multi_properties()
		|| test_quoted_properties()
		|| test_errors()
	;
}
