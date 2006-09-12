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

#ifndef GLEAM_SCOPED_HANDLE_INCLUDED
#define GLEAM_SCOPED_HANDLE_INCLUDED

#include <glib.h>

#include <cerrno>

namespace gleam {

/**
 * scoped_handle is a class using Resource Acquisition Is 
 * Initialization(RAII) and will work for types where
 * the function to close or release the resource returns
 * zero on success.
 */
template <typename handleT>
class scoped_handle
{
private:
	typedef scoped_handle<handleT> this_type;

	// Uncopyable
	scoped_handle(const this_type&);
	this_type& operator= (const this_type&);

public:

	typedef handleT    handle_type;
	typedef int (*close_func_type)(handleT);

	scoped_handle(handle_type handle,
			close_func_type close_func,
			handle_type null_value = 0)
		:
			m_handle(handle),
			m_close_func(close_func),
			m_null_value(null_value)
	{

	}

	~scoped_handle()
	{
		close();
	}

	handle_type get() const
	{
		return const_cast<this_type&>(*this).m_handle;
	}

	bool valid() const
	{ return m_handle != m_null_value; }

	void close()
	{
		if(valid())
		{
			if(m_close_func(m_handle) != 0)
			{
				g_printerr("%s : Error closing resource handle : %s", G_STRLOC, g_strerror(errno));
			}
			m_handle = m_null_value;
		}
	}

private:

	handle_type                   m_handle;
	const close_func_type&        m_close_func;
	const handle_type             m_null_value;

};

} // namespace gleam

#endif // GLEAM_SCOPED_HANDLE_INCLUDED
