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

#include <glib/gatomic.h>

#include "snd/ios.hpp"
#include "snd/ostream.hpp"
#include "snd/istream.hpp"
#include "snd/fstream.hpp"

#include "snd/sndfile_filebuf.hpp"

namespace snd_internal
{
  using namespace snd;

  extern sndfile_filebuf<float> buf_leftin;
  extern sndfile_filebuf<float> buf_rightin;
  extern sndfile_filebuf<float> buf_leftout;
  extern sndfile_filebuf<float> buf_rightout;

} // namespace snd_internal

namespace snd 
{
  using namespace snd_internal;
  
  extern istream leftin;
  extern istream rightin;
  extern ostream leftout;
  extern ostream rightout;
  
  ios_base::Init::Init()
  {
    if (g_atomic_int_exchange_and_add(&s_refcount, 1) == 0)
      {
	// The standard streams are constructed once only and never
	// destroyed.
	new (&leftin) istream(&buf_leftin);
        new (&rightin) ostream(&buf_rightin);
	new (&leftout) ostream(&buf_leftout);
	new (&rightout) ostream(&buf_rightout);
	
	// NB: Have to set refcount above one, so that standard
	// streams are not re-initialized with uses of ios_base::Init
	// besides iostream.hpp static object, ie just using "ios.hpp"
	// with ios_base::Init objects.
	g_atomic_int_add(&s_refcount, 1);
      }
  }

  ios_base::Init::~Init()
  {
    if (g_atomic_int_exchange_and_add(&s_refcount, -1) == 2)
      {
	// Catch any exceptions thrown by basic_ostream::flush()
	try
	  { 
	    // Flush standard output streams as required by 27.4.2.1.6
	    leftin.flush();
            rightin.flush();
	    leftout.flush();
	    rightout.flush();
	  }
	catch (...)
	  { }
      }
  } 

} // namespace std

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
