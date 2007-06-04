
#ifndef CFORMAT_LOCALE_GUARD_INCLUDED
#define CFORMAT_LOCALE_GUARD_INCLUDED

#include <clocale>
#include <cstring>
#include <cstdlib>

#include <cformat/cformat_exception.hpp>

namespace cformat {

struct LocaleGuard {

	LocaleGuard (const int locale_catagory,
			const char* temporary_locale)
		:
			m_locale_catagory(locale_catagory),
			m_original_locale(0)
	{
		char* original_locale = setlocale(locale_catagory, NULL);

		// I doubt this is even possible.
		if(!original_locale) {
			throw cformat_exception();
		}

		m_original_locale = strdup (original_locale);

		if (strcmp (original_locale, temporary_locale)) {
			setlocale (locale_catagory, temporary_locale);
		}
	}

	~LocaleGuard ()
	{
		char* temporary_locale = setlocale(m_locale_catagory, m_original_locale);

		if(!temporary_locale) {
			// how can this be dealt with in the destructor?
		}

		free(m_original_locale);
	}

private:

	const int	m_locale_catagory;
	char *		m_original_locale;

};

struct NumericGuard : public LocaleGuard {
	NumericGuard ()	: LocaleGuard(LC_NUMERIC, "C")
	{ }
};

} // namespace cformat

#endif // CFORMAT_LOCALE_GUARD_INCLUDED
