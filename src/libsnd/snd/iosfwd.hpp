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

#ifndef SND_IOSFWD_HPP
#define SND_IOSFWD_HPP 1

#include "soundfwd.hpp"	// For sound forward declarations.
#include "postypes.hpp"

namespace snd
{

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_ios;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_streambuf;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_istream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_ostream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_iostream;

/*
template<typename SampleT, typename SampleTraits = sample_traits<SampleT>,
         typename _Alloc = allocator<SampleT> >
         class basic_soundbuf;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT>,
         typename _Alloc = allocator<SampleT> >
         class basic_isoundstream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT>,
         typename _Alloc = allocator<SampleT> >
         class basic_osoundstream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT>,
         typename _Alloc = allocator<SampleT> >
         class basic_soundstream;

*/

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_filebuf;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_ifstream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_ofstream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class basic_fstream;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class istreambuf_iterator;

template<typename SampleT, typename SampleTraits = sample_traits<SampleT> >
class ostreambuf_iterator;

class ios_base; 

/** 
 *  @defgroup iosfwd I/O Forward Declarations
 *
 *  Nearly all of the I/O classes are parameterized on the type of
 *  samples they read and write.  (The major exception is ios_base at
 *  the top of the hierarchy.)
 *
 *  Because properly forward-declaring these classes can be difficult, you
 *  should not do it yourself.  Instead, include the iosfwd.hpp
 *  header, which contains only declarations of all the I/O classes as
 *  well as the typedefs.  Trying to forward-declare the typedefs
 *  themselves (e.g., "class ostream;") is not valid ISO C++.
 *
 *  @{
 */
typedef basic_ios<float>     	        ios;		///< @isiosfwd
typedef basic_streambuf<float> 	        streambuf;	///< @isiosfwd
typedef basic_istream<float> 		istream;	///< @isiosfwd
typedef basic_ostream<float> 		ostream;	///< @isiosfwd
typedef basic_iostream<float>		iostream;	///< @isiosfwd

/*
typedef basic_soundbuf<float> 	        soundbuf;	///< @isiosfwd
typedef basic_isoundstream<float> 	isoundstream;	///< @isiosfwd
typedef basic_osoundstream<float> 	osoundstream;	///< @isiosfwd
typedef basic_soundstream<float> 	soundstream;	///< @isiosfwd
*/

typedef basic_filebuf<float> 		filebuf;	///< @isiosfwd
typedef basic_ifstream<float>		ifstream;	///< @isiosfwd
typedef basic_ofstream<float>		ofstream;	///< @isiosfwd
typedef basic_fstream<float> 		fstream;	///< @isiosfwd

/** @}  */

} // namespace snd

#endif /* SND_IOSFWD_HPP */

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
