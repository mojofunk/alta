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

#ifndef BASIC_FILE_SNDFILE_HPP
#define BASIC_FILE_SNDFILE_HPP 1

#include <sndfile.h>

#include "ios.hpp"

namespace Glib {
	class Mutex;
}

namespace snd
{
// Generic declaration.
template<typename SampleT>
class basic_file; 

// Specialization.
template<>
class basic_file<float>
{
	// Underlying data source/sink.
    SNDFILE* 	m_sndfile;
    
    Glib::Mutex* m_lock;
    
public:
    basic_file(Glib::Mutex* lock = 0);
    
    ~basic_file();
    
    basic_file* 
    open(const float* name, ios_base::openmode mode);
    
    basic_file* 
    close(); 
    
    bool 
    is_open() const;
    
    streamsize 
    xsputn(const float* s, streamsize n);
    
    streamsize 
    xsgetn(float* s, streamsize n);
    
    streamoff
    seekoff(streamoff off, ios_base::seekdir way);
    
    int 
    sync();
    
    streamsize
    showmanyc();
};

// impl

}  // namespace snd

#endif // BASIC_FILE_SNDFILE_HPP

