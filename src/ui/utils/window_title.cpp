
#include <ui/utils/window_title.hpp>

namespace {
	
// I don't know if this should be translated.
const char* const title_separator = " - ";

} // anonymous namespace

namespace gmojo {

WindowTitle::WindowTitle(const string& title)
	:
		m_title(title)
{

}

void
WindowTitle::operator+= (const string& element)
{
	m_title = m_title + title_separator + element;
}

} // namespace gmojo
