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

#ifndef SND_IOSTREAM_HPP
#define SND_IOSTREAM_HPP 1

#include "ostream.hpp"
#include "istream.hpp"

namespace snd
{

/**
 *  @name Standard Stream Objects
 *
 *  The "iostream.hpp" header declares the 4 standard stream
 *  objects. Input streams left and right channels and Output
 *  streams left and right channels.
 */
//@{
extern istream leftin;		///< Linked to the left input
extern istream rightin;		///< Linked to the left input
extern ostream leftout;		///< Linked to left output.
extern ostream rightout;	///< Linked to right output.
//@}

// For construction of filebuffers for leftin, rightin, leftout, rightout.
static ios_base::Init s_ioinit;

} // namespace snd

#endif /* SND_IOSTREAM_HPP */

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
