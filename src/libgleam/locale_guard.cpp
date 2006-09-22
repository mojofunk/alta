#include <glib.h>

#include <clocale>
#include <cstring>
#include <cstdlib>

#include <libgleam/locale_guard.hpp>

#include "debug.hpp"

namespace gleam {

LocaleGuard::LocaleGuard (const int locale_catagory,
                          const char* temporary_locale)
	:
		m_locale_catagory(locale_catagory),
		m_original_locale(0)
{
	char* original_locale = setlocale(locale_catagory, NULL);

	// I doubt this is even possible.
	g_return_if_fail(original_locale);

	m_original_locale = strdup (original_locale);

	if (strcmp (original_locale, temporary_locale)) {
		setlocale (locale_catagory, temporary_locale);
	}
}

LocaleGuard::~LocaleGuard ()
{
	char* temporary_locale = setlocale(m_locale_catagory, m_original_locale);

#ifdef GLEAM_DEBUG

	if(!temporary_locale) {

		LOG_GLEAM_CRITICAL
			<< "Unable to restore locale"
			<< m_original_locale;

	}

#endif

	free(m_original_locale);
}

NumericGuard::NumericGuard ()
	: LocaleGuard(LC_NUMERIC, "C")
{

}

} // namespace gleam
