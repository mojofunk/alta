#ifndef STRING_COMPOSE_H
#define STRING_COMPOSE_H

#include <string>
#include <sstream>

namespace mojo {

namespace internal {

void
compose_oss(const char* format, std::stringstream& oss)
{
	oss << format;
}

template<typename T, typename... Targs>
void
compose_oss (const char* format, std::stringstream& oss, T value, Targs...Fargs)
{
	while (*format != '\0') {
		if (*format == '%') {
			oss << value;
			compose_oss(format+1, oss, Fargs...); // recurse
			return;
		}
		oss << *format;
		format++;
	}
}

} // namespace internal

template<typename... Targs>
std::string
compose (const char* format, Targs...Fargs)
{
	std::stringstream oss;
	internal::compose_oss (format, oss, Fargs...);
	return oss.str();
}

} // namespace mojo

#endif // STRING_COMPOSE_H