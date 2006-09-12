/*
  Copyright (C) 2005 Tim Mayberry
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
  
  $Id$
*/

#ifndef SND_POSTYPES_HPP
#define SND_POSTYPES_HPP 1

#include <stdint.h> // For int64_t
#include <cstddef> // For ptrdiff_t

/*
  I'm thinking that one way to support multi-channel
  streams is to create a stream position object 
  similar to in the standard library and make 
  template specializations based on the number of
  channels in the stream.

*/

namespace snd
{

typedef int64_t       streamoff;

/// Integral type for I/O operation counts and buffer sizes.
typedef ptrdiff_t     streamsize; // Signed integral type
typedef streamsize    streampos;

} // namespace snd

#endif // SND_POSTYPES_HPP

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
