
#ifndef GLEAM_LOCALE_GUARD_INCLUDED
#define GLEAM_LOCALE_GUARD_INCLUDED

namespace gleam {

struct LocaleGuard {
	
	LocaleGuard (const int locale_catagory,
	             const char* temporary_locale);

	~LocaleGuard ();

private:

	const int	m_locale_catagory;
	char *		m_original_locale;

};

struct NumericGuard : public LocaleGuard {
	NumericGuard();
};

} // namespace gleam

#endif // GLEAM_LOCALE_GUARD_INCLUDED
