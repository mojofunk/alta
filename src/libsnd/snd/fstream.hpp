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

#ifndef SND_FSTREAM_HPP
#define SND_FSTREAM_HPP 1

#include "istream.hpp"
#include "ostream.hpp"
#include "basic_file.hpp"
//#include "streambuf.hpp"

//#include "sample_traits.hpp"

namespace snd
{
 
template<typename SampleT, typename SampleTraits>
class basic_filebuf : public basic_streambuf<SampleT, SampleTraits>
{
public:

    typedef SampleT                    	        sample_type;
    typedef SampleTraits               	        traits_type;
    typedef typename traits_type::int_type 		int_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;
    
    typedef basic_streambuf<sample_type, traits_type> streambuf_type;
    typedef basic_filebuf<sample_type, traits_type>   filebuf_type;
    typedef basic_file<sample_type> 		      file_type;
        
protected:

    // Data Members:
    // MT lock inherited from glibmm or other threading library.
    // @todo
    Glib::Mutex   	m_lock;
    
    file_type 		m_file;
    
    ios_base::openmode 	m_mode;
    
    /**
     *  @if maint
     *  Pointer to the beginning of internal buffer.
     *  @endif
     */
    sample_type*		m_buf; 	
    
    /**
     *  @if maint
     *  Actual size of internal buffer. This number is equal to the size
     *  of the put area + 1 position, reserved for the overflow char of
     *  a full area.
     *  @endif
     */
    size_t			m_buf_size;
    
    // Set iff m_buf is allocated memory from m_allocate_internal_buffer.
    bool			m_buf_allocated;
    
    /**
     *  @if maint
     *  m_reading == false && m_writing == false for 'uncommitted' mode;  
     *  m_reading == true for 'read' mode;
     *  m_writing == true for 'write' mode;
     *
     *  NB: m_reading == true && m_writing == true is unused.
     *  @endif
     */ 
    bool                      m_reading;
    bool                      m_writing;
  
    /**
     *  @if maint
     *  Size of buffer held by m_ext_buf.
     *  @endif
     */ 
    streamsize		m_ext_buf_size;
    
public:
    // Constructors/destructor:
    /**
     *  @brief  Does not open any files.
     *
     *  The default constructor initializes the parent class using its
     *  own default ctor.
     */
    basic_filebuf();
    
    /**
     *  @brief  The destructor closes the file first.
     */
    virtual
    ~basic_filebuf()
    { this->close(); }
    
    // Members:
    /**
     *  @brief  Returns true if the external file is open.
     */
    bool
    is_open() const throw()
    { return m_file.is_open(); }
    
    /**
     *  @brief  Opens an external file.
     *  @param  s  The name of the file.
     *  @param  mode  The open mode flags.
     *  @return  @c this on success, NULL on failure
     *
     *  If a file is already open, this function immediately fails.
     *  Otherwise it tries to open the file named @a s using the flags
     *  given in @a mode.
     *
     *  [Table 92 gives the relation between openmode combinations and the
     *  equivalent fopen() flags, but the table has not been copied yet.]
     */
    filebuf_type*
    open(const char* s, ios_base::openmode mode);
    
    /**
     *  @brief  Closes the currently associated file.
     *  @return  @c this on success, NULL on failure
     *
     *  If no file is currently open, this function immediately fails.
     *
     *  If a "put buffer area" exists, @c overflow(eof) is called to flush
     *  all the characters.  The file is then closed.
     *
     *  If any operations fail, this function also fails.
     */
    filebuf_type*
    close() throw();
    
protected:

    virtual streamsize
    showmanyc();

    virtual int_type
    underflow();
    
    virtual int_type
    pbackfail(int_type s);

    virtual int_type
    overflow(int_type s);

    virtual streambuf_type*
    setbuf(sample_type* s, streamsize n);
    
    virtual pos_type
    seekoff(off_type off, ios_base::seekdir way,
            ios_base::openmode mode = ios_base::in | ios_base::out);
    
    virtual pos_type
    seekpos(pos_type pos,
            ios_base::openmode mode = ios_base::in | ios_base::out);
    
    virtual int
    sync();
        
    virtual streamsize
    xsgetn(sample_type* s, streamsize n);
    
    virtual streamsize
    xsputn(const sample_type* s, streamsize n);

};

template<typename SampleT, typename SampleTraits>
class basic_ifstream : public basic_istream<SampleT, SampleTraits>
{
public:
  
    typedef SampleT 					        sample_type;
    typedef SampleTraits 					    traits_type;
    typedef typename traits_type::int_type 		int_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;
    
    
    typedef basic_filebuf<sample_type, traits_type> filebuf_type;
    typedef basic_istream<sample_type, traits_type>	istream_type;
    
private:
    filebuf_type	m_filebuf;
    
public:
    // Constructors/Destructors:
    /**
     *  @brief  Default constructor.
     *
     *  Initializes @c sb using its default constructor, and passes
     *  @c &sb to the base class initializer.  Does not open any files
     *  (you haven't given it a filename to open).
     */
    basic_ifstream() : istream_type(), m_filebuf()
    { this->init(&m_filebuf); }
    
    /**
     *  @brief  Create an input file stream.
     *  @param  s  Null terminated string specifying the filename.
     *  @param  mode  Open file in specified mode (see std::ios_base).
     *
     *  @c ios_base::in is automatically included in @a mode.
     *
     *  Tip:  When using std::string to hold the filename, you must use
     *  .c_str() before passing it to this constructor.
     */
    explicit
    basic_ifstream(const char* s, ios_base::openmode mode = ios_base::in)
        : istream_type(), m_filebuf()
    {
        this->init(&m_filebuf);
        this->open(s, mode);
    }
    
    /**
     *  @brief  The destructor does nothing.
     *
     *  The file is closed by the filebuf object, not the formatting
     *  stream.
     */
    ~basic_ifstream()
    { }
    
    // Members:
    /**
     *  @brief  Accessing the underlying buffer.
     *  @return  The current basic_filebuf buffer.
     *
     *  This hides both signatures of std::basic_ios::rdbuf().
     */
    filebuf_type*
    rdbuf() const
    { return const_cast<filebuf_type*>(&m_filebuf); }
    
    /**
     *  @brief  Wrapper to test for an open file.
     *  @return  @c rdbuf()->is_open()
     */
    bool
    is_open()
    { return m_filebuf.is_open(); }
    
    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 365. Lack of const-qualification in clause 27
    bool
    is_open() const
    { return m_filebuf.is_open(); }
    
    /**
     *  @brief  Opens an external file.
     *  @param  s  The name of the file.
     *  @param  mode  The open mode flags.
     *
     *  Calls @c snd::basic_filebuf::open(s,mode|in).  If that function
     *  fails, @c failbit is set in the stream's error state.
     */
    void
    open(const char* s, ios_base::openmode mode = ios_base::in)
    {
        if (!m_filebuf.open(s, mode | ios_base::in))
            this->setstate(ios_base::failbit);
        else
            this->clear();
    }
    
    /**
     *  @brief  Close the file.
     *
     *  Calls @c snd::basic_filebuf::close().  If that function
     *  fails, @c failbit is set in the stream's error state.
     */
    void
    close()
    {
        if (!m_filebuf.close())
            this->setstate(ios_base::failbit);
    }
};

/**
 *  @brief  Controlling output for files.
 *
 *  This class supports reading from named files, using the inherited
 *  functions from snd::basic_ostream.  To control the associated
 *  sequence, an instance of snd::basic_filebuf is used, which this page
 *  refers to as @c sb.
 */
template<typename SampleT, typename SampleTraits>
class basic_ofstream : public basic_ostream<SampleT,SampleTraits>
{
public:
    // Types:
    typedef SampleT 					        sample_type;
    typedef SampleTraits 					    traits_type;
    typedef typename traits_type::int_type 		int_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;
    
    // Non-standard types:
    typedef basic_filebuf<sample_type, traits_type> filebuf_type;
    typedef basic_ostream<sample_type, traits_type>	ostream_type;
    
private:
    filebuf_type	m_filebuf;
    
public:
    // Constructors:
    /**
     *  @brief  Default constructor.
     *
     *  Initializes @c sb using its default constructor, and passes
     *  @c &sb to the base class initializer.  Does not open any files
     *  (you haven't given it a filename to open).
     */
    basic_ofstream(): ostream_type(), m_filebuf()
    { this->init(&m_filebuf); }
    
    /**
     *  @brief  Create an output file stream.
     *  @param  s  Null terminated string specifying the filename.
     *  @param  mode  Open file in specified mode (see std::ios_base).
     *
     *  @c ios_base::out|ios_base::trunc is automatically included in
     *  @a mode.
     *
     *  Tip:  When using std::string to hold the filename, you must use
     *  .c_str() before passing it to this constructor.
     */
    explicit
    basic_ofstream(const char* s,
                   ios_base::openmode mode = ios_base::out | ios_base::trunc )
        : ostream_type(), m_filebuf()
    {
        this->init(&m_filebuf);
        this->open(s, mode);
    }
    
    /**
     *  @brief  The destructor does nothing.
     *
     *  The file is closed by the filebuf object, not the formatting
     *  stream.
     */
    ~basic_ofstream()
    { }
    
    // Members:
    /**
     *  @brief  Accessing the underlying buffer.
     *  @return  The current basic_filebuf buffer.
     *
     *  This hides both signatures of std::basic_ios::rdbuf().
     */
    filebuf_type*
    rdbuf() const
    { return const_cast<filebuf_type*>(&m_filebuf); }
    
    /**
     *  @brief  Wrapper to test for an open file.
     *  @return  @c rdbuf()->is_open()
     */
    bool
    is_open()
    { return m_filebuf.is_open(); }
    
    bool
    is_open() const
    { return m_filebuf.is_open(); }
    
    /**
     *  @brief  Opens an external file.
     *  @param  s  The name of the file.
     *  @param  mode  The open mode flags.
     *
     *  Calls @c std::basic_filebuf::open(s,mode|out|trunc).  If that
     *  function fails, @c failbit is set in the stream's error state.
     *
     *  Tip:  When using std::string to hold the filename, you must use
     *  .c_str() before passing it to this constructor.
     */
    void
    open(const char* s,
         ios_base::openmode mode = ios_base::out | ios_base::trunc)
    {
        if (!m_filebuf.open(s, mode | ios_base::out))
            this->setstate(ios_base::failbit);
        else
            // _GLIBCXX_RESOLVE_LIB_DEFECTS
            // 409. Closing an fstream should clear error state
            this->clear();
    }
    
    /**
     *  @brief  Close the file.
     *
     *  Calls @c std::basic_filebuf::close().  If that function
     *  fails, @c failbit is set in the stream's error state.
     */
    void
    close()
    {
        if (!m_filebuf.close())
            this->setstate(ios_base::failbit);
    }
};


// [27.8.1.11] Template class basic_fstream
/**
 *  @brief  Controlling intput and output for files.
 *
 *  This class supports reading from and writing to named files, using
 *  the inherited functions from std::basic_iostream.  To control the
 *  associated sequence, an instance of std::basic_filebuf is used, which
 *  this page refers to as @c sb.
 */
template<typename SampleT, typename SampleTraits>
class basic_fstream : public basic_iostream<SampleT, SampleTraits>
{
public:
    // Types:
    typedef SampleT 					        sample_type;
    typedef SampleTraits 					    traits_type;
    typedef typename traits_type::int_type 		int_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;
    
    // Non-standard types:
    typedef basic_filebuf<sample_type, traits_type> 	filebuf_type;
    typedef basic_ios<sample_type, traits_type>		ios_type;
    typedef basic_iostream<sample_type, traits_type>	iostream_type;
    
private:
    filebuf_type	m_filebuf;
    
public:
    // Constructors/destructor:
    /**
     *  @brief  Default constructor.
     *
     *  Initializes @c sb using its default constructor, and passes
     *  @c &sb to the base class initializer.  Does not open any files
     *  (you haven't given it a filename to open).
     */
    basic_fstream()
        : iostream_type(), m_filebuf()
    { this->init(&m_filebuf); }
    
    /**
     *  @brief  Create an input/output file stream.
     *  @param  s  Null terminated string specifying the filename.
     *  @param  mode  Open file in specified mode (see std::ios_base).
     *
     *  Tip:  When using std::string to hold the filename, you must use
     *  .c_str() before passing it to this constructor.
     */
    explicit
    basic_fstream(const char* s,
                  ios_base::openmode mode = ios_base::in | ios_base::out)
        : iostream_type(NULL), m_filebuf()
    {
        this->init(&m_filebuf);
        this->open(s, mode);
    }
    
    /**
     *  @brief  The destructor does nothing.
     *
     *  The file is closed by the filebuf object, not the formatting
     *  stream.
     */
    ~basic_fstream()
    { }
    
    // Members:
    /**
     *  @brief  Accessing the underlying buffer.
     *  @return  The current basic_filebuf buffer.
     *
     *  This hides both signatures of std::basic_ios::rdbuf().
     */
    filebuf_type*
    rdbuf() const
    { return const_cast<filebuf_type*>(&m_filebuf); }
    
    /**
     *  @brief  Wrapper to test for an open file.
     *  @return  @c rdbuf()->is_open()
     */
    bool
    is_open()
    { return m_filebuf.is_open(); }
    
    bool
    is_open() const
    { return m_filebuf.is_open(); }
    
    /**
     *  @brief  Opens an external file.
     *  @param  s  The name of the file.
     *  @param  mode  The open mode flags.
     *
     *  Calls @c std::basic_filebuf::open(s,mode).  If that
     *  function fails, @c failbit is set in the stream's error state.
     *
     *  Tip:  When using std::string to hold the filename, you must use
     *  .c_str() before passing it to this constructor.
     */
    void
    open(const char* s,
         ios_base::openmode mode = ios_base::in | ios_base::out)
    {
        if (!m_filebuf.open(s, mode))
            this->setstate(ios_base::failbit);
        else
            this->clear();
    }
    
    /**
     *  @brief  Close the file.
     *
     *  Calls @c std::basic_filebuf::close().  If that function
     *  fails, @c failbit is set in the stream's error state.
     */
    void
    close()
    {
        if (!m_filebuf.close())
            this->setstate(ios_base::failbit);
    }
};

} // namespace snd

#endif /* SND_FSTREAM_HPP */

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
