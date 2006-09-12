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

#ifndef SND_OSTREAM_HPP
#define SND_OSTREAM_HPP 1

#include "ios.hpp"

namespace snd
{

/**
 *  @brief  Controlling output.
 *
 *  This is the base class for all output streams.  It provides text
 *  formatting of all builtin types, and communicates with any class
 *  derived from basic_streambuf to do the actual output.
 */
template<typename SampleT, typename SampleTraits>
class basic_ostream : virtual public basic_ios<SampleT, SampleTraits>
{
public:
    
    typedef SampleT                     		sample_type;
    typedef typename SampleTraits::pos_type 		pos_type;
    typedef typename SampleTraits::off_type 		off_type;
    typedef SampleTraits                    		traits_type;
    
    typedef basic_streambuf<SampleT, SampleTraits> 	streambuf_type;
    typedef basic_ios<SampleT, SampleTraits>		ios_type;
    typedef basic_ostream<SampleT, SampleTraits>	ostream_type;
    
    /**
     *  @brief  Base constructor.
     *
     *  This ctor is almost never called by the user directly, rather from
     *  derived classes' initialization lists, which pass a pointer to
     *  their own stream buffer.
     */
    explicit 
    basic_ostream(streambuf_type* sb)
    { this->init(sb); }
    
    /**
     *  @brief  Base destructor.
     *
     *  This does very little apart from providing a virtual base dtor.
     */
    virtual 
    ~basic_ostream() { }
    
    class sentry;
    friend class sentry;
    
    //@{
    /**
     *  @brief  Interface for manipulators.
     *
     *  Manuipulators such as @c std::endl and @c std::hex use these
     *  functions in constructs like "std::cout << std::endl".  For more
     *  information, see the iomanip header.
     */
    inline ostream_type&
    operator<<(ostream_type& (*pf)(ostream_type&));
    
    inline ostream_type&
    operator<<(ios_type& (*pf)(ios_type&));
    
    inline ostream_type&
    operator<<(ios_base& (*pf) (ios_base&));
    //@}
    
    /**
     *  @brief  Extracting from another streambuf.
     *  @param  sb  A pointer to a streambuf
     *
     *  This function behaves like one of the basic arithmetic extractors,
     *  in that it also constructs a sentry object and has the same error
     *  handling behavior.
     *
     *  If @a sb is NULL, the stream will set failbit in its error state.
     *
     *  Samples are extracted from @a sb and inserted into @c *this
     *  until one of the following occurs:
     *
     *  - the input stream reaches end-of-file,
     *  - insertion into the output sequence fails (in this case, the
     *    sample that would have been inserted is not extracted), or
     *  - an exception occurs while getting a sample from @a sb, which
     *    sets failbit in the error state
     *
     *  If the function inserts no samples, failbit is set.
     */
    ostream_type& 
    operator<<(streambuf_type* sb);
    //@}
    
    /**
     *  @name Unformatted Output Functions
     *
     *  All the unformatted output functions have some common behavior.
     *  Each starts by constructing a temporary object of type
     *  std::basic_ostream::sentry.  This has several effects, concluding
     *  with the setting of a status flag; see the sentry documentation
     *  for more.
     *
     *  If the sentry status is good, the function tries to generate
     *  whatever data is appropriate for the type of the argument.
     *
     *  If an exception is thrown during insertion, ios_base::badbit
     *  will be turned on in the stream's error state.  If badbit is on in
     *  the stream's exceptions mask, the exception will be rethrown
     *  without completing its actions.
     */
    //@{
    /**
     *  @brief  Simple insertion.
     *  @param  c  The sample to insert.
     *  @return  *this
     *
     *  Tries to insert @a c.
     *
     */
    ostream_type& 
    put(sample_type s);
    
    // Core write functionality, without sentry.
    void
    m_write(const sample_type* s, streamsize n)
    {
        streamsize put = this->rdbuf()->sputn(s, n);
        if (put != n)
            this->setstate(ios_base::badbit);
    }
    
    /**
     *  @brief  Sample string insertion.
     *  @param  s  The array to insert.
     *  @param  n  Maximum number of samples to insert.
     *  @return  *this
     *
     *  Samples are copied from @a s and inserted into the stream until
     *  one of the following happens:
     *
     *  - @a n samples are inserted
     *  - inserting into the output sequence fails (in this case, badbit
     *    will be set in the stream's error state)
     *
     *  @note  This function is not overloaded on signed char and
     *         unsigned char.
     */
    ostream_type& 
    write(const sample_type* s, streamsize n);
    //@}
    
    /**
     *  @brief  Synchronizing the stream buffer.
     *  @return  *this
     *
     *  If @c rdbuf() is a null pointer, changes nothing.
     *
     *  Otherwise, calls @c rdbuf()->pubsync(), and if that returns -1,
     *  sets badbit.
     */
    ostream_type& 
    flush();
    
    /**
     *  @brief  Getting the current write position.
     *  @return  A file position object.
     *
     *  If @c fail() is not false, returns @c pos_type(-1) to indicate
     *  failure.  Otherwise returns @c rdbuf()->pubseekoff(0,cur,out).
     */
    pos_type 
    tellp();
    
    /**
     *  @brief  Changing the current write position.
     *  @param  pos  A file position object.
     *  @return  *this
     *
     *  If @c fail() is not true, calls @c rdbuf()->pubseekpos(pos).  If
     *  that function fails, sets failbit.
     */
    ostream_type& 
    seekp(pos_type);
    
    /**
     *  @brief  Changing the current write position.
     *  @param  off  A file offset object.
     *  @param  dir  The direction in which to seek.
     *  @return  *this
     *
     *  If @c fail() is not true, calls @c rdbuf()->pubseekoff(off,dir).
     *  If that function fails, sets failbit.
     */
    ostream_type& 
    seekp(off_type, ios_base::seekdir);
    
protected:
    explicit 
    basic_ostream() { }
};

/**
 *  @brief  Performs setup work for output streams.
 *
 *  Objects of this class are created before all of the standard
 *  inserters are run.  It is responsible for "exception-safe prefix and
 *  suffix operations."  Additional actions may be added by the
 *  implementation, and we list them in
 *  http://gcc.gnu.org/onlinedocs/libstdc++/17_intro/howto.html#5
 *  under [27.6] notes.
 */
template <typename SampleT, typename SampleTraits>
class basic_ostream<SampleT, SampleTraits>::sentry
{
    // Data Members:
    bool 				m_ok;
    basic_ostream<SampleT,SampleTraits>& 	m_os;
    
public:
    
    /**
     *  @brief  The constructor performs preparatory work.
     *  @param  os  The output stream to guard.
     *
     *  If the stream state is good (@a os.good() is true), then if the
     *  stream is tied to another output stream, @c is.tie()->flush()
     *  is called to synchronize the output sequences.
     *
     *  If the stream state is still good, then the sentry state becomes
     *  true ("okay").
     */
    explicit
    sentry(basic_ostream<SampleT,SampleTraits>& os);
    
    /**
     *  @brief  Possibly flushes the stream.
     *
     *  If @c ios_base::unitbuf is set in @c os.flags(), and
     *  @c std::uncaught_exception() is true, the sentry destructor calls
     *  @c flush() on the output stream.
     */
    ~sentry()
    {
        // XXX MT
        //if (m_os.flags() & ios_base::unitbuf && !uncaught_exception())
        //{
            // Can't call flush directly or else will get into recursive lock.
            if (m_os.rdbuf() && m_os.rdbuf()->pubsync() == -1)
                m_os.setstate(ios_base::badbit);
            //}
    }
    
    /**
     *  @brief  Quick status checking.
     *  @return  The sentry state.
     *
     *  For ease of use, sentries may be converted to booleans.  The
     *  return value is that of the sentry state (true == okay).
     */
    operator bool() const
    { return m_ok; }
};

/**
 *  @brief  Flushes the output stream.
 *
 *  This manipulator simply calls the stream's @c flush() member function.
 */
template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>& 
flush(basic_ostream<SampleT, SampleTraits>& os)
{ return os.flush(); }

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>::sentry::
sentry(basic_ostream<SampleT, SampleTraits>& os)
    : m_ok(false), m_os(os)
{
    // XXX MT
    if (os.tie() && os.good())
        os.tie()->flush();
    
    if (os.good())
        m_ok = true;
    else
        os.setstate(ios_base::failbit);
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
operator<<(ostream_type& (*pf)(ostream_type&))
{
    return pf(*this);
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
operator<<(ios_type& (*pf)(ios_type&))
{
    pf(*this);
    return *this;
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
operator<<(ios_base& (*pf)(ios_base&))
{
    pf(*this);
    return *this;
}


template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
put(sample_type s)
{
    sentry cerb(*this);
    if (cerb)
    {
        ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
        try
        {
            if(!this->rdbuf()->sputs(s))
                err |= ios_base::badbit;
        }
        catch (...)
        { this->m_setstate(ios_base::badbit); }
        if (err)
            this->setstate(err);
    }
    return *this;
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
write(const SampleT* s, streamsize n)
{
    sentry cerb(*this);
    if (cerb)
    {
        try
        { m_write(s, n); }
        catch (...)
        { this->m_setstate(ios_base::badbit); }
    }
    return *this;
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
flush()
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    try
    {
        if (this->rdbuf() && this->rdbuf()->pubsync() == -1)
            err |= ios_base::badbit;
    }
    catch(...)
    { this->m_setstate(ios_base::badbit); }
    if (err)
        this->setstate(err);
    return *this;
}

template<typename SampleT, typename SampleTraits>
typename basic_ostream<SampleT, SampleTraits>::pos_type
basic_ostream<SampleT, SampleTraits>::
tellp()
{
    pos_type ret = pos_type(-1);
    try
    {
        if (!this->fail())
            ret = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out);
    }
    catch(...)
    { this->m_setstate(ios_base::badbit); }
    return ret;
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
seekp(pos_type pos)
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    try
    {
        if (!this->fail())
        {
            const pos_type p = this->rdbuf()->pubseekpos(pos,
                                                         ios_base::out);
            
            if (p == pos_type(off_type(-1)))
                err |= ios_base::failbit;
        }
    }
    catch(...)
    { this->m_setstate(ios_base::badbit); }
    if (err)
        this->setstate(err);
    return *this;
}

template<typename SampleT, typename SampleTraits>
basic_ostream<SampleT, SampleTraits>&
basic_ostream<SampleT, SampleTraits>::
seekp(off_type off, ios_base::seekdir dir)
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    try
    {
        if (!this->fail())
        {
            const pos_type p = this->rdbuf()->pubseekoff(off, dir,
                                                         ios_base::out);
            
            if (p == pos_type(off_type(-1)))
                err |= ios_base::failbit;
        }
    }
    catch(...)
    { this->m_setstate(ios_base::badbit); }
    if (err)
        this->setstate(err);
    return *this;
}

} // namespace snd

#endif	/* SND_OSTREAM_HPP */

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
