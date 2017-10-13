$(BDIR)/test_node_matches_selector: test/main.c test/node/node_matches_selector.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=$(BDIR)/test_node_matches_selector

$(BDIR)/test_node_find_descendant: test/main.c test/node/node_find_descendant.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=$(BDIR)/test_node_find_descendant
