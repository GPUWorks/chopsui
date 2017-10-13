TESTCC=$(CC) $(CFLAGS) -Itest/

$(BDIR)/test_%: test/main.c test/test_%.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS=\
	$(BDIR)/test_selector_parse \
	$(BDIR)/test_scalar_parse \
	$(BDIR)/test_css_parse \
	$(BDIR)/test_node_matches_selector \
	$(BDIR)/test_node_find_descendant \
	$(BDIR)/test_sui_parse \
	$(BDIR)/test_unicode
