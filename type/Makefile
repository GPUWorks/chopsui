ARCHIVES+= $(BDIR)/type/type.a

OBJECTS=$(BDIR)/type/type_impl_register.o \
		$(BDIR)/type/type_impls_register.o \
		$(BDIR)/type/type_impl_map.o

$(BDIR)/type/type.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=$(BDIR)/type/type.a
