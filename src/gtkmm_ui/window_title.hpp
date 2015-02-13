#ifndef UI_WINDOW_TITLE
#define UI_WINDOW_TITLE

#include <string>

namespace ui {

/**
 * \class The WindowTitle class can be used to maintain the
 * consistancy of window titles between windows and dialogs.
 *
 * Each std::string element that is added to the window title will
 * be separated by a hyphen.
 */
class WindowTitle
{
public:

	/**
	 * \param title The first string/element of the window title
	 * which will may be the application name or the document
	 * name in a document based application.
	 */
	WindowTitle(const std::string& title);

	/**
	 * Add an string element to the window title.
	 */
	void operator+= (const std::string&);

	/// @return The window title string.
	const std::string& get_string () { return m_title;}

private:

	std::string                         m_title;

};

} // ui

#endif // UI_WINDOW_TITLE
