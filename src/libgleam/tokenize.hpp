/*
   Copyright (C) 2006 Tim Mayberry

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA  02110-1301, USA.
*/

#ifndef GLEAM_TOKENIZER_INCLUDED
#define GLEAM_TOKENIZER_INCLUDED

#include <iterator>
#include <string>

namespace gleam {

/**
    Tokenize a string, this should work for std::string as well
	as Glib::ustring. This is a simple string tokenizing pattern,
	there are more powerful patterns out there, for instance 
	boost::tokenizer.

	\param str The string to tokenize.
	\param delims The characters to use for deliminating strings.
	\param it An insert iterator.
	\return The number of resulting tokens.
*/
template<typename StringType, typename Iter>
unsigned int
tokenize(const StringType& str,        
        const StringType& delims,
        Iter it)
{
    typename StringType::size_type start_pos = 0;
    typename StringType::size_type end_pos = 0;
    unsigned int token_count = 0;

    do {
        start_pos = str.find_first_not_of(delims, start_pos);
        end_pos = str.find_first_of(delims, start_pos);
        if (start_pos != end_pos) {
            if (end_pos == str.npos) {
                end_pos = str.length();
            }
            *it++ = str.substr(start_pos, end_pos - start_pos);
            ++token_count;
            start_pos = str.find_first_not_of(delims, end_pos + 1);
        }
    } while (start_pos != str.npos);

    if (start_pos != str.npos) {
        *it++ = str.substr(start_pos, str.length() - start_pos);
        ++token_count;
    }

    return token_count;
}

} // namespace gleam

#endif // GLEAM_TOKENIZER_INCLUDED
