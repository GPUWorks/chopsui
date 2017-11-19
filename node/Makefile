ARCHIVES+= $(BDIR)/node/node.a

OBJECTS=$(BDIR)/node/node_get_attr.o \
		$(BDIR)/node/node_set_attr.o \
		$(BDIR)/node/node_has_class.o \
		$(BDIR)/node/node_add_class.o \
		$(BDIR)/node/node_remove_class.o \
		$(BDIR)/node/node_free.o \
		$(BDIR)/node/node_append_child.o \
		$(BDIR)/node/node_insert_child.o \
		$(BDIR)/node/node_detach.o \
		$(BDIR)/node/node_matches_selector.o \
		$(BDIR)/node/node_find_descendants.o \
		$(BDIR)/node/node_find_descendant.o \
		$(BDIR)/node/node_find_ancestors.o \
		$(BDIR)/node/node_find_ancestor.o \
		$(BDIR)/node/node_type_add_impl.o \
		$(BDIR)/node/node_type_remove_impl.o \
		$(BDIR)/node/node_initialize_types.o

$(BDIR)/node/node.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=$(BDIR)/node/node.a
