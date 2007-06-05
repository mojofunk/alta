
#ifndef CFORMAT_CFORMAT_EXCEPTION_INCLUDED
#define CFORMAT_CFORMAT_EXCEPTION_INCLUDED

#include <exception>

namespace cformat {

struct cformat_exception : public std::exception {
	virtual const char *what() const throw() { return "cformat exception"; }
};

} // namespace cformat

#endif // CFORMAT_CFORMAT_EXCEPTION_INCLUDED
