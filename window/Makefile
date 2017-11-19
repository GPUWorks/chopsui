ARCHIVES+= $(BDIR)/window/window.a

OBJECTS=$(BDIR)/window/window.o

sinclude window/wayland/Makefile

$(BDIR)/window/window.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?
