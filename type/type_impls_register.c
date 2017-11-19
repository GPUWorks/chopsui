#include <stdarg.h>
#include <chopsui/type.h>

void type_impls_register(const char *type, ...)  {
	va_list ap;
	va_start(ap, type);
	const struct sui_type_impl *_impl;
	while ((_impl = va_arg(ap, const struct sui_type_impl *))) {
		type_impl_register(type, _impl);
	}
	va_end(ap);
}
