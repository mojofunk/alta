
#ifndef CFORMAT_CFORMAT_EXCEPTION
#define CFORMAT_CFORMAT_EXCEPTION

#include <exception>

namespace cformat {

struct cformat_exception : public std::exception {
	virtual const char *what() const throw() { return "cformat exception"; }
};

} // namespace cformat

#endif // CFORMAT_CFORMAT_EXCEPTION
