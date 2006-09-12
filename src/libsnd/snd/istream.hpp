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

#ifndef SND_ISTREAM_HPP
#define SND_ISTREAM_HPP 1

#include "ios.hpp"

namespace snd
{

/**
 *  @brief  Controlling input.
 *
 *  This is the base class for all input streams.  It provides text
 *  formatting of all builtin types, and communicates with any class
 *  derived from basic_streambuf to do the actual input.
 */
template<typename SampleT, typename SampleTraits>
class basic_istream : virtual public basic_ios<SampleT, SampleTraits>
{
public:
    
    typedef SampleT                         		sample_type;
    typedef typename SampleTraits::pos_type 		pos_type;
    typedef typename SampleTraits::off_type 		off_type;
    typedef SampleTraits                    		traits_type;
    
    typedef basic_streambuf<SampleT, SampleTraits> 	streambuf_type;
    typedef basic_ios<SampleT, SampleTraits>		ios_type;
    typedef basic_istream<SampleT, SampleTraits>	istream_type;

/*   
    // doc me 
    template<typename SampleT2, typename SampleTraits2>
    friend basic_istream<SampleT2, SampleTraits2>&
    operator>>(basic_istream<SampleT2, SampleTraits2>&, SampleT2&);
    
    // doc me
    template<typename SampleT2, typename SampleTraits2>
    friend basic_istream<SampleT2, SampleTraits2>&
    operator>>(basic_istream<SampleT2, SampleTraits2>&, SampleT2*);
*/
  
protected:
    // Data Members:
    /**
     *  @if maint
     *  The number of characters extracted in the previous unformatted
     *  function; see gcount().
     *  @endif
     */
    streamsize 		m_gcount;
    
public:

    /**
     *  @brief  Base constructor.
     *
     *  This ctor is almost never called by the user directly, rather from
     *  derived classes' initialization lists, which pass a pointer to
     *  their own stream buffer.
     */
    explicit 
    basic_istream(streambuf_type* sb): m_gcount(streamsize(0))
    { this->init(sb); }
    
    /**
     *  @brief  Base destructor.
     *
     *  This does very little apart from providing a virtual base dtor.
     */
    virtual 
    ~basic_istream() 
    { m_gcount = streamsize(0); }
    
    class sentry;
    friend class sentry;

    //@{
    /**
     *  @brief  Interface for manipulators.
     *
     *  Manuipulators. For more information, see the iomanip header.
     */
    inline istream_type&
    operator>>(istream_type& (*pf)(istream_type&));

    inline istream_type&
    operator>>(ios_type& (*pf)(ios_type&));
    
    inline istream_type&
    operator>>(ios_base& (*pf)(ios_base&));
    //@}
        
    /**
     *  @brief  Extracting into another streambuf.
     *  @param  sb  A pointer to a streambuf
     *
     *  If @a sb is NULL, the stream will set failbit in its error state.
     *
     *  Samples are extracted from this stream and inserted into the
     *  @a sb streambuf until one of the following occurs:
     *
     *  - insertion into the output buffer fails (in this case, the
     *    sample that would have been inserted is not extracted), or
     *  - an exception occurs (and in this case is caught)
     *
     *  If the function inserts no samples, failbit is set.
     */
    istream_type& 
    operator>>(streambuf_type* sb);
    //@}
    
    /**
     *  @brief  Sample counting
     *  @return  The number of samples extracted by the previous
     *           unformatted input function dispatched for this stream.
     */
    inline streamsize 
    gcount() const 
    { return m_gcount; }
    
    /**
     *  @name Unformatted Input Functions
     *
     *  All the unformatted input functions have some common behavior.
     *  Each starts by constructing a temporary object of type
     *  snd::basic_istream::sentry.  This has several effects, concluding
     *  with the setting of a status flag; see the sentry documentation
     *  for more.
     *
     *  If the sentry status is good, the function tries to extract
     *  whatever data is appropriate for the type of the argument.
     *
     *  The number of samples extracted is stored for later retrieval
     *  by gcount().
     *
     *  XXX todo?
     *  If an exception is thrown during extraction, ios_base::badbit
     *  will be turned on in the stream's error state without causing an
     *  ios_base::failure to be thrown.  The original exception will then
     *  be rethrown.
     */
    //@{
    /**
     *  @brief  Simple extraction.
     *  @return  A sample, or eof().
     *
     *  Tries to extract a sample.  If none are available, sets failbit
     *  and returns false.
     */
    bool 
    get(sample_type& s);

    /**
     *  @brief  Looking ahead in the stream
     *  @return  The next sample.
     *
     *  If, after constructing the sentry object, @c good() is false,
     *  returns @c false.  Otherwise reads but does not extract
     *  the next input sample.
     */
    bool
    peek(sample_type& s);
    
    /**
     *  @brief  Extraction.
     *  @param  s  A sample array.
     *  @param  n  Maximum number of samples to store.
     *  @return  *this
     *
     *  If the stream state is @c good(), extracts samples and stores
     *  them into @a s until one of the following happens:
     *  - @a n samples are stored
     *  - the end of input sequence is reached, in which case the error
     *    state is set to @c failbit|eofbit.
     *
     */
    istream_type& 
    read(sample_type* s, streamsize n);
    
    /**
     *  @brief  Extraction until the buffer is exhausted, but no more.
     *  @param  s  A sample array.
     *  @param  n  Maximum number of samples to store.
     *  @return  The number of samples extracted.
     *
     *  Extracts samples and stores them into @a s depending on the
     *  number of samples remaining in the streambuf's buffer,
     *  @c rdbuf()->in_avail(), called @c A here:
     *  - if @c A @c == @c -1, sets eofbit and extracts no samples
     *  - if @c A @c == @c 0, extracts no samples
     *  - if @c A @c > @c 0, extracts @c min(A,n)
     *
     *  The goal is to empty the current buffer, and to not request any
     *  more from the external input sequence controlled by the streambuf.
     */
    streamsize 
    readsome(sample_type* s, streamsize n);
    
    /**
     *  @brief  Synchronizing the stream buffer.
     *  @return  0 on success, -1 on failure
     *
     *  If @c rdbuf() is a null pointer, returns -1.
     *
     *  Otherwise, calls @c rdbuf()->pubsync(), and if that returns -1,
     *  sets badbit and returns -1.
     *
     *  Otherwise, returns 0.
     *
     *  @note  This function does not count the number of samples
     *         extracted, if any, and therefore does not affect the next
     *         call to @c gcount().
     */
    int 
    sync();
    
    /**
     *  @brief  Getting the current read position.
     *  @return  A file position object.
     *
     *  If @c fail() is not false, returns @c pos_type(-1) to indicate
     *  failure.  Otherwise returns @c rdbuf()->pubseekoff(0,cur,in).
     *
     *  @note  This function does not count the number of samples
     *         extracted, if any, and therefore does not affect the next
     *         call to @c gcount().
     */
    pos_type 
    tellg();
    
    /**
     *  @brief  Changing the current read position.
     *  @param  pos  A file position object.
     *  @return  *this
     *
     *  If @c fail() is not true, calls @c rdbuf()->pubseekpos(pos).  If
     *  that function fails, sets failbit.
     *
     *  @note  This function does not count the number of samples
     *         extracted, if any, and therefore does not affect the next
     *         call to @c gcount().
     */
    istream_type& 
    seekg(pos_type);
    
    /**
     *  @brief  Changing the current read position.
     *  @param  off  A file offset object.
     *  @param  dir  The direction in which to seek.
     *  @return  *this
     *
     *  If @c fail() is not true, calls @c rdbuf()->pubseekoff(off,dir).
     *  If that function fails, sets failbit.
     *
     *  @note  This function does not count the number of samples
     *         extracted, if any, and therefore does not affect the next
     *         call to @c gcount().
     */
    istream_type& 
    seekg(off_type, ios_base::seekdir);
    //@}
    
protected:
    explicit 
    basic_istream(): m_gcount(streamsize(0)) { }
};

/**
 *  @brief  Performs setup work for input streams.
 *
 *  Objects of this class are created before all of the standard
 *  extractors are run.  It is responsible for "exception-safe prefix and
 *  suffix operations,".
 */
template<typename SampleT, typename SampleTraits>
class basic_istream<SampleT, SampleTraits>::sentry
{
public:
    /// Easy access to dependant types.
    typedef SampleTraits 					            traits_type;
    typedef basic_streambuf<SampleT, SampleTraits> 		streambuf_type;
    typedef basic_istream<SampleT, SampleTraits> 		istream_type;
    
    /**
     *  @brief  The constructor performs all the work.
     *  @param  is  The input stream to guard.
     *
     *  If the stream state is good (@a is.good() is true), then the
     *  following actions are performed, otherwise the sentry state is
     *  false ("not okay") and failbit is set in the stream state.
     *
     *  The sentry's preparatory actions are:
     *
     *  -# if the stream is tied to an output stream, @c is.tie()->flush()
     *     is called to synchronize the output sequence
     *
     *  If the stream state is still good, then the sentry state becomes
     *  true ("okay").
     */
    explicit 
    sentry(basic_istream<SampleT, SampleTraits>& is);
    
    /**
     *  @brief  Quick status checking.
     *  @return  The sentry state.
     *
     *  For ease of use, sentries may be converted to booleans.  The
     *  return value is that of the sentry state (true == okay).
     */
    operator bool() const { return m_ok; }
    
private:
    bool m_ok;
};

/**
 *  @brief  Merging istream and ostream capabilities.
 *
 *  This class multiply inherits from the input and output stream classes
 *  simply to provide a single interface.
 */
template<typename SampleT, typename SampleTraits>
class basic_iostream
    : public basic_istream<SampleT, SampleTraits>, 
      public basic_ostream<SampleT, SampleTraits>
{
public:
    
    typedef SampleT                                 sample_type;
    typedef typename SampleTraits::pos_type 		pos_type;
    typedef typename SampleTraits::off_type 		off_type;
    typedef SampleTraits                    		traits_type;
    
    typedef basic_istream<SampleT, SampleTraits>		istream_type;
    typedef basic_ostream<SampleT, SampleTraits>		ostream_type;
    
    /**
     *  @brief  Constructor does nothing.
     *
     *  Both of the parent classes are initialized with the same
     *  streambuf pointer passed to this constructor.
     */
    explicit 
    basic_iostream(basic_streambuf<SampleT, SampleTraits>* sb)
        : istream_type(), ostream_type()
    { this->init(sb); }
    
    /**
     *  @brief  Destructor does nothing.
     */
    virtual 
    ~basic_iostream() { }
    
protected:
    explicit 
    basic_iostream() : istream_type(), ostream_type()
    { }
};

// standard manipulators, eat silence?


template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>::sentry::
sentry(basic_istream<SampleT, SampleTraits>& in) : m_ok(false)
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    if (in.good())
	{
        if (in.tie())
            in.tie()->flush();

        const SampleT s;
        
        /*
          Try and get next sample from the streambuf,
          if it isn't possible set eofbit.
        */
        streambuf_type* sb = in.rdbuf();
        if(!sb->sgets(s)) err |= ios_base::eofbit;
    }
    
    if (in.good() && err == ios_base::goodbit)
        m_ok = true;
    else
    {
        err |= ios_base::failbit;
        in.setstate(err);
    }
}

template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
operator>>(istream_type& (*pf)(istream_type&))
{ return pf(*this); }

template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
operator>>(ios_type& (*pf)(ios_type&))
{
    pf(*this);
    return *this;
}

template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
operator>>(ios_base& (*pf)(ios_base&))
{
    pf(*this);
    return *this;
}

template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
operator>>(streambuf_type* sbout)
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    sentry cerb(*this);
    if (cerb && sbout)
    {
        try
        {
            if (!copy_streambufs(this->rdbuf(), sbout))
                err |= ios_base::failbit;
        }
        catch(...)
        { this->m_setstate(ios_base::failbit); }
    }
    else if (!sbout)
        err |= ios_base::failbit;
    if (err)
        this->setstate(err);
    return *this;
}

template<typename SampleT, typename SampleTraits>
bool
basic_istream<SampleT, SampleTraits>::
get(SampleT& s)
{
    m_gcount = 0;
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    sentry cerb(*this);
    if (cerb)
    {
        try
        {
            if(this->rdbuf()->sbumps(s))            
                m_gcount = 1;
            else
                err |= ios_base::eofbit;
        }
        catch(...)
        { this->m_setstate(ios_base::badbit); }
    }
    if (!m_gcount)
        err |= ios_base::failbit;
    if (err) {
        this->setstate(err);
        return false;
    }
    
    return true;
}


template<typename SampleT, typename SampleTraits>
bool
basic_istream<SampleT, SampleTraits>::
peek(sample_type& s)
{
    m_gcount = 0;
    sentry cerb(*this);
    if (!cerb) return false;
    
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    try
    {
        if(!this->rdbuf()->sgets(s))
            err |= ios_base::eofbit;
    }
    catch(...)
    { this->m_setstate(ios_base::badbit); }
    
    if (err) {
        this->setstate(err);
        return false;
    }
    return true;
}

template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
read(sample_type* s, streamsize n)
{
    m_gcount = 0;
    sentry cerb(*this);
    if (cerb)
    {
        ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
        try
        {
            m_gcount = this->rdbuf()->sgetn(s, n);
            if (m_gcount != n)
                err |= (ios_base::eofbit | ios_base::failbit);
        }
        catch(...)
        { this->m_setstate(ios_base::badbit); }
        if (err)
            this->setstate(err);
    }
    return *this;
}

template<typename SampleT, typename SampleTraits>
streamsize
basic_istream<SampleT, SampleTraits>::
readsome(sample_type* s, streamsize n)
{
    m_gcount = 0;
    sentry cerb(*this);
    if (cerb)
    {
        ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
        try
        {
            const streamsize num = this->rdbuf()->in_avail();
            if (num > 0)
                m_gcount = this->rdbuf()->sgetn(s, std::min(num, n));
            else if (num == -1)
                err |= ios_base::eofbit;
        }
        catch(...)
        { this->m_setstate(ios_base::badbit); }
        if (err)
            this->setstate(err);
    }
    return m_gcount;
}

template<typename SampleT, typename SampleTraits>
int
basic_istream<SampleT, SampleTraits>::
sync(void)
{
    int ret = -1;
    sentry cerb(*this);
    if (cerb)
    {
        ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
        try
        {
            streambuf_type* sb = this->rdbuf();
            if (sb)
            {
                if (sb->pubsync() == -1)
                    err |= ios_base::badbit;
                else
                    ret = 0;
            }
        }
        catch(...)
        { this->m_setstate(ios_base::badbit); }
        if (err)
            this->setstate(err);
    }
    return ret;
}

template<typename SampleT, typename SampleTraits>
typename basic_istream<SampleT, SampleTraits>::pos_type
basic_istream<SampleT, SampleTraits>::
tellg(void)
{
    pos_type ret = pos_type(-1);
    try
    {
        if (!this->fail())
            ret = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::in);
    }
    catch(...)
    { this->m_setstate(ios_base::badbit); }
    return ret;
}

template<typename SampleT, typename SampleTraits>
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
seekg(pos_type pos)
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    try
    {
        if (!this->fail())
        {
            const pos_type p = this->rdbuf()->pubseekpos(pos,
                                                         ios_base::in);
            
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
basic_istream<SampleT, SampleTraits>&
basic_istream<SampleT, SampleTraits>::
seekg(off_type off, ios_base::seekdir dir)
{
    ios_base::iostate err = ios_base::iostate(ios_base::goodbit);
    try
    {
        if (!this->fail())
        {
            const pos_type p = this->rdbuf()->pubseekoff(off, dir,
                                                         ios_base::in);
            
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

#endif	/* SND_ISTREAM_HPP */

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
