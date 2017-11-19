ARCHIVES+= $(BDIR)/type/type.a

OBJECTS=$(BDIR)/type/type_impl_register.o \
		$(BDIR)/type/type_impls_register.o \
		$(BDIR)/type/type_impl_map.o \
		$(BDIR)/type/attr_spec_attr_spec.o \
		$(BDIR)/type/attr_spec_attr_default.o

$(BDIR)/type/type.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?
