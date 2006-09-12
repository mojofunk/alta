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

//#include <glib/gatomic.h>
#include "snd/ios.hpp"

namespace snd 
{  
  // Definitions for static const members of ios_base.
  const ios_base::fmtflags ios_base::dither;

  const ios_base::iostate ios_base::badbit;
  const ios_base::iostate ios_base::eofbit;
  const ios_base::iostate ios_base::failbit;
  const ios_base::iostate ios_base::goodbit;

  const ios_base::openmode ios_base::app;
  const ios_base::openmode ios_base::ate;
  const ios_base::openmode ios_base::in;
  const ios_base::openmode ios_base::out;
  const ios_base::openmode ios_base::trunc;

  const ios_base::seekdir ios_base::beg;
  const ios_base::seekdir ios_base::cur;
  const ios_base::seekdir ios_base::end;

  //  const int ios_base::_S_local_word_size;

  gint ios_base::Init::s_refcount;

  ios_base::ios_base() 
  : m_flags(), m_streambuf_state()
  {
    // Do nothing: basic_ios::init() does it.  
  }
  
  ios_base::~ios_base()
  {

  }

} // namespace std
