
#include "window_title.hpp"

using std::string;

namespace {

const char* const title_separator = " - ";

} // anonymous namespace

namespace ui {

WindowTitle::WindowTitle(const string& title)
    : m_title(title)
{
}

void WindowTitle::operator+=(const string& element)
{
	m_title = m_title + title_separator + element;
}

} // namespace ui
