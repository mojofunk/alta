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

#ifndef SND_IOS_BASE_HPP
#define SND_IOS_BASE_HPP 1

#include <string>

#include <glib/gatomic.h>

namespace snd
{

enum Ios_Fmtflags 
{ 
    s_dither 	= 1L << 0,
    s_ios_fmtflags_end = 1L << 16 
};

inline Ios_Fmtflags
operator&(Ios_Fmtflags a, Ios_Fmtflags b)
{ return Ios_Fmtflags(static_cast<int>(a) & static_cast<int>(b)); }

inline Ios_Fmtflags
operator|(Ios_Fmtflags a, Ios_Fmtflags b)
{ return Ios_Fmtflags(static_cast<int>(a) | static_cast<int>(b)); }

inline Ios_Fmtflags
operator^(Ios_Fmtflags a, Ios_Fmtflags b)
{ return Ios_Fmtflags(static_cast<int>(a) ^ static_cast<int>(b)); }

inline Ios_Fmtflags&
operator|=(Ios_Fmtflags& a, Ios_Fmtflags b)
{ return a = a | b; }

inline Ios_Fmtflags&
operator&=(Ios_Fmtflags& a, Ios_Fmtflags b)
{ return a = a & b; }

inline Ios_Fmtflags&
operator^=(Ios_Fmtflags& a, Ios_Fmtflags b)
{ return a = a ^ b; }

inline Ios_Fmtflags
operator~(Ios_Fmtflags a)
{ return Ios_Fmtflags(~static_cast<int>(a)); }


enum Ios_Openmode 
{ 
    s_app 		= 1L << 0,
    s_ate 		= 1L << 1,
    s_in 		= 1L << 2,
    s_out 		= 1L << 3,
    s_trunc 	= 1L << 4,
    s_ios_openmode_end = 1L << 16 
};

inline Ios_Openmode
operator&(Ios_Openmode a, Ios_Openmode b)
{ return Ios_Openmode(static_cast<int>(a) & static_cast<int>(b)); }

inline Ios_Openmode
operator|(Ios_Openmode a, Ios_Openmode b)
{ return Ios_Openmode(static_cast<int>(a) | static_cast<int>(b)); }

inline Ios_Openmode
operator^(Ios_Openmode a, Ios_Openmode b)
{ return Ios_Openmode(static_cast<int>(a) ^ static_cast<int>(b)); }

inline Ios_Openmode&
operator|=(Ios_Openmode& a, Ios_Openmode b)
{ return a = a | b; }

inline Ios_Openmode&
operator&=(Ios_Openmode& a, Ios_Openmode b)
{ return a = a & b; }

inline Ios_Openmode&
operator^=(Ios_Openmode& a, Ios_Openmode b)
{ return a = a ^ b; }

inline Ios_Openmode
operator~(Ios_Openmode a)
{ return Ios_Openmode(~static_cast<int>(a)); }


enum Ios_Iostate
{ 
    s_goodbit 	= 0,
    s_badbit 		= 1L << 0,
    s_eofbit 		= 1L << 1,
    s_failbit		= 1L << 2,
    s_ios_iostate_end = 1L << 16 
};

inline Ios_Iostate
operator&(Ios_Iostate a, Ios_Iostate b)
{ return Ios_Iostate(static_cast<int>(a) & static_cast<int>(b)); }

inline Ios_Iostate
operator|(Ios_Iostate a, Ios_Iostate b)
{ return Ios_Iostate(static_cast<int>(a) | static_cast<int>(b)); }

inline Ios_Iostate
operator^(Ios_Iostate a, Ios_Iostate b)
{ return Ios_Iostate(static_cast<int>(a) ^ static_cast<int>(b)); }

inline Ios_Iostate&
operator|=(Ios_Iostate& a, Ios_Iostate b)
{ return a = a | b; }

inline Ios_Iostate&
operator&=(Ios_Iostate& a, Ios_Iostate b)
{ return a = a & b; }

inline Ios_Iostate&
operator^=(Ios_Iostate& a, Ios_Iostate b)
{ return a = a ^ b; }

inline Ios_Iostate
operator~(Ios_Iostate a)
{ return Ios_Iostate(~static_cast<int>(a)); }

enum Ios_Seekdir 
{ 
    s_beg = 0,
    s_cur = 1,
    s_end = 2,
    s_ios_seekdir_end = 1L << 16 
};

class ios_base
{
public:
   
    // this class is unused until I decide whether or
    // or not to support stream exceptions
    class failure : public std::exception
    {
    public:
        
        explicit
        failure(const std::string& str) throw();
        
        // This declaration is not useless:
        // http://gcc.gnu.org/onlinedocs/gcc-3.0.2/gcc_6.html#SEC118
        virtual
        ~failure() throw();
        
        virtual const char*
        what() const throw();
        
    private:
        std::string m_msg;
    };
    
    typedef Ios_Fmtflags fmtflags;
    
    static const fmtflags dither = fmtflags(s_dither);

    /**
     *  @brief This is a bitmask type.
     *
     *  @c "Ios_Iostate" is implementation-defined, but it is valid to
     *  perform bitwise operations on these values and expect the Right
     *  Thing to happen.  Defined objects of type iostate are:
     *  - badbit
     *  - eofbit
     *  - failbit
     *  - goodbit
    */
    typedef Ios_Iostate iostate;

    /// Indicates a loss of integrity in an input or output sequence (such
    /// as an irrecoverable read error from a file).
    static const iostate badbit =	iostate(s_badbit);

    /// Indicates that an input operation reached the end of an input sequence.
    static const iostate eofbit =	iostate(s_eofbit);

    /// Indicates that an input operation failed to read the expected
    /// characters, or that an output operation failed to generate the
    /// desired characters.
    static const iostate failbit =	iostate(s_failbit);

    /// Indicates all is well.
    static const iostate goodbit =	iostate(s_goodbit);
    
    /**
     *  @brief This is a bitmask type.
     *
     *  @c "Ios_Openmode" is implementation-defined, but it is valid to
     *  perform bitwise operations on these values and expect the Right
     *  Thing to happen.  Defined objects of type openmode are:
     *  - app
     *  - ate
     *  - in
     *  - out
     *  - trunc
     */
    typedef Ios_Openmode openmode;
    
    /// Seek to end before each write.
    static const openmode app =		openmode(s_app);
    
    /// Open and seek to end immediately after opening.
    static const openmode ate =		openmode(s_ate);
    
    /// Open for input.  Default for @c ifstream and fstream.
    static const openmode in =		openmode(s_in);
    
    /// Open for output.  Default for @c ofstream and fstream.
    static const openmode out =		openmode(s_out);
    
    /// Open for input.  Default for @c ofstream.
    static const openmode trunc =	openmode(s_trunc);
    
    typedef Ios_Seekdir seekdir;
    
    /// Request a seek relative to the beginning of the stream.
    static const seekdir beg =		seekdir(s_beg);
    
    /// Request a seek relative to the current position within the sequence.
    static const seekdir cur =		seekdir(s_cur);
    
    /// Request a seek relative to the current end of the sequence.
    static const seekdir end =		seekdir(s_end);
    
    typedef int io_state;
    typedef int open_mode;
    typedef int seek_dir;
        
protected:
    
    fmtflags		m_flags;
//    iostate		m_exception;
    iostate		m_streambuf_state;
    
    void
    m_init();
    
public:
  
    // Class snd::ios_base::Init
    // Used to initialize standard streams.
    class Init
    {
        friend class ios_base;
    public:
        Init();
        ~Init();
        
    private:
        static gint       s_refcount;
    };
    
    /**
     *  @brief  Access to format flags.
     *  @return  The format control flags for both input and output.
     */
    inline fmtflags
    flags() const { return m_flags; }
    
    /**
     *  @brief  Setting new format flags all at once.
     *  @param  fmtfl  The new flags to set.
     *  @return  The previous format control flags.
     *
     *  This function overwrites all the format flags with @a fmtfl.
     */
    inline fmtflags
    flags(fmtflags fmtfl)
    {
        fmtflags old = m_flags;
        m_flags = fmtfl;
        return old;
    }
    
    /**
     *  @brief  Setting new format flags.
     *  @param  fmtfl  Additional flags to set.
     *  @return  The previous format control flags.
     *
     *  This function sets additional flags in format control.  Flags that
     *  were previously set remain set.
     */
    inline fmtflags
    setf(fmtflags fmtfl)
    {
        fmtflags old = m_flags;
        m_flags |= fmtfl;
        return old;
    }
    
    /**
     *  @brief  Setting new format flags.
     *  @param  fmtfl  Additional flags to set.
     *  @param  mask  The flags mask for @a fmtfl.
     *  @return  The previous format control flags.
     *
     */
    inline fmtflags
    setf(fmtflags fmtfl, fmtflags mask)
    {
        fmtflags old = m_flags;
        m_flags &= ~mask;
        m_flags |= (fmtfl & mask);
        return old;
    }
    
    /**
     *  @brief  Clearing format flags.
     *  @param  mask  The flags to unset.
     *
     *  This function clears @a mask in the format flags.
     */
    inline void
    unsetf(fmtflags mask) { m_flags &= ~mask; }
    
    virtual ~ios_base();
    
protected:
    ios_base();
    
private:
    ios_base(const ios_base&);
    
    ios_base&
    operator=(const ios_base&);
};

} // namespace snd

#endif /* SND_IOS_BASE_HPP */

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
