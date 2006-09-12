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

#ifndef SOUND_ITERATOR_HPP
#define SOUND_ITERATOR_HPP 1

#include <iterator>

#include "soundfwd.hpp"

namespace snd
{

template<typename Iterator>
class sound_iterator
{
protected:
    Iterator m_current;
    
public:
    typedef typename std::iterator_traits<Iterator>::iterator_category  iterator_category;
    typedef typename std::iterator_traits<Iterator>::value_type         value_type;
    typedef typename std::iterator_traits<Iterator>::difference_type    difference_type;
    typedef typename std::iterator_traits<Iterator>::reference          reference;
    typedef typename std::iterator_traits<Iterator>::pointer            pointer;
    
    sound_iterator() : m_current(Iterator()) { }
    
    explicit
    sound_iterator(const Iterator& i) : m_current(i) { }
    
    // Allow iterator to const_iterator conversion
    template<typename Iter>
    inline sound_iterator(const sound_iterator<Iter>& i)
	: m_current(i.base()) { }
    
    // Forward iterator requirements
    reference
    operator*() const
    { return *m_current; }
    
    pointer
    operator->() const
    { return m_current; }
    
    sound_iterator&
    operator++()
    {
	++m_current;
	return *this;
    }
    
    sound_iterator
    operator++(int)
    { return sound_iterator(m_current++); }
    
    // Bidirectional iterator requirements
    sound_iterator&
    operator--()
    {
	--m_current;
	return *this;
    }
    
    sound_iterator
    operator--(int)
    { return sound_iterator(m_current--); }
    
    // Random access iterator requirements
    reference
    operator[](const difference_type& n) const
    { return m_current[n]; }
    
    sound_iterator&
    operator+=(const difference_type& n)
    { m_current += n; return *this; }
    
    sound_iterator
    operator+(const difference_type& n) const
    { return sound_iterator(m_current + n); }
    
    sound_iterator&
    operator-=(const difference_type& n)
    { m_current -= n; return *this; }
    
    sound_iterator
    operator-(const difference_type& n) const
    { return sound_iterator(m_current - n); }
    
    const Iterator&
    base() const
    { return m_current; }
};

// Note: In what follows, the left- and right-hand-side iterators are
// allowed to vary in types (conceptually in cv-qualification) so that
// comparaison between cv-qualified and non-cv-qualified iterators be
// valid.  However, the greedy and unfriendly operators in std::rel_ops
// will make overload resolution ambiguous (when in scope) if we don't
// provide overloads whose operands are of the same type.  Can someone
// remind me what generic programming is about? -- Gaby

// Forward iterator requirements
template<typename IteratorL, typename IteratorR>
inline bool
operator==(const sound_iterator<IteratorL>& lhs,
           const sound_iterator<IteratorR>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename Iterator>
inline bool
operator==(const sound_iterator<Iterator>& lhs,
           const sound_iterator<Iterator>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator!=(const sound_iterator<IteratorL>& lhs,
           const sound_iterator<IteratorR>& rhs)
{ return lhs.base() != rhs.base(); }

template<typename Iterator>
inline bool
operator!=(const sound_iterator<Iterator>& lhs,
           const sound_iterator<Iterator>& rhs)
{ return lhs.base() != rhs.base(); }

// Random access iterator requirements
template<typename IteratorL, typename IteratorR>
inline bool
operator<(const sound_iterator<IteratorL>& lhs,
          const sound_iterator<IteratorR>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename Iterator>
inline bool
operator<(const sound_iterator<Iterator>& lhs,
          const sound_iterator<Iterator>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>(const sound_iterator<IteratorL>& lhs,
          const sound_iterator<IteratorR>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename Iterator>
inline bool
operator>(const sound_iterator<Iterator>& lhs,
          const sound_iterator<Iterator>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator<=(const sound_iterator<IteratorL>& lhs,
           const sound_iterator<IteratorR>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename Iterator>
inline bool
operator<=(const sound_iterator<Iterator>& lhs,
           const sound_iterator<Iterator>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>=(const sound_iterator<IteratorL>& lhs,
           const sound_iterator<IteratorR>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename Iterator>
inline bool
operator>=(const sound_iterator<Iterator>& lhs,
           const sound_iterator<Iterator>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline typename sound_iterator<IteratorL>::difference_type
operator-(const sound_iterator<IteratorL>& lhs,
          const sound_iterator<IteratorR>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator>
inline sound_iterator<Iterator>
operator+(typename sound_iterator<Iterator>::difference_type
          n, const sound_iterator<Iterator>& i)
{ return sound_iterator<Iterator>(i.base() + n); }

} // namespace snd

#endif

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
