/*
 * Copyright (C) 2006 Tim Mayberry
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#ifndef LOGX_PRETTY_FORMATTER_HEADER
#define LOGX_PRETTY_FORMATTER_HEADER

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // min/max

#include <logx/uncopyable.hpp>

namespace logx {

using std::string;
using std::vector;
using std::ostream;

class PrettyFormatter : Uncopyable
{
public:

	typedef vector<string>::const_iterator    const_iterator;

	PrettyFormatter(const vector<string>& log_data);

	/**
	 * \todo Actually do something pretty
	 */
	ostream& operator()(ostream& out) const;

private:

	const vector<string>&		m_log_data;

};

ostream& operator<<(ostream& out, PrettyFormatter& formatter);

} // namespace logx

#endif // LOGX_PRETTY_FORMATTER_HEADER
