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

#ifndef SND_BASIC_IOS_HPP
#define SND_BASIC_IOS_HPP 1

//#include "streambuf_iterator.hpp"

#include "iosfwd.hpp"
#include "ios_base.hpp"

namespace snd
{

/**
 *  @brief  Virtual base class for all stream classes.
 *
 *  Most of the member functions called dispatched on stream objects
 *  
 */
template<typename SampleT, typename SampleTraits>
class basic_ios : public ios_base
{
public:
    
    typedef SampleT                                     sample_type;
    typedef typename SampleTraits::int_type             int_type;
    typedef typename SampleTraits::pos_type             pos_type;
    typedef typename SampleTraits::off_type             off_type;
    typedef SampleTraits                                traits_type;
    
protected:
    
    basic_ostream<SampleT, SampleTraits>*            m_tie;
    basic_streambuf<SampleT, SampleTraits>*          m_streambuf;
    
public:

    //@{
    /**
     *  @brief  The quick-and-easy status check.
     *
     *  This allows you to write constructs such as
     *  "if (!a_stream) ..." and "while (a_stream) ..."
     */
    operator void*() const
    { return this->fail() ? 0 : const_cast<basic_ios*>(this); }
    
    bool
    operator!() const
    { return this->fail(); }
    //@}
    
    /**
     *  @brief  Returns the error state of the stream buffer.
     *  @return  A bit pattern (well, isn't everything?)
     *
     *  See snd::ios_base::iostate for the possible bit values.  Most
     *  users will call one of the interpreting wrappers, e.g., good().
     */
    iostate
    rdstate() const
    { return m_streambuf_state; }
    
    /**
     *  @brief  [Re]sets the error state.
     *  @param  state  The new state flag(s) to set.
     *
     *  See snd::ios_base::iostate for the possible bit values.  Most
     *  users will not need to pass an argument.
     */
    void
    clear(iostate state = goodbit)
    {
        if (this->rdbuf())
            m_streambuf_state = state;
        else
            m_streambuf_state = state | badbit;
    }
    
    /**
     *  @brief  Sets additional flags in the error state.
     *  @param  state  The additional state flag(s) to set.
     *
     *  See snd::ios_base::iostate for the possible bit values.
     */
    void
    setstate(iostate state)
    { this->clear(this->rdstate() | state); }
        
    /**
     *  @brief  Fast error checking.
     *  @return  True if no error flags are set.
     *
     *  A wrapper around rdstate.
     */
    bool
    good() const
    { return this->rdstate() == 0; }
    
    /**
     *  @brief  Fast error checking.
     *  @return  True if the eofbit is set.
     *
     *  Note that other iostate flags may also be set.
     */
    bool
    eof() const
    { return (this->rdstate() & eofbit) != 0; }
    
    /**
     *  @brief  Fast error checking.
     *  @return  True if either the badbit or the failbit is set.
     *
     *  Checking the badbit in fail() is historical practice.
     *  Note that other iostate flags may also be set.
     */
    bool
    fail() const
    { return (this->rdstate() & (badbit | failbit)) != 0; }
    
    /**
     *  @brief  Fast error checking.
     *  @return  True if the badbit is set.
     *
     *  Note that other iostate flags may also be set.
     */
    bool
    bad() const
    { return (this->rdstate() & badbit) != 0; }

    // Constructor/destructor:
    /**
     *  @brief  Constructor performs initialization.
     *
     *  The parameter is passed by derived streams.
     */
    explicit
    basic_ios(basic_streambuf<SampleT, SampleTraits>* sb)
        : ios_base(), m_tie(0), m_streambuf(0)
    { this->init(sb); }
    
    /**
     *  @brief  Empty.
     *
     *  The destructor does nothing.  More specifically, it does not
     *  destroy the streambuf held by rdbuf().
     */
    virtual
    ~basic_ios() { }
    
    // Members:
    /**
     *  @brief  Fetches the current @e tied stream.
     *  @return  A pointer to the tied stream, or NULL if the stream is
     *           not tied.
     *
     *  A stream may be @e tied (or synchronized) to a second output
     *  stream.  When this stream performs any I/O, the tied stream is
     *  first flushed.
     */
    basic_ostream<SampleT, SampleTraits>*
    tie() const
    { return m_tie; }
    
    /**
     *  @brief  Ties this stream to an output stream.
     *  @param  tiestr  The output stream.
     *  @return  The previously tied output stream, or NULL if the stream
     *           was not tied.
     *
     *  This sets up a new tie; see tie() for more.
     */
    basic_ostream<SampleT, SampleTraits>*
    tie(basic_ostream<SampleT, SampleTraits>* tiestr)
    {
        basic_ostream<SampleT, SampleTraits>* old = m_tie;
        m_tie = tiestr;
        return old;
    }
    
    /**
     *  @brief  Accessing the underlying buffer.
     *  @return  The current stream buffer.
     *
     *  This does not change the state of the stream.
     */
    basic_streambuf<SampleT, SampleTraits>*
    rdbuf() const
    { return m_streambuf; }
    
    /**
     *  @brief  Changing the underlying buffer.
     *  @param  sb  The new stream buffer.
     *  @return  The previous stream buffer.
     *
     *  Associates a new buffer with the current stream, and clears the
     *  error state.
     *
     *  Due to historical accidents which the LWG refuses to correct, the
     *  I/O library suffers from a design error:  this function is hidden
     *  in derived classes by overrides of the zero-argument @c rdbuf(),
     *  which is non-virtual for hysterical raisins.  As a result, you
     *  must use explicit qualifications to access this function via any
     *  derived class.  For example:
     *
     *  @code
     *  snd::fstream     foo;         // or some other derived type
     *  snd::streambuf*  p = .....;
     *
     *  foo.ios::rdbuf(p);            // ios == basic_ios<char>
     *  @endcode
     */
    basic_streambuf<SampleT, SampleTraits>*
    rdbuf(basic_streambuf<SampleT, SampleTraits>* sb)
    {
        basic_streambuf<SampleT, SampleTraits>* old = m_streambuf;
        m_streambuf = sb;
        this->clear();
        return old;
    }

    
protected:
   
    /**
     *  @brief  Empty.
     *
     *  The default constructor does nothing and is not normally
     *  accessible to users.
     */
    basic_ios()
        : ios_base(), m_streambuf(0)
    { }
    
    /**
     *  @brief  All setup is performed here.
     *
     *  This is called from the public constructor.  It is not virtual and
     *  cannot be redefined.
     */
    void
    init(basic_streambuf<SampleT, SampleTraits>* sb)
    {
        // not sure about this.
        ios_base::m_init();
        
        m_tie = 0;
        m_streambuf = sb;
        m_streambuf_state = sb ? goodbit : badbit;
    }

};

} // namespace snd

#endif /* SND_BASIC_IOS_HPP */

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
