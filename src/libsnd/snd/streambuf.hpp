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

#ifndef SND_STREAMBUF_HPP
#define SND_STREAMBUF_HPP 1

#include "iosfwd.hpp"
#include "ios_base.hpp"

namespace snd
{

template<typename SampleT, typename SampleTraits>
streamsize
copy_streambufs(basic_streambuf<SampleT, SampleTraits>* sbin,
                basic_streambuf<SampleT, SampleTraits>* sbout);

/**
 *  @brief  The actual work of input and output (interface).
 *
 *  This is a base class.  Derived stream buffers each control a
 *  pair of sample sequences:  one for input, and one for output.
 *
 *  Section [27.5.1] of the standard describes the requirements and
 *  behavior of stream buffer classes.  That section (three paragraphs)
 *  is reproduced here, for simplicity and accuracy.
 *
 *  -# Stream buffers can impose various constraints on the sequences
 *     they control.  Some constraints are:
 *     - The controlled input sequence can be not readable.
 *     - The controlled output sequence can be not writable.
 *     - The controlled sequences can be associated with the contents of
 *       other representations for sample sequences, such as external
 *       files.
 *     - The controlled sequences can support operations @e directly to or
 *       from associated sequences.
 *     - The controlled sequences can impose limitations on how the
 *       program can read samples from a sequence, write samples to
 *       a sequence, put samples back into an input sequence, or alter
 *       the stream position.
 *     .
 *  -# Each sequence is characterized by three pointers which, if non-null,
 *     all point into the same @c SampleT array object.  The array object
 *     represents, at any moment, a (sub)sequence of samples from the
 *     sequence.  Operations performed on a sequence alter the values
 *     stored in these pointers, perform reads and writes directly to or
 *     from associated sequences, and alter "the stream position" and
 *     conversion state as needed to maintain this subsequence relationship.
 *     The three pointers are:
 *     - the <em>beginning pointer</em>, or lowest element address in the
 *       array (called @e xbeg here);
 *     - the <em>next pointer</em>, or next element address that is a
 *       current candidate for reading or writing (called @e xnext here);
 *     - the <em>end pointer</em>, or first element address beyond the
 *       end of the array (called @e xend here).
 *     .
 *  -# The following semantic constraints shall always apply for any set
 *     of three pointers for a sequence, using the pointer names given
 *     immediately above:
 *     - If @e xnext is not a null pointer, then @e xbeg and @e xend shall
 *       also be non-null pointers into the same @c SampleT array, as
 *       described above; otherwise, @e xbeg and @e xend shall also be null.
 *     - If @e xnext is not a null pointer and @e xnext < @e xend for an
 *       output sequence, then a <em>write position</em> is available.
 *       In this case, @e *xnext shall be assignable as the next element
 *       to write (to put, or to store a sample value, into the sequence).
 *     - If @e xnext is not a null pointer and @e xbeg < @e xnext for an
 *       input sequence, then a <em>putback position</em> is available.
 *       In this case, @e xnext[-1] shall have a defined value and is the
 *       next (preceding) element to store a sample that is put back
 *       into the input sequence.
 *     - If @e xnext is not a null pointer and @e xnext< @e xend for an
 *       input sequence, then a <em>read position</em> is available.
 *       In this case, @e *xnext shall have a defined value and is the
 *       next element to read (to get, or to obtain a sample value,
 *       from the sequence).
 */
template<typename SampleT, typename SampleTraits>
class basic_streambuf 
{
public:

    //@{
    /**
     *  These are standard types.  They permit a standardized way of
     *  referring to names of (or names dependant on) the template
     *  parameters, which are specific to the implementation.
     */
    typedef SampleT 					sample_type;
    typedef SampleTraits 				traits_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;
    //@}
    
    typedef basic_streambuf<sample_type, traits_type>  	streambuf_type;
    
    friend class basic_ios<sample_type, traits_type>;
    friend class basic_istream<sample_type, traits_type>;
    friend class basic_ostream<sample_type, traits_type>;
    friend class istreambuf_iterator<sample_type, traits_type>;
    friend class ostreambuf_iterator<sample_type, traits_type>;
    
    friend streamsize
    copy_streambufs<>(streambuf_type* sbin,
                      streambuf_type* sbout);
    
protected:
    //@{
    /**
     *  @if maint
     *  This is based on _IO_FILE, just reordered to be more consistent,
     *  and is intended to be the most minimal abstraction for an
     *  internal buffer.
     *  -  get == input == read
     *  -  put == output == write
     *  @endif
     */
    sample_type* 		m_in_beg;     // Start of get area. 
    sample_type* 		m_in_cur;     // Current read area. 
    sample_type* 		m_in_end;     // End of get area. 
    sample_type* 		m_out_beg;    // Start of put area. 
    sample_type* 		m_out_cur;    // Current put area. 
    sample_type* 		m_out_end;    // End of put area.

  public:
    /// Destructor deallocates no buffer space.
    virtual 
    ~basic_streambuf() 
    { }
    
    //@{
    /**
     *  @brief  Entry points for derived buffer functions.
     *
     *  The public versions of @c pubfoo dispatch to the protected
     *  derived @c foo member functions, passing the arguments (if any)
     *  and returning the result unchanged.
     */
    streambuf_type* 
    pubsetbuf(sample_type* s, streamsize n) 
    { return this->setbuf(s, n); }
    
    pos_type 
    pubseekoff(off_type off, ios_base::seekdir way, 
               ios_base::openmode mode = ios_base::in | ios_base::out)
    { return this->seekoff(off, way, mode); }
    
    pos_type 
    pubseekpos(pos_type sp,
               ios_base::openmode mode = ios_base::in | ios_base::out)
    { return this->seekpos(sp, mode); }
    
    int 
    pubsync() { return this->sync(); }
    //@}
    
    /**
     *  @brief  Looking ahead into the stream.
     *  @return  The number of samples available.
     *
     *  If a read position is available, returns the number of samples
     *  available for reading before the buffer must be refilled.
     *  Otherwise returns the derived @c showmanys().
     */
    streamsize 
    in_avail() 
    { 
	const streamsize ret = this->egptr() - this->gptr();
	return ret ? ret : this->showmanys();
    }
    
    /**
     *  @brief  Getting the next sample.
     *  @param s Destination for next sample.
     *  @return  true If s contains the next sample.
     *
     *  Calls @c sbumps(), and if that function returns
     *  @c false so does this function.  Otherwise return true
     *  and s contains the next sample, @c sgets().
     */
    bool
    snexts(sample_type& s)
    {
        if(this->sbumps(s))
            return this->sgets(s); // should always be true.
        else
            return false;
    }
    
    /**
     *  @brief  Getting the next sample.
     *  @param s Destination for next sample.
     *  @return  true If s contains the next sample.
     *
     *  If the input read position is available, returns that sample
     *  and increments the read pointer, otherwise calls and returns
     *  @c uflow(s). In either case if true is returned s contains 
     *  the next sample from control sequence and read pointer is
     *  incremented. 
     */
    bool
    sbumps(sample_type& s)
    {
        if(this->gptr() < this->egptr())
        {
	    s = *this->gptr();
	    this->gbump(1);
        }
	else 
            return this->uflow(s);
	return true;
    }
    
    /**
     *  @brief  Getting the next sample.
     *  @param s Destination for next sample.
     *  @return  true If s contains the next sample.
     *
     *  If the input read position is available, returns that sample,
     *  otherwise calls and returns @c underflow().  Does not move the 
     *  read position after fetching the sample.
     */
    bool
    sgets(sample_type& s)
    {
        if(this->gptr() < this->egptr())
        {
            s = *this->gptr();
            return true;
        }
	else 
            return this->underflow(s);
    }
    
    /**
     *  @brief  Entry point for xsgetn.
     *  @param  s  A buffer area.
     *  @param  n  A count.
     *
     *  Returns xsgetn(s,n).  The effect is to fill @a s[0] through
     *  @a s[n-1] with samples from the input sequence, if possible.
     */
    streamsize 
    sgetn(sample_type* s, streamsize n)
    { return this->xsgetn(s, n); }
    
    
    
    /**
     *  @brief  Entry point for all single-sample output functions.
     *  @param  s  A sample to output.
     *  @return true If possible.
     *
     *  One of two public output functions.
     *
     *  If a write position is available for the output sequence (i.e.,
     *  the buffer is not full), stores @a s in that position, increments
     *  the position and returns true.  If a write position is not 
     *  available, returns @c overflow(s).
     */
    bool
    sputs(sample_type s)
    {
	if(this->pptr() < this->epptr())
        {
	    *this->pptr() = s;
	    this->pbump(1);
	    return true;
        }
	else
            return this->overflow(s);
    }
    
    /**
     *  @brief  Entry point for all multi-sample output functions.
     *  @param  s  A buffer read area.
     *  @param  n  A count.
     *
     *  One of two public output functions.
     *
     *  Returns xsputn(s,n).  The effect is to write @a s[0] through
     *  @a s[n-1] to the output sequence, if possible.
     */
    streamsize 
    sputn(const sample_type* s, streamsize n)
    { return this->xsputn(s, n); }
    
protected:
    
    /**
     *  @brief  Base constructor.
     *
     *  Only called from derived constructors, and sets up all the
     *  buffer data to zero, including the pointers described in the
     *  basic_streambuf class description.  Note that, as a result,
     *  - the class starts with no read nor write positions available,
     *  - this is not an error
     */
    basic_streambuf()
        : m_in_beg(0), m_in_cur(0), m_in_end(0), 
          m_out_beg(0), m_out_cur(0), m_out_end(0)
    { }

    //@{
    /**
     *  @brief  Access to the get area.
     *
     *  These functions are only available to other protected functions,
     *  including derived classes.
     *
     *  - eback() returns the beginning pointer for the input sequence
     *  - gptr() returns the next pointer for the input sequence
     *  - egptr() returns the end pointer for the input sequence
     */
    sample_type* 
    eback() const { return m_in_beg; }
    
    sample_type* 
    gptr()  const { return m_in_cur;  }
    
    sample_type* 
    egptr() const { return m_in_end; }
    //@}
    
    /**
     *  @brief  Moving the read position.
     *  @param  n  The delta by which to move.
     *
     *  This just advances the read position without returning any data.
     */
    void 
    gbump(int n) { m_in_cur += n; }
    
    /**
     *  @brief  Setting the three read area pointers.
     *  @param  gbeg  A pointer.
     *  @param  gnext  A pointer.
     *  @param  gend  A pointer.
     *  @post  @a gbeg == @c eback(), @a gnext == @c gptr(), and
     *         @a gend == @c egptr()
     */
    void 
    setg(sample_type* gbeg, sample_type* gnext, sample_type* gend)
    {
	m_in_beg = gbeg;
	m_in_cur = gnext;
	m_in_end = gend;
    }
    
    //@{
    /**
     *  @brief  Access to the put area.
     *
     *  These functions are only available to other protected functions,
     *  including derived classes.
     *
     *  - pbase() returns the beginning pointer for the output sequence
     *  - pptr() returns the next pointer for the output sequence
     *  - epptr() returns the end pointer for the output sequence
     */
    sample_type* 
    pbase() const { return m_out_beg; }
    
    sample_type* 
    pptr() const { return m_out_cur; }
    
    sample_type* 
    epptr() const { return m_out_end; }
    //@}
    
    /**
     *  @brief  Moving the write position.
     *  @param  n  The delta by which to move.
     *
     *  This just advances the write position without returning any data.
     */
    void 
    pbump(int n) { m_out_cur += n; }
    
    /**
     *  @brief  Setting the three write area pointers.
     *  @param  pbeg  A pointer.
     *  @param  pend  A pointer.
     *  @post  @a pbeg == @c pbase(), @a pbeg == @c pptr(), and
     *         @a pend == @c epptr()
     */
    void 
    setp(sample_type* pbeg, sample_type* pend)
    { 
	m_out_beg = m_out_cur = pbeg; 
	m_out_end = pend;
    }
    
    /**
     *  @brief  Maniuplates the buffer.
     *
     *  Each derived class provides its own appropriate behavior.  See
     *  the next-to-last paragraph of 
     *  http://gcc.gnu.org/onlinedocs/libstdc++/27_io/howto.html#2 for
     *  more on this function.
     *
     *  @note  Base class version does nothing, returns @c this.
     */
    virtual basic_streambuf<sample_type,SampleTraits>* 
    setbuf(sample_type*, streamsize)
    { return this; }
    
    /**
     *  @brief  Alters the stream positions.
     *
     *  Each derived class provides its own appropriate behavior.
     *  @note  Base class version does nothing, returns a @c pos_type
     *         that represents an invalid stream position.
     */
    virtual pos_type 
    seekoff(off_type, ios_base::seekdir,
            ios_base::openmode /*mode*/ = ios_base::in | ios_base::out)
    { return pos_type(off_type(-1)); } 
    
    /**
     *  @brief  Alters the stream positions.
     *
     *  Each derived class provides its own appropriate behavior.
     *  @note  Base class version does nothing, returns a @c pos_type
     *         that represents an invalid stream position.
     */
    virtual pos_type 
    seekpos(pos_type, 
            ios_base::openmode /*mode*/ = ios_base::in | ios_base::out)
    { return pos_type(off_type(-1)); } 
    
    /**
     *  @brief  Synchronizes the buffer arrays with the controlled sequences.
     *  @return  -1 on failure.
     *
     *  Each derived class provides its own appropriate behavior,
     *  including the definition of "failure".
     *  @note  Base class version does nothing, returns zero.
     */
    virtual int 
    sync() { return 0; }
    
    /**
     *  @brief  Investigating the data available.
     *  @return  An estimate of the number of samples available in the
     *           input sequence, or -1.
     *
     *  If it returns a positive value, then successive calls to
     *  @c underflow() will not return false until at least that
     *  number of samples have been supplied.  If @c showmanys()
     *  returns -1, then calls to @c underflow() or @c uflow() will fail.
     *
     *  @note  Base class version does nothing, returns zero.
     *  @note  The standard adds that "the intention is not only that the
     *         calls [to underflow or uflow] will not return @c eof() but
     *         that they will return "immediately".
     */
    virtual streamsize 
    showmanys() { return 0; }
    
    /**
     *  @brief  Multiple sample extraction.
     *  @param  s  A buffer area.
     *  @param  n  Maximum number of samples to assign.
     *  @return  The number of samples assigned.
     *
     *  Fills @a s[0] through @a s[n-1] with samples from the input
     *  sequence, as if by @c sbumpc().  Stops when either @a n samples
     *  have been copied, or input control sequence is exhausted.
     *
     *  It is expected that derived classes provide a more efficient
     *  implementation by overriding this definition.
     */
    virtual streamsize 
    xsgetn(sample_type* s, streamsize n);
    
    /**
     *  @brief  Fetches more data from the controlled sequence.
     *  @return  The first sample from the <em>pending sequence</em>.
     *
     *  Informally, this function is called when the input buffer is
     *  exhausted (or does not exist, as buffering need not actually be
     *  done).  If a buffer exists, it is "refilled".  If the buffer is
     *  able to be "refilled" then true is returned and s contains the
     *  next sample from the control sequence. false is returned to a 
     *  null pending sequence and the value of s is meaningless.
     *
     *  For a formal definiton of the pending sequence, see a good text
     *  such as Langer & Kreft, or [27.5.2.4.3]/7-14.
     *
     *  A functioning input streambuf can be created by overriding only
     *  this function (no buffer area will be used).  For an example, see
     *  http://gcc.gnu.org/onlinedocs/libstdc++/27_io/howto.html#6
     *
     *  @note  Base class version does nothing, returns false.
     */
    virtual bool 
    underflow(sample_type& s)
    { return false; }
    
    /**
     *  @brief  Fetches more data from the controlled sequence.
     *  @return  The first sample from the <em>pending sequence</em>.
     *
     *  Informally, this function does the same thing as @c underflow(),
     *  and in fact is required to call that function.  It also returns
     *  the new sample in s, like @c underflow(s) does.  However, this
     *  function also moves the read position forward by one.
     */
    virtual bool 
    uflow(sample_type& s) 
    {
        if(this->underflow(s))
        {
            s = *this->gptr();
            this->gbump(1);            
            return true;
        }
        else
            return false;
    }
    
    // Put area:
    /**
     *  @brief  Multiple sample insertion.
     *  @param  s  A buffer area.
     *  @param  n  Maximum number of samples to write.
     *  @return  The number of samples written.
     *
     *  Writes @a s[0] through @a s[n-1] to the output sequence, as if
     *  by @c sputc().  Stops when either @a n samples have been
     *  copied, or when @c sputc() would return @c traits::eof().
     *
     *  It is expected that derived classes provide a more efficient
     *  implementation by overriding this definition.
     */
    virtual streamsize 
    xsputn(const sample_type* s, streamsize n);
    
    /**
     *  @brief  Consumes data from the buffer; writes to the
     *          controlled sequence.
     *  @param  s An additional sample to consume.
     *  @return false to indicate failure.
     *
     *  Informally, this function is called when the output buffer is full
     *  (or does not exist, as buffering need not actually be done).  If a
     *  buffer exists, it is "consumed", with "some effect" on the
     *  controlled sequence.  (Typically, the buffer is written out to the
     *  sequence verbatim.)  In either case, the sample @a s is also
     *  written out, if @a s is true.
     *
     *  For a formal definiton of this function, see a good text
     *  such as Langer & Kreft, or [27.5.2.4.5]/3-7.
     *
     *  A functioning output streambuf can be created by overriding only
     *  this function (no buffer area will be used).
     *
     *  @note  Base class version does nothing, returns false.
     */
    virtual bool 
    overflow(sample_type)
    { return false; }

private:
    
    basic_streambuf(const streambuf_type& sb)
        : m_in_beg(sb.m_in_beg), m_in_cur(sb.m_in_cur), 
          m_in_end(sb.m_in_end), m_out_beg(sb.m_out_beg), 
          m_out_cur(sb.m_out_cur), m_out_end(sb.m_out_cur)
    { }
    
    streambuf_type& 
    operator=(const streambuf_type&) { return *this; };

};

template<typename SampleT, typename SampleTraits>
streamsize
basic_streambuf<SampleT, SampleTraits>::
xsgetn(sample_type* s, streamsize n)
{
    streamsize ret = 0;
    while (ret < n)
    {
        const size_t buf_len = this->egptr() - this->gptr();
        if (buf_len)
        {
            const size_t remaining = n - ret;
            const size_t len = std::min(buf_len, remaining);
            traits_type::copy(s, this->gptr(), len);
            ret += len;
            s += len;
            this->gbump(len);
        }
        
        if (ret < n)
        {
            SampleT tmp;
            if(this->uflow(tmp))
            {
                *s++ = tmp;
                ++ret;
            }
            else
                break;
        }
    }
    return ret;
}

template<typename SampleT, typename SampleTraits>
streamsize
basic_streambuf<SampleT, SampleTraits>::
xsputn(const sample_type* s, streamsize n)
{
    streamsize ret = 0;
    while (ret < n)
    {
        const size_t buf_len = this->epptr() - this->pptr();
        if (buf_len)
        {
            const size_t remaining = n - ret;
            const size_t len = std::min(buf_len, remaining);
            traits_type::copy(this->pptr(), s, len);
            ret += len;
            s += len;
            this->pbump(len);
        }
        
        if (ret < n)
        {
            if(this->overflow(*s))
            {
                ++ret;
                ++s;
            }
            else
		break;
        }
    }
    return ret;
}

// Conceivably, this could be used to implement buffer-to-buffer
// copies, if this was ever desired in an un-ambiguous way by the
// standard.
template<typename SampleT, typename SampleTraits>
streamsize
copy_streambufs(basic_streambuf<SampleT, SampleTraits>* sbin,
                basic_streambuf<SampleT, SampleTraits>* sbout)
{
    streamsize ret = 0;
    SampleT s;

    if(!sbin->sgetc(s)) return ret;
    
    do
    {
        if(!sbout->sputc(s))
            break;
        ++ret;
    } while(sbin->snextc(s));
    return ret;
}

} // namespace snd

#endif /* SND_STREAMBUF_HPP */

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
