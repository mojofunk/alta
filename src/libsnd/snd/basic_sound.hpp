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
  
  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
  
  $Id$
*/


#ifndef BASIC_SOUND_HPP
#define BASIC_SOUND_HPP 1

#include <stdexcept>

// should make this more generic.
// so we aren't dependent on glib
#include <glib/gatomic.h>

#include "debug.hpp"
#include "sound_iterator.hpp"

namespace snd
{

/**
 *  @class basic_sound basic_sound.hpp
 *  @brief  Managing sequences of samples and sample-like objects.
 *
 *  @ingroup Containers
 *  @ingroup Sequences
 *
 *  Meets the requirements of a <a href="tables.html#65">container</a>, a
 *  <a href="tables.html#66">reversible container</a>, and a
 *  <a href="tables.html#67">sequence</a>.  Of the
 *  <a href="tables.html#68">optional sequence requirements</a>, only
 *  @c push_back, @c at, and array access are supported.
 *
 *  @doctodo
 *
 *
 *  @if maint
 *  Documentation?  What's that?
 *  Nathan Myers <ncm@cantrip.org>.
 *
 *  A sound looks like this:
 *
 *  @code
 *                                        [_Rep]
 *                                        m_length
 *   [basic_sound<sample_type>]           m_capacity
 *   m_dataplus                           m_refcount
 *   m_p ---------------->                unnamed array of sample_type
 *  @endcode
 *
 *  Where the m_p points to the first sample in the sound, and
 *  you cast it to a pointer-to-_Rep and subtract 1 to get a
 *  pointer to the header.
 *
 *  This approach has the enormous advantage that a sound object
 *  requires only one allocation.  All the ugliness is confined
 *  within a single pair of inline functions, which each compile to
 *  a single "add" instruction: _Rep::m_data(), and
 *  sound::m_rep(); and the allocation function which gets a
 *  block of raw bytes and with room enough and constructs a _Rep
 *  object at the front.
 *
 *  The reason you want m_data pointing to the sample array and
 *  not the _Rep is so that the debugger can see the sound
 *  contents. (Probably we should add a non-inline member to get
 *  the _Rep for the debugger to use, so users can check the actual
 *  sound length.)
 *
 *  Note that the _Rep object is a POD so that you can have a
 *  static "empty sound" _Rep object already "constructed" before
 *  static constructors have run.  The reference-count encoding is
 *  chosen so that a 0 indicates one reference, so you never try to
 *  destroy the empty-sound _Rep object.
 *
 *  All but the last paragraph is considered pretty conventional
 *  for a C++ sound implementation.
 *  @endif
 */
// 21.3  Template class basic_sound
template<typename SampleType, typename SampleTraits, typename Alloc>
class basic_sound
{
    // Types:
public:
    typedef SampleTraits				    traits_type;
    typedef typename SampleTraits::sample_type		    value_type;
    typedef Alloc					    allocator_type;
    typedef typename Alloc::size_type		            size_type;
    typedef typename Alloc::difference_type		    difference_type;
    typedef typename Alloc::reference		            reference;
    typedef typename Alloc::const_reference		    const_reference;
    typedef typename Alloc::pointer			    pointer;
    typedef typename Alloc::const_pointer		    const_pointer;
    
    typedef sound_iterator<pointer>                         iterator;
    typedef sound_iterator<const_pointer>                   const_iterator;
    typedef std::reverse_iterator<const_iterator>	    const_reverse_iterator;
    typedef std::reverse_iterator<iterator>		    reverse_iterator;
    
private:
    // rep: sound representation
    //   Invariants:
    //   1. Sound contains m_length samples. not m_length + 1 like a
    //      null terminated string.
    //   2. m_capacity >= m_length
    //      Allocated memory is always (m_capacity) * sizeof(SampleType).
    //   3. m_refcount has three states:
    //      -1: leaked, one reference, no ref-copies allowed, non-const.
    //       0: one reference, non-const.
    //     n>0: n + 1 references, operations require a lock, const.
    //   4. All fields==0 is an empty sound; thus, the shared
    //      empty sound representation needs no constructor.
    
    struct rep_base
    {
	size_type		m_length;
	size_type		m_capacity;
	gint    		m_refcount;
    };

    struct rep : rep_base
    {
	// Types:
	typedef typename Alloc::template rebind<char>::other Raw_bytes_alloc;
        
	// (Public) Data members:
        
	// The maximum number of individual sample_type elements of an
	// individual sound is determined by s_max_size. This is the
	// value that will be returned by max_size().  (Whereas npos
	// is the maximum number of bytes the allocator can allocate.)
	// If one was to divvy up the theoretical largest size sound,
	// with a terminating sample and m SampleType elements, it'd
	// look like this:
	// npos = sizeof(rep) + (m * sizeof(SampleType)) + sizeof(SampleType)
	// Solving for m:
	// m = ((npos - sizeof(rep))/sizeof(CharT)) - 1
	// In addition, this implementation quarters this amount.
	static const size_type	s_max_size;
                
        bool
	m_is_leaked() const
        { return this->m_refcount < 0; }
        
        bool
	m_is_shared() const
        { return this->m_refcount > 0; }
        
        void
	m_set_leaked()
        { this->m_refcount = -1; }
        
        void
	m_set_sharable()
        { this->m_refcount = 0; }
        
	void
	m_set_length_and_sharable(size_type n)
	{ 
            this->m_set_sharable();  // One reference.
            this->m_length = n;
        }
        
	SampleType*
	m_refdata() throw()
	{ return reinterpret_cast<SampleType*>(this + 1); }
        
	SampleType*
	m_grab(const Alloc& alloc1, const Alloc& alloc2)
	{
            return (!m_is_leaked() && alloc1 == alloc2)
                ? m_refcopy() : m_clone(alloc1);
	}
        
	// Create & Destroy
	static rep*
	s_create(size_type, size_type, const Alloc&);
        
	void
	m_dispose(const Alloc& a)
	{
            if (g_atomic_int_exchange_and_add(&this->m_refcount, -1) <= 0)
                m_destroy(a);
	}  // XXX MT
        
	void
	m_destroy(const Alloc&) throw();
        
	SampleType*
	m_refcopy() throw()
	{
            g_atomic_int_add(&this->m_refcount, 1);
            return m_refdata();
	}  // XXX MT
        
	SampleType*
	m_clone(const Alloc&, size_type res = 0);
    };
    
    // Use empty-base optimization: http://www.cantrip.org/emptyopt.html
    struct Alloc_hider : Alloc
    {
	Alloc_hider(SampleType* dat, const Alloc& a)
            : Alloc(a), m_p(dat) { }
        
	SampleType* m_p; // The actual data.
    };
    
public:
    // Data Members (public):
    // NB: This is an unsigned type, and thus represents the maximum
    // size that the allocator can hold.
    ///  Value returned by various member functions when they fail.
    static const size_type	npos = static_cast<size_type>(-1);
    
private:
    // Data Members (private):
    mutable Alloc_hider	m_dataplus;
    
    SampleType*
    m_data() const
    { return  m_dataplus.m_p; }
    
    SampleType*
    m_data(SampleType* p)
    { return (m_dataplus.m_p = p); }
    
    rep*
    m_rep() const
    { return &((reinterpret_cast<rep*> (m_data()))[-1]); }
    
    // For the internal use we have functions similar to `begin'/`end'
    // but they do not call m_leak.
    iterator
    m_ibegin() const
    { return iterator(m_data()); }
    
    iterator
    m_iend() const
    { return iterator(m_data() + this->size()); }
    
    void
    m_leak()    // for use in begin() & non-const op[]
    {
	if (!m_rep()->m_is_leaked())
            m_leak_hard();
    }
    
    size_type
    m_check(size_type pos, const char* s) const
    {
	if (pos > this->size())
            throw std::out_of_range(s);
	return pos;
    }
    
    void
    m_check_length(size_type n1, size_type n2, const char* s) const
    {
	if (this->max_size() - (this->size() - n1) < n2)
            throw std::length_error(s);
    }
    
    // NB: m_limit doesn't check for a bad pos value.
    size_type
    m_limit(size_type pos, size_type off) const
    {
	const bool testoff =  off < this->size() - pos;
	return testoff ? off : this->size() - pos;
    }
    
    // True if rep and source do not overlap.
    bool
    m_disjunct(const SampleType* s) const
    {
	return (std::less<const SampleType*>()(s, m_data())
		|| std::less<const SampleType*>()(m_data() + this->size(), s));
    }
    
    // When n = 1 assign is faster than a general copy
    // traits_type::copy/move/assign.
    static void
    m_copy(SampleType* d, const SampleType* s, size_type n)
    {
	if (n == 1)
            traits_type::assign(*d, *s);
	else
            traits_type::copy(d, s, n);
    }
    
    static void
    m_move(SampleType* d, const SampleType* s, size_type n)
    {
	if (n == 1)
            traits_type::assign(*d, *s);
	else
            traits_type::move(d, s, n);	  
    }
    
    static void
    m_assign(SampleType* d, size_type n, SampleType s)
    {
	if (n == 1)
            traits_type::assign(*d, s);
	else
            traits_type::assign(d, n, s);	  
    }
    
    // s_copy_samples is a separate template to permit specialization
    // to optimize for the common case of pointers as iterators.
    template<class Iter>
    static void
    s_copy_samples(SampleType* p, Iter k1, Iter k2)
    {
        for (; k1 != k2; ++k1, ++p)
	    traits_type::assign(*p, *k1); // These types are off.
    }
    
    static void
    s_copy_samples(SampleType* p, iterator k1, iterator k2)
    { s_copy_samples(p, k1.base(), k2.base()); }
    
    static void
    s_copy_samples(SampleType* p, const_iterator k1, const_iterator k2)
    { s_copy_samples(p, k1.base(), k2.base()); }
    
    static void
    s_copy_samples(SampleType* p, SampleType* k1, SampleType* k2)
    { m_copy(p, k1, k2 - k1); }
    
    static void
    s_copy_samples(SampleType* p, const SampleType* k1, const SampleType* k2)
    { m_copy(p, k1, k2 - k1); }
    
    void
    m_mutate(size_type pos, size_type len1, size_type len2);
    
    void
    m_leak_hard();
    
public:
    // Construct/copy/destroy:
    
    /**
     *  @brief  Default constructor creates an empty sound.
     */
    inline
    basic_sound();
    
    /**
     *  @brief  Construct an empty sound using allocator @a a.
     */
    explicit
    basic_sound(const Alloc& a);
    
    /**
     *  @brief  Construct sound with copy of value of @a snd.
     *  @param  snd  Source sound.
     */
    basic_sound(const basic_sound& snd);
    
    /**
     *  @brief  Construct sound as copy of a subsound.
     *  @param  snd  Source sound.
     *  @param  pos  Index of first sample to copy from.
     *  @param  n  Number of samples to copy (default remainder).
     */
    basic_sound(const basic_sound& snd, size_type pos,
                size_type n = npos);
    /**
     *  @brief  Construct sound as copy of a subsound.
     *  @param  snd  Source sound.
     *  @param  pos  Index of first sample to copy from.
     *  @param  n  Number of samples to copy.
     *  @param  a  Allocator to use.
     */
    basic_sound(const basic_sound& snd, size_type pos,
                size_type n, const Alloc& a);
    
    /**
     *  @brief  Construct sound initialized by a sample array.
     *  @param  s  Source sample array.
     *  @param  n  Number of samples to copy.
     *  @param  a  Allocator to use (default is default allocator).
     *
     *  NB: @a s must have at least @a n samples.
     */
    basic_sound(const SampleType* s, size_type n,
                const Alloc& a = Alloc());
    /**
     *  @brief  Construct sound as multiple samples.
     *  @param  n  Number of samples.
     *  @param  c  Sample to use.
     *  @param  a  Allocator to use (default is default allocator).
     */
    basic_sound(size_type n, SampleType c, const Alloc& a = Alloc());
    
    /**
     *  @brief  Construct sound as copy of a range.
     *  @param  beg  Start of range.
     *  @param  end  End of range.
     *  @param  a  Allocator to use (default is default allocator).
     */
    template<class InputIter>
    basic_sound(InputIter beg, InputIter end,
                const Alloc& a = Alloc());
    
    /**
     *  @brief  Destroy the sound instance.
     */
    ~basic_sound()
    { m_rep()->m_dispose(this->get_allocator()); }

    /**
     *  @brief  Assign the value of @a snd to this sound.
     *  @param  snd  Source sound.
     */
    basic_sound&
    operator=(const basic_sound& snd) 
    { return this->assign(snd); }
    
    /**
     *  @brief  Copy contents of @a s into this sound.
     *  @param  s  Source null-terminated sound.
     */
    basic_sound&
    operator=(const SampleType* s) 
    { return this->assign(s); }
    
    /**
     *  @brief  Set value to sound of length 1.
     *  @param  c  Source sample.
     *
     *  Assigning to a sample makes this sound length 1 and
     *  (*this)[0] == @a c.
     */
    basic_sound&
    operator=(SampleType c) 
    { 
	this->assign(1, c); 
	return *this;
    }
    
    // Iters:
    /**
     *  Returns a read/write iterator that points to the first sample in
     *  the %sound.  Unshares the sound.
     */
    iterator
    begin()
    {
	m_leak();
	return iterator(m_data());
    }
    
    /**
     *  Returns a read-only (constant) iterator that points to the first
     *  sample in the %sound.
     */
    const_iterator
    begin() const
    { return const_iterator(m_data()); }
    
    /**
     *  Returns a read/write iterator that points one past the last
     *  sample in the %sound.  Unshares the sound.
     */
    iterator
    end()
    {
	m_leak();
	return iterator(m_data() + this->size());
    }
    
    /**
     *  Returns a read-only (constant) iterator that points one past the
     *  last sample in the %sound.
     */
    const_iterator
    end() const
    { return const_iterator(m_data() + this->size()); }
    
    /**
     *  Returns a read/write reverse iterator that points to the last
     *  sample in the %sound.  Iteration is done in reverse element
     *  order.  Unshares the sound.
     */
    reverse_iterator
    rbegin()
    { return reverse_iterator(this->end()); }
    
    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last sample in the %sound.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator
    rbegin() const
    { return const_reverse_iterator(this->end()); }
    
    /**
     *  Returns a read/write reverse iterator that points to one before the
     *  first sample in the %sound.  Iteration is done in reverse
     *  element order.  Unshares the sound.
     */
    reverse_iterator
    rend()
    { return reverse_iterator(this->begin()); }
    
    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first sample in the %sound.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator
    rend() const
    { return const_reverse_iterator(this->begin()); }
    
public:
    // Capacity:
    ///  Returns the number of samples in the sound.
    size_type
    size() const
    { return m_rep()->m_length; }
    
    ///  Returns the number of samples in the sound.
    size_type
    length() const
    { return m_rep()->m_length; }
    
    /// Returns the size() of the largest possible %sound.
    size_type
    max_size() const
    { return rep::s_max_size; }
    
    /**
     *  @brief  Resizes the %sound to the specified number of samples.
     *  @param  n  Number of samples the %sound should contain.
     *  @param  c  Sample to fill any new elements.
     *
     *  This function will %resize the %sound to the specified
     *  number of samples.  If the number is smaller than the
     *  %sound's current size the %sound is truncated, otherwise
     *  the %sound is extended and new elements are set to @a c.
     */
    void
    resize(size_type n, SampleType c);
    
    /**
     *  @brief  Resizes the %sound to the specified number of samples.
     *  @param  n  Number of samples the %sound should contain.
     *
     *  This function will resize the %sound to the specified length.  If
     *  the new size is smaller than the %sound's current size the %sound
     *  is truncated, otherwise the %sound is extended and new samples
     *  are constructed using sample_traits::zero(), although the default
     *  constructor should achieve the same effect.
     */
    void
    resize(size_type n)
    { this->resize(n, sample_traits<SampleType>::zero()); }
    
    /**
     *  Returns the total number of samples that the %sound can hold
     *  before needing to allocate more memory.
     */
    size_type
    capacity() const
    { return m_rep()->m_capacity; }
    
    /**
     *  @brief  Attempt to preallocate enough memory for specified number of
     *          samples.
     *  @param  res_arg  Number of samples required.
     *  @throw  std::length_error  If @a res_arg exceeds @c max_size().
     *
     *  This function attempts to reserve enough memory for the
     *  %sound to hold the specified number of samples.  If the
     *  number requested is more than max_size(), length_error is
     *  thrown.
     *
     *  The advantage of this function is that if optimal code is a
     *  necessity and the user can determine the sound length that will be
     *  required, the user can reserve the memory in %advance, and thus
     *  prevent a possible reallocation of memory and copying of %sound
     *  data.
     */
    void
    reserve(size_type res_arg = 0);
    
    /**
     *  Erases the sound, making it empty.
     */
    void
    clear()
    { m_mutate(0, this->size(), 0); }
    
    /**
     *  Returns true if the %sound is empty.  Equivalent to *this == "".
     */
    bool
    empty() const
    { return this->size() == 0; }
    
    // Element access:
    /**
     *  @brief  Subscript access to the data contained in the %sound.
     *  @param  pos  The index of the sample to access.
     *  @return  Read-only (constant) reference to the sample.
     *
     *  This operator allows for easy, array-style, data access.
     *  Note that data access with this operator is unchecked and
     *  out_of_range lookups are not defined. (For checked lookups
     *  see at().)
     */
    const_reference
    operator[] (size_type pos) const
    {
	SND_DEBUG_ASSERT(pos < size());
	return m_data()[pos];
    }
    
    /**
     *  @brief  Subscript access to the data contained in the %sound.
     *  @param  pos  The index of the sample to access.
     *  @return  Read/write reference to the sample.
     *
     *  This operator allows for easy, array-style, data access.
     *  Note that data access with this operator is unchecked and
     *  out_of_range lookups are not defined. (For checked lookups
     *  see at().)  Unshares the sound.
     */
    reference
    operator[](size_type pos)
    {
	SND_DEBUG_ASSERT(pos < size());
	m_leak();
	return m_data()[pos];
    }
    
    /**
     *  @brief  Provides access to the data contained in the %sound.
     *  @param n The index of the sample to access.
     *  @return  Read-only (const) reference to the sample.
     *  @throw  std::out_of_range  If @a n is an invalid index.
     *
     *  This function provides for safer data access.  The parameter is
     *  first checked that it is in the range of the sound.  The function
     *  throws out_of_range if the check fails.
     */
    const_reference
    at(size_type n) const
    {
	if (n >= this->size())
            throw std::out_of_range("basic_sound::at");
	return m_data()[n];
    }
    
    /**
     *  @brief  Provides access to the data contained in the %sound.
     *  @param n The index of the sample to access.
     *  @return  Read/write reference to the sample.
     *  @throw  std::out_of_range  If @a n is an invalid index.
     *
     *  This function provides for safer data access.  The parameter is
     *  first checked that it is in the range of the sound.  The function
     *  throws out_of_range if the check fails.  Success results in
     *  unsharing the sound.
     */
    reference
    at(size_type n)
    {
	if (n >= size())
            throw std::out_of_range("basic_sound::at");
	m_leak();
	return m_data()[n];
    }
    
    // Modifiers:
    /**
     *  @brief  Append a sound to this sound.
     *  @param snd  The sound to append.
     *  @return  Reference to this sound.
     */
    basic_sound&
    operator+=(const basic_sound& snd)
    { return this->append(snd); }
    
    /**
     *  @brief  Append a sample.
     *  @param c  The sample to append.
     *  @return  Reference to this sound.
     */
    basic_sound&
    operator+=(SampleType c)
    { 
	this->push_back(c);
	return *this;
    }
    
    /**
     *  @brief  Append a sound to this sound.
     *  @param snd  The sound to append.
     *  @return  Reference to this sound.
     */
    basic_sound&
    append(const basic_sound& snd);
    
    /**
     *  @brief  Append a subsound.
     *  @param snd  The sound to append.
     *  @param pos  Index of the first sample of snd to append.
     *  @param n  The number of samples to append.
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range if @a pos is not a valid index.
     *
     *  This function appends @a n samples from @a snd starting at @a pos
     *  to this sound.  If @a n is is larger than the number of available
     *  samples in @a snd, the remainder of @a snd is appended.
     */
    basic_sound&
    append(const basic_sound& snd, size_type pos, size_type n);
    
    /**
     *  @brief  Append a C subsound.
     *  @param s  The C sound to append.
     *  @param n  The number of samples to append.
     *  @return  Reference to this sound.
     */
    basic_sound&
    append(const SampleType* s, size_type n);
    
    /**
     *  @brief  Append multiple samples.
     *  @param n  The number of samples to append.
     *  @param c  The sample to use.
     *  @return  Reference to this sound.
     *
     *  Appends n copies of c to this sound.
     */
    basic_sound&
    append(size_type n, SampleType c);
    
    /**
     *  @brief  Append a range of samples.
     *  @param first  Iter referencing the first sample to append.
     *  @param last  Iter marking the end of the range.
     *  @return  Reference to this sound.
     *
     *  Appends samples in the range [first,last) to this sound.
     */
    template<class InputIter>
    basic_sound&
    append(InputIter first, InputIter last)
    { return this->replace(m_iend(), m_iend(), first, last); }
    
    /**
     *  @brief  Append a single sample.
     *  @param c  Sample to append.
     */
    void
    push_back(SampleType c)
    { 
        const size_type len = 1 + this->size();
	if (len > this->capacity() || m_rep()->m_is_shared())
            this->reserve(len);
	traits_type::assign(m_data()[this->size()], c);
	m_rep()->m_set_length_and_sharable(len);
    }
    
    /**
     *  @brief  Set value to contents of another sound.
     *  @param  snd  Source sound to use.
     *  @return  Reference to this sound.
     */
    basic_sound&
    assign(const basic_sound& snd);
    
    /**
     *  @brief  Set value to a subsound of a sound.
     *  @param snd  The sound to use.
     *  @param pos  Index of the first sample of snd.
     *  @param n  Number of samples to use.
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range if @a pos is not a valid index.
     *
     *  This function sets this sound to the subsound of @a snd consisting
     *  of @a n samples at @a pos.  If @a n is is larger than the number
     *  of available samples in @a snd, the remainder of @a snd is used.
     */
    basic_sound&
    assign(const basic_sound& snd, size_type pos, size_type n)
    { return this->assign(snd.m_data()
                          + snd.m_check(pos, "basic_sound::assign"),
                          snd.m_limit(pos, n)); }
    
    /**
     *  @brief  Set value to a C subsound.
     *  @param s  The C sound to use.
     *  @param n  Number of samples to use.
     *  @return  Reference to this sound.
     *
     *  This function sets the value of this sound to the first @a n
     *  samples of @a s.  If @a n is is larger than the number of
     *  available samples in @a s, the remainder of @a s is used.
     */
    basic_sound&
    assign(const SampleType* s, size_type n);
    
    /**
     *  @brief  Set value to multiple samples.
     *  @param n  Length of the resulting sound.
     *  @param c  The sample to use.
     *  @return  Reference to this sound.
     *
     *  This function sets the value of this sound to @a n copies of
     *  sample @a c.
     */
    basic_sound&
    assign(size_type n, SampleType c)
    { return m_replace_aux(size_type(0), this->size(), n, c); }
    
    /**
     *  @brief  Set value to a range of samples.
     *  @param first  Iter referencing the first sample to append.
     *  @param last  Iter marking the end of the range.
     *  @return  Reference to this sound.
     *
     *  Sets value of sound to samples in the range [first,last).
     */
    template<class InputIter>
    basic_sound&
    assign(InputIter first, InputIter last)
    { return this->replace(m_ibegin(), m_iend(), first, last); }
    
    /**
     *  @brief  Insert multiple samples.
     *  @param p  Iter referencing location in sound to insert at.
     *  @param n  Number of samples to insert
     *  @param c  The sample to insert.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Inserts @a n copies of sample @a c starting at the position
     *  referenced by iterator @a p.  If adding samples causes the length
     *  to exceed max_size(), length_error is thrown.  The value of the
     *  sound doesn't change if an error is thrown.
     */
    void
    insert(iterator p, size_type n, SampleType c)
    {	this->replace(p, p, n, c);  }
    
    /**
     *  @brief  Insert a range of samples.
     *  @param p  Iter referencing location in sound to insert at.
     *  @param beg  Start of range.
     *  @param end  End of range.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Inserts samples in range [beg,end).  If adding samples causes
     *  the length to exceed max_size(), length_error is thrown.  The value
     *  of the sound doesn't change if an error is thrown.
     */
    template<class InputIter>
    void
    insert(iterator p, InputIter beg, InputIter end)
    { this->replace(p, p, beg, end); }
    
    /**
     *  @brief  Insert value of a sound.
     *  @param pos1  Iter referencing location in sound to insert at.
     *  @param snd  The sound to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Inserts value of @a snd starting at @a pos1.  If adding samples
     *  causes the length to exceed max_size(), length_error is thrown.  The
     *  value of the sound doesn't change if an error is thrown.
     */
    basic_sound&
    insert(size_type pos1, const basic_sound& snd)
    { return this->insert(pos1, snd, size_type(0), snd.size()); }
    
    /**
     *  @brief  Insert a subsound.
     *  @param pos1  Iter referencing location in sound to insert at.
     *  @param snd  The sound to insert.
     *  @param pos2  Start of samples in snd to insert.
     *  @param n  Number of samples to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *  @throw  std::out_of_range  If @a pos1 > size() or
     *  @a pos2 > @a snd.size().
     *
     *  Starting at @a pos1, insert @a n sample of @a snd beginning with
     *  @a pos2.  If adding samples causes the length to exceed
     *  max_size(), length_error is thrown.  If @a pos1 is beyond the end of
     *  this sound or @a pos2 is beyond the end of @a snd, out_of_range is
     *  thrown.  The value of the sound doesn't change if an error is
     *  thrown.
     */
    basic_sound&
    insert(size_type pos1, const basic_sound& snd,
           size_type pos2, size_type n)
    { return this->insert(pos1, snd.m_data()
                          + snd.m_check(pos2, "basic_sound::insert"),
                          snd.m_limit(pos2, n)); }
    
    /**
     *  @brief  Insert a C subsound.
     *  @param pos  Iter referencing location in sound to insert at.
     *  @param s  The C sound to insert.
     *  @param n  The number of samples to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *  @throw  std::out_of_range  If @a pos is beyond the end of this
     *  sound.
     *
     *  Inserts the first @a n samples of @a s starting at @a pos.  If
     *  adding samples causes the length to exceed max_size(),
     *  length_error is thrown.  If @a pos is beyond end(), out_of_range is
     *  thrown.  The value of the sound doesn't change if an error is
     *  thrown.
     */
    basic_sound&
    insert(size_type pos, const SampleType* s, size_type n);
    
    /**
     *  @brief  Insert multiple samples.
     *  @param pos  Index in sound to insert at.
     *  @param n  Number of samples to insert
     *  @param c  The sample to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *  @throw  std::out_of_range  If @a pos is beyond the end of this
     *  sound.
     *
     *  Inserts @a n copies of sample @a c starting at index @a pos.  If
     *  adding samples causes the length to exceed max_size(),
     *  length_error is thrown.  If @a pos > length(), out_of_range is
     *  thrown.  The value of the sound doesn't change if an error is
     *  thrown.
     */
    basic_sound&
    insert(size_type pos, size_type n, SampleType c)
    { return m_replace_aux(m_check(pos, "basic_sound::insert"),
                           size_type(0), n, c); }
    
    /**
     *  @brief  Insert one sample.
     *  @param p  Iter referencing position in sound to insert at.
     *  @param c  The sample to insert.
     *  @return  Iter referencing newly inserted char.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Inserts sample @a c at position referenced by @a p.  If adding
     *  sample causes the length to exceed max_size(), length_error is
     *  thrown.  If @a p is beyond end of sound, out_of_range is thrown.
     *  The value of the sound doesn't change if an error is thrown.
     */
    iterator
    insert(iterator p, SampleType c)
    {
	SND_DEBUG_ASSERT(p >= m_ibegin() && p <= m_iend());
	const size_type pos = p - m_ibegin();
	m_replace_aux(pos, size_type(0), size_type(1), c);
	m_rep()->m_set_leaked();
	return this->m_ibegin() + pos;
    }
    
    /**
     *  @brief  Remove samples.
     *  @param pos  Index of first sample to remove (default 0).
     *  @param n  Number of samples to remove (default remainder).
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range  If @a pos is beyond the end of this
     *  sound.
     *
     *  Removes @a n samples from this sound starting at @a pos.  The
     *  length of the sound is reduced by @a n.  If there are < @a n
     *  samples to remove, the remainder of the sound is truncated.  If
     *  @a p is beyond end of sound, out_of_range is thrown.  The value of
     *  the sound doesn't change if an error is thrown.
     */
    basic_sound&
    erase(size_type pos = 0, size_type n = npos)
    { 
	m_mutate(m_check(pos, "basic_sound::erase"),
                 m_limit(pos, n), size_type(0));
	return *this;
    }
    
    /**
     *  @brief  Remove one sample.
     *  @param position  Iter referencing the sample to remove.
     *  @return  iterator referencing same location after removal.
     *
     *  Removes the sample at @a position from this sound. The value
     *  of the sound doesn't change if an error is thrown.
     */
    iterator
    erase(iterator position)
    {
	SND_DEBUG_ASSERT(position >= m_ibegin()
                         && position < m_iend());
	const size_type pos = position - m_ibegin();
	m_mutate(pos, size_type(1), size_type(0));
	m_rep()->m_set_leaked();
	return m_ibegin() + pos;
    }
    
    /**
     *  @brief  Remove a range of samples.
     *  @param first  Iter referencing the first sample to remove.
     *  @param last  Iter referencing the end of the range.
     *  @return  Iter referencing location of first after removal.
     *
     *  Removes the samples in the range [first,last) from this sound.
     *  The value of the sound doesn't change if an error is thrown.
     */
    iterator
    erase(iterator first, iterator last)
    {
	SND_DEBUG_ASSERT(first >= m_ibegin() && first <= last
                         && last <= m_iend());
        const size_type pos = first - m_ibegin();
	m_mutate(pos, last - first, size_type(0));
	m_rep()->m_set_leaked();
	return m_ibegin() + pos;
    }
    
    /**
     *  @brief  Replace samples with value from another sound.
     *  @param pos  Index of first sample to replace.
     *  @param n  Number of samples to be replaced.
     *  @param snd  Sound to insert.
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range  If @a pos is beyond the end of this
     *  sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [pos,pos+n) from this sound.
     *  In place, the value of @a snd is inserted.  If @a pos is beyond end
     *  of sound, out_of_range is thrown.  If the length of the result
     *  exceeds max_size(), length_error is thrown.  The value of the sound
     *  doesn't change if an error is thrown.
     */
    basic_sound&
    replace(size_type pos, size_type n, const basic_sound& snd)
    { return this->replace(pos, n, snd.m_data(), snd.size()); }
    
    /**
     *  @brief  Replace samples with value from another sound.
     *  @param pos1  Index of first sample to replace.
     *  @param n1  Number of samples to be replaced.
     *  @param snd  Sound to insert.
     *  @param pos2  Index of first sample of snd to use.
     *  @param n2  Number of samples from snd to use.
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range  If @a pos1 > size() or @a pos2 >
     *  snd.size().
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [pos1,pos1 + n) from this
     *  sound.  In place, the value of @a snd is inserted.  If @a pos is
     *  beyond end of sound, out_of_range is thrown.  If the length of the
     *  result exceeds max_size(), length_error is thrown.  The value of the
     *  sound doesn't change if an error is thrown.
     */
    basic_sound&
    replace(size_type pos1, size_type n1, const basic_sound& snd,
            size_type pos2, size_type n2)
    { return this->replace(pos1, n1, snd.m_data()
                           + snd.m_check(pos2, "basic_sound::replace"),
                           snd.m_limit(pos2, n2)); }
    
    /**
     *  @brief  Replace samples with value of a C subsound.
     *  @param pos  Index of first sample to replace.
     *  @param n1  Number of samples to be replaced.
     *  @param s  C sound to insert.
     *  @param n2  Number of samples from @a s to use.
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range  If @a pos1 > size().
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [pos,pos + n1) from this sound.
     *  In place, the first @a n2 samples of @a s are inserted, or all
     *  of @a s if @a n2 is too large.  If @a pos is beyond end of sound,
     *  out_of_range is thrown.  If the length of result exceeds max_size(),
     *  length_error is thrown.  The value of the sound doesn't change if
     *  an error is thrown.
     */
    basic_sound&
    replace(size_type pos, size_type n1, const SampleType* s,
            size_type n2);
    
    /**
     *  @brief  Replace samples with multiple samples.
     *  @param pos  Index of first sample to replace.
     *  @param n1  Number of samples to be replaced.
     *  @param n2  Number of samples to insert.
     *  @param c  Sample to insert.
     *  @return  Reference to this sound.
     *  @throw  std::out_of_range  If @a pos > size().
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [pos,pos + n1) from this sound.
     *  In place, @a n2 copies of @a c are inserted.  If @a pos is beyond
     *  end of sound, out_of_range is thrown.  If the length of result
     *  exceeds max_size(), length_error is thrown.  The value of the sound
     *  doesn't change if an error is thrown.
     */
    basic_sound&
    replace(size_type pos, size_type n1, size_type n2, SampleType c)
    { return m_replace_aux(m_check(pos, "basic_sound::replace"),
                           m_limit(pos, n1), n2, c); }
    
    /**
     *  @brief  Replace range of samples with sound.
     *  @param i1  Iter referencing start of range to replace.
     *  @param i2  Iter referencing end of range to replace.
     *  @param snd  Sound value to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [i1,i2).  In place, the value of
     *  @a snd is inserted.  If the length of result exceeds max_size(),
     *  length_error is thrown.  The value of the sound doesn't change if
     *  an error is thrown.
     */
    basic_sound&
    replace(iterator i1, iterator i2, const basic_sound& snd)
    { return this->replace(i1, i2, snd.m_data(), snd.size()); }
    
    /**
     *  @brief  Replace range of samples with C subsound.
     *  @param i1  Iter referencing start of range to replace.
     *  @param i2  Iter referencing end of range to replace.
     *  @param s  C sound value to insert.
     *  @param n  Number of samples from s to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [i1,i2).  In place, the first @a
     *  n samples of @a s are inserted.  If the length of result exceeds
     *  max_size(), length_error is thrown.  The value of the sound doesn't
     *  change if an error is thrown.
     */
    basic_sound&
    replace(iterator i1, iterator i2, const SampleType* s, size_type n)
    {
	SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
                         && i2 <= m_iend());
	return this->replace(i1 - m_ibegin(), i2 - i1, s, n);
    }
    
    /**
     *  @brief  Replace range of samples with multiple samples
     *  @param i1  Iter referencing start of range to replace.
     *  @param i2  Iter referencing end of range to replace.
     *  @param n  Number of samples to insert.
     *  @param c  Sample to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [i1,i2).  In place, @a n copies
     *  of @a c are inserted.  If the length of result exceeds max_size(),
     *  length_error is thrown.  The value of the sound doesn't change if
     *  an error is thrown.
     */
    basic_sound&
    replace(iterator i1, iterator i2, size_type n, SampleType c)
    {
	SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
                         && i2 <= m_iend());
	return m_replace_aux(i1 - m_ibegin(), i2 - i1, n, c);
    }
    
    /**
     *  @brief  Replace range of samples with range.
     *  @param i1  Iter referencing start of range to replace.
     *  @param i2  Iter referencing end of range to replace.
     *  @param k1  Iter referencing start of range to insert.
     *  @param k2  Iter referencing end of range to insert.
     *  @return  Reference to this sound.
     *  @throw  std::length_error  If new length exceeds @c max_size().
     *
     *  Removes the samples in the range [i1,i2).  In place, samples
     *  in the range [k1,k2) are inserted.  If the length of result exceeds
     *  max_size(), length_error is thrown.  The value of the sound doesn't
     *  change if an error is thrown.
     */
    /*
      template<class InputIter>
      basic_sound&
      replace(iterator i1, iterator i2,
      InputIter k1, InputIter k2)
      {
      SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
      && i2 <= m_iend());
      snd_requires_valid_range(k1, k2);
	  typedef typename std::is_integer<InputIter>::type Integral;
	  return m_replace_dispatch(i1, i2, k1, k2, Integral());
          }
    */

    // Specializations for the common case of pointer and iterator:
    // useful to avoid the overhead of temporary buffering in m_replace.
    basic_sound&
    replace(iterator i1, iterator i2, SampleType* k1, SampleType* k2)
    {
	SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
                         && i2 <= m_iend());
	snd_requires_valid_range(k1, k2);
	return this->replace(i1 - m_ibegin(), i2 - i1,
			     k1, k2 - k1);
    }
    
    basic_sound&
    replace(iterator i1, iterator i2,
            const SampleType* k1, const SampleType* k2)
    {
	SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
                         && i2 <= m_iend());
	snd_requires_valid_range(k1, k2);
	return this->replace(i1 - m_ibegin(), i2 - i1,
			     k1, k2 - k1);
    }
    
    basic_sound&
    replace(iterator i1, iterator i2, iterator k1, iterator k2)
    {
	SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
                         && i2 <= m_iend());
	snd_requires_valid_range(k1, k2);
	return this->replace(i1 - m_ibegin(), i2 - i1,
			     k1.base(), k2 - k1);
    }
    
    basic_sound&
    replace(iterator i1, iterator i2,
            const_iterator k1, const_iterator k2)
    {
	SND_DEBUG_ASSERT(m_ibegin() <= i1 && i1 <= i2
                         && i2 <= m_iend());
	snd_requires_valid_range(k1, k2);
	return this->replace(i1 - m_ibegin(), i2 - i1,
			     k1.base(), k2 - k1);
    }
    
private:
    
    basic_sound&
    m_replace_aux(size_type pos1, size_type n1, size_type n2,
                  SampleType c);
    
    basic_sound&
    m_replace_safe(size_type pos1, size_type n1, const SampleType* s,
                   size_type n2);
    
    // For Input Iters, used in istreambuf_iterators, etc.
    template<class InIter>
    static SampleType*
    s_construct(InIter beg, InIter end, const Alloc& a,
                std::input_iterator_tag);
    
    // For forward_iterators up to random_access_iterators, used for
    // snd::iterator, SampleType*, etc. XXX ???
    template<class FwdIter>
    static SampleType*
    s_construct(FwdIter beg, FwdIter end, const Alloc& a,
                std::forward_iterator_tag);
    
    static SampleType*
    s_construct(size_type req, SampleType c, const Alloc& a);

    public:
    
    /**
     *  @brief  Copy subsound into C sound.
     *  @param s  C sound to copy value into.
     *  @param n  Number of samples to copy.
     *  @param pos  Index of first sample to copy.
     *  @return  Number of samples actually copied
     *  @throw  std::out_of_range  If pos > size().
     *
     *  Copies up to @a n samples starting at @a pos into the C sound @a
     *  s.  If @a pos is greater than size(), out_of_range is thrown.
     */
    size_type
    copy(SampleType* s, size_type n, size_type pos = 0) const;
    
    /**
     *  @brief  Swap contents with another sound.
     *  @param s  Sound to swap with.
     *
     *  Exchanges the contents of this sound with that of @a s in constant
     *  time.
     */
    void
    swap(basic_sound& s);
    
    // Sound operations:
    
    /**
     *  @brief  Return const pointer to contents.
     *
     *  This is a handle to internal data.  Do not modify or dire things may
     *  happen.
     */
    const SampleType*
    data() const
    { return m_data(); }
    
    /**
     *  @brief  Return copy of allocator used to construct this sound.
     */
    allocator_type
    get_allocator() const
    { return m_dataplus; }
    
    /**
     *  @brief  Get a subsound.
     *  @param pos  Index of first sample (default 0).
     *  @param n  Number of samples in subsound (default remainder).
     *  @return  The new sound.
     *  @throw  std::out_of_range  If pos > size().
     *
     *  Construct and return a new sound using the @a n samples starting
     *  at @a pos.  If the sound is too short, use the remainder of the
     *  samples.  If @a pos is beyond the end of the sound, out_of_range
     *  is thrown.
     */
    basic_sound
    subsnd(size_type pos = 0, size_type n = npos) const
    { return basic_sound(*this,
                         m_check(pos, "basic_sound::subsnd"), n); }
    
    /**
     *  XXX do something meaningful for sounds.
     *
     *  @brief  Compare to a sound.
     *  @param snd  Sound to compare against.
     *  @return  Integer < 0, 0, or > 0.
     *
     *  Returns an integer < 0 if this sound is ordered before @a snd, 0 if
     *  their values are equivalent, or > 0 if this sound is ordered after
     *  @a snd.  Determines the effective length rlen of the sounds to
     *  compare as the smallest of size() and snd.size().  The function
     *  then compares the two sounds by calling traits::compare(data(),
     *  snd.data(),rlen).  If the result of the comparison is nonzero returns
     *  it, otherwise the shorter one is ordered first.
     */
    int
    compare(const basic_sound& snd) const
    {
	const size_type size = this->size();
	const size_type osize = snd.size();
	const size_type len = std::min(size, osize);
        
	int r = traits_type::compare(m_data(), snd.data(), len);
	if (!r)
            r =  size - osize;
	return r;
    }
};

template<typename SampleType, typename SampleTraits, typename Alloc>
inline basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound()
    : m_dataplus(s_construct(size_type(), SampleType(), Alloc()), Alloc()) { }

// operator+
/**
 *  @brief  Concatenate two sounds.
 *  @param lhs  First sound.
 *  @param rhs  Last sound.
 *  @return  New sound with value of @a lhs followed by @a rhs.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>
operator+(const basic_sound<SampleType, SampleTraits, Alloc>& lhs,
          const basic_sound<SampleType, SampleTraits, Alloc>& rhs)
{
    basic_sound<SampleType, SampleTraits, Alloc> snd(lhs);
    snd.append(rhs);
    return snd;
}

/**
 *  @brief  Concatenate sample and sound.
 *  @param lhs  First sound.
 *  @param rhs  Last sound.
 *  @return  New sound with @a lhs followed by @a rhs.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType,SampleTraits,Alloc>
operator+(SampleType lhs, const basic_sound<SampleType,SampleTraits,Alloc>& rhs);

/**
 *  @brief  Concatenate sound and C sound.
 *  @param lhs  First sound.
 *  @param rhs  Last sound.
 *  @return  New sound with @a lhs followed by @a rhs.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
inline basic_sound<SampleType, SampleTraits, Alloc>
operator+(const basic_sound<SampleType, SampleTraits, Alloc>& lhs,
          const SampleType* rhs)
{
    basic_sound<SampleType, SampleTraits, Alloc> snd(lhs);
    snd.append(rhs);
    return snd;
}

/**
 *  @brief  Concatenate sound and sample.
 *  @param lhs  First sound.
 *  @param rhs  Last sound.
 *  @return  New sound with @a lhs followed by @a rhs.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
inline basic_sound<SampleType, SampleTraits, Alloc>
operator+(const basic_sound<SampleType, SampleTraits, Alloc>& lhs, SampleType rhs)
{
    typedef basic_sound<SampleType, SampleTraits, Alloc>	sound_type;
    typedef typename sound_type::size_type		size_type;
    sound_type snd(lhs);
    snd.append(size_type(1), rhs);
    return snd;
}

// operator ==
/**
 *  @brief  Test equivalence of two sounds.
 *  @param lhs  First sound.
 *  @param rhs  Second sound.
 *  @return  True if @a lhs.compare(@a rhs) == 0.  False otherwise.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
inline bool
operator==(const basic_sound<SampleType, SampleTraits, Alloc>& lhs,
           const basic_sound<SampleType, SampleTraits, Alloc>& rhs)
{ return lhs.compare(rhs) == 0; }

// operator !=
/**
 *  @brief  Test difference of two sounds.
 *  @param lhs  First sound.
 *  @param rhs  Second sound.
 *  @return  True if @a lhs.compare(@a rhs) != 0.  False otherwise.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
inline bool
operator!=(const basic_sound<SampleType, SampleTraits, Alloc>& lhs,
           const basic_sound<SampleType, SampleTraits, Alloc>& rhs)
{ return rhs.compare(lhs) != 0; }

/**
 *  @brief  Swap contents of two sounds.
 *  @param lhs  First sound.
 *  @param rhs  Second sound.
 *
 *  Exchanges the contents of @a lhs and @a rhs in constant time.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
inline void
swap(basic_sound<SampleType, SampleTraits, Alloc>& lhs,
     basic_sound<SampleType, SampleTraits, Alloc>& rhs)
{ lhs.swap(rhs); }

/**
 *  @brief  Read stream into a sound.
 *  @param is  Input stream.
 *  @param snd  Buffer to store into.
 *  @return  Reference to the input stream.
 *
 *  Stores samples from @a is into @a snd until whitespace is found, the
 *  end of the stream is encountered, or snd.max_size() is reached.  If
 *  is.width() is non-zero, that is the limit on the number of samples
 *  stored into @a snd.  Any previous contents of @a snd are erased.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
basic_istream<SampleType, SampleTraits>&
operator>>(basic_istream<SampleType, SampleTraits>& is,
           basic_sound<SampleType, SampleTraits, Alloc>& snd);

/**
 *  @brief  Write sound to a stream.
 *  @param os  Output stream.
 *  @param snd  Sound to write out.
 *  @return  Reference to the output stream.
 *
 *  Output samples of @a snd into os following the same rules as for
 *  writing a C sound.
 */
template<typename SampleType, typename SampleTraits, typename Alloc>
basic_ostream<SampleType, SampleTraits>&
operator<<(basic_ostream<SampleType, SampleTraits>& os,
           const basic_sound<SampleType, SampleTraits, Alloc>& snd);

template<typename _Type>
inline bool
is_null_pointer(_Type* ptr)
{ return ptr == 0; }

template<typename _Type>
inline bool
is_null_pointer(_Type)
{ return false; }

template<typename SampleType, typename SampleTraits, typename Alloc>
const typename basic_sound<SampleType, SampleTraits, Alloc>::size_type
basic_sound<SampleType, SampleTraits, Alloc>::
rep::s_max_size = (((npos - sizeof(rep_base))/sizeof(SampleType)) - 1) / 4;

template<typename SampleType, typename SampleTraits, typename Alloc>
const typename basic_sound<SampleType, SampleTraits, Alloc>::size_type
basic_sound<SampleType, SampleTraits, Alloc>::npos;

// NB: This is the special case for Input Iters, used in
// istreambuf_iterators, etc.
// Input Iters have a cost structure very different from
// pointers, calling for a different coding style.
template<typename SampleType, typename SampleTraits, typename Alloc>
template<typename InIter>
SampleType*
basic_sound<SampleType, SampleTraits, Alloc>::
s_construct(InIter beg, InIter end, const Alloc& a,
            std::input_iterator_tag)
{
    // Avoid reallocation for common case.
    SampleType buf[128];
    size_type len = 0;
    while (beg != end && len < sizeof(buf) / sizeof(SampleType))
    {
        buf[len++] = *beg;
        ++beg;
    }
    rep* r = rep::s_create(len, size_type(0), a);
    m_copy(r->m_refdata(), buf, len);
    try
    {
        while (beg != end)
        {
            if (len == r->m_capacity)
            {
                // Allocate more space.
                rep* another = rep::s_create(len + 1, len, a);
                m_copy(another->m_refdata(), r->m_refdata(), len);
                r->m_destroy(a);
                r = another;
            }
            r->m_refdata()[len++] = *beg;
            ++beg;
        }
    }
    catch(...)
    {
        r->m_destroy(a);
        throw;
    }
    r->m_set_length_and_sharable(len);
    return r->m_refdata();
}

template<typename SampleType, typename SampleTraits, typename Alloc>
template <typename InIter>
SampleType*
basic_sound<SampleType, SampleTraits, Alloc>::
s_construct(InIter beg, InIter end, const Alloc& a,
            std::forward_iterator_tag)
{
    // NB: Not required, but considered best practice.
    if (builtin_expect(is_null_pointer(beg) && beg != end, 0))
        throw std::logic_error("basic_sound::s_construct NULL not valid");
    
    const size_type dnew = static_cast<size_type>(std::distance(beg,
                                                                end));
    // Check for out_of_range and length_error exceptions.
    rep* r = rep::s_create(dnew, size_type(0), a);
    try
    { s_copy_samples(r->m_refdata(), beg, end); }
    catch(...)
    {
        r->m_destroy(a);
        throw;
    }
    r->m_set_length_and_sharable(dnew);
    return r->m_refdata();
}

template<typename SampleType, typename SampleTraits, typename Alloc>
SampleType*
basic_sound<SampleType, SampleTraits, Alloc>::
s_construct(size_type n, SampleType c, const Alloc& a)
{
    // Check for out_of_range and length_error exceptions.
    rep* r = rep::s_create(n, size_type(0), a);
    if (n)
	m_assign(r->m_refdata(), n, c);
    
    r->m_set_length_and_sharable(n);
    return r->m_refdata();
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(const basic_sound& snd)
    : m_dataplus(snd.m_rep()->m_grab(Alloc(snd.get_allocator()),
                                     snd.get_allocator()),
                 snd.get_allocator())
{ }

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(const Alloc& a)
    : m_dataplus(s_construct(size_type(), SampleType(), a), a)
{ }

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(const basic_sound& snd, size_type pos, size_type n)
    : m_dataplus(s_construct(snd.m_data()
                             + snd.m_check(pos,
                                           "basic_sound::basic_sound"),
                             snd.m_data() + snd.m_limit(pos, n)
                             + pos, Alloc()), Alloc())
{ }

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(const basic_sound& snd, size_type pos,
            size_type n, const Alloc& a)
    : m_dataplus(s_construct(snd.m_data()
                             + snd.m_check(pos,
                                           "basic_sound::basic_sound"),
                             snd.m_data() + snd.m_limit(pos, n)
                             + pos, a), a)
{ }

// TBD: DPG annotate
template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(const SampleType* s, size_type n, const Alloc& a)
    : m_dataplus(s_construct(s, s + n, a), a)
{ }

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(size_type n, SampleType c, const Alloc& a)
    : m_dataplus(s_construct(n, c, a), a)
{ }

// TBD: DPG annotate
template<typename SampleType, typename SampleTraits, typename Alloc>
template<typename InputIter>
basic_sound<SampleType, SampleTraits, Alloc>::
basic_sound(InputIter beg, InputIter end, const Alloc& a)
    : m_dataplus(s_construct(beg, end, a), a)
{ }

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
assign(const basic_sound& snd)
{
    if (m_rep() != snd.m_rep())
    {
        // XXX MT
        const allocator_type a = this->get_allocator();
        SampleType* tmp = snd.m_rep()->m_grab(a, snd.get_allocator());
        m_rep()->m_dispose(a);
        m_data(tmp);
    }
    return *this;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
assign(const SampleType* s, size_type n)
{
//    snd_requires_sound_len(s, n);
    m_check_length(this->size(), n, "basic_sound::assign");
    if (m_disjunct(s) || m_rep()->m_is_shared())
	return m_replace_safe(size_type(0), this->size(), s, n);
    else
    {
        // Work in-place.
        const size_type pos = s - m_data();
        if (pos >= n)
	    m_copy(m_data(), s, n);
        else if (pos)
	    m_move(m_data(), s, n);
        m_rep()->m_set_length_and_sharable(n);
        return *this;
    }
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
append(size_type n, SampleType c)
{
    if (n)
    {
        m_check_length(size_type(0), n, "basic_sound::append");	  
        const size_type len = n + this->size();
        if (len > this->capacity() || m_rep()->m_is_shared())
	    this->reserve(len);
        m_assign(m_data() + this->size(), n, c);
        m_rep()->m_set_length_and_sharable(len);
    }
    return *this;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
append(const SampleType* s, size_type n)
{
    snd_requires_sound_len(s, n);
    if (n)
    {
        m_check_length(size_type(0), n, "basic_sound::append");
        const size_type len = n + this->size();
        if (len > this->capacity() || m_rep()->m_is_shared())
        {
            if (m_disjunct(s))
		this->reserve(len);
            else
            {
                const size_type off = s - m_data();
                this->reserve(len);
                s = m_data() + off;
            }
        }
        m_copy(m_data() + this->size(), s, n);
        m_rep()->m_set_length_and_sharable(len);
    }
    return *this;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
append(const basic_sound& snd)
{
    const size_type size = snd.size();
    if (size)
    {
        const size_type len = size + this->size();
        if (len > this->capacity() || m_rep()->m_is_shared())
	    this->reserve(len);
        m_copy(m_data() + this->size(), snd.m_data(), size);
        m_rep()->m_set_length_and_sharable(len);
    }
    return *this;
}    

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
append(const basic_sound& snd, size_type pos, size_type n)
{
    snd.m_check(pos, "basic_sound::append");
    n = snd.m_limit(pos, n);
    if (n)
    {
        const size_type len = n + this->size();
        if (len > this->capacity() || m_rep()->m_is_shared())
	    this->reserve(len);
        m_copy(m_data() + this->size(), snd.m_data() + pos, n);
        m_rep()->m_set_length_and_sharable(len);	  
    }
    return *this;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
insert(size_type pos, const SampleType* s, size_type n)
{
    snd_requires_sound_len(s, n);
    m_check(pos, "basic_sound::insert");
    m_check_length(size_type(0), n, "basic_sound::insert");
    if (m_disjunct(s) || m_rep()->m_is_shared())
        return m_replace_safe(pos, size_type(0), s, n);
    else
    {
        // Work in-place.
        const size_type off = s - m_data();
        m_mutate(pos, 0, n);
        s = m_data() + off;
        SampleType* p = m_data() + pos;
        if (s  + n <= p)
            m_copy(p, s, n);
        else if (s >= p)
            m_copy(p, s + n, n);
        else
        {
            const size_type nleft = p - s;
            m_copy(p, s, nleft);
            m_copy(p + nleft, p + n, n - nleft);
        }
        return *this;
    }
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
replace(size_type pos, size_type n1, const SampleType* s,
        size_type n2)
{
    snd_requires_sound_len(s, n2);
    m_check(pos, "basic_sound::replace");
    n1 = m_limit(pos, n1);
    m_check_length(n1, n2, "basic_sound::replace");
    bool left;
    if (m_disjunct(s) || m_rep()->m_is_shared())
        return m_replace_safe(pos, n1, s, n2);
    else if ((left = s + n2 <= m_data() + pos)
             || m_data() + pos + n1 <= s)
    {
        // Work in-place: non-overlapping case.
        size_type off = s - m_data();
        left ? off : (off += n2 - n1);
        m_mutate(pos, n1, n2);
        m_copy(m_data() + pos, m_data() + off, n2);
        return *this;
    }
    else
    {
        // Todo: overlapping case.
        const basic_sound tmp(s, n2);
        return m_replace_safe(pos, n1, tmp.m_data(), n2);
    }
}

template<typename SampleType, typename SampleTraits, typename Alloc>
void
basic_sound<SampleType, SampleTraits, Alloc>::rep::
m_destroy(const Alloc& a) throw ()
{
    const size_type size = sizeof(rep_base) +
        (this->m_capacity + 1) * sizeof(SampleType);
    Raw_bytes_alloc(a).deallocate(reinterpret_cast<char*>(this), size);
}

template<typename SampleType, typename SampleTraits, typename Alloc>
void
basic_sound<SampleType, SampleTraits, Alloc>::
m_leak_hard()
{
    if (m_rep()->m_is_shared())
	m_mutate(0, 0, 0);
    m_rep()->m_set_leaked();
}

template<typename SampleType, typename SampleTraits, typename Alloc>
void
basic_sound<SampleType, SampleTraits, Alloc>::
m_mutate(size_type pos, size_type len1, size_type len2)
{
    const size_type old_size = this->size();
    const size_type new_size = old_size + len2 - len1;
    const size_type how_much = old_size - pos - len1;
    
    if (new_size > this->capacity() || m_rep()->m_is_shared())
    {
        // Must reallocate.
        const allocator_type a = get_allocator();
        rep* r = rep::s_create(new_size, this->capacity(), a);
        
        if (pos)
	    m_copy(r->m_refdata(), m_data(), pos);
        if (how_much)
	    m_copy(r->m_refdata() + pos + len2,
                   m_data() + pos + len1, how_much);
        
        m_rep()->m_dispose(a);
        m_data(r->m_refdata());
    }
    else if (how_much && len1 != len2)
    {
        // Work in-place.
        m_move(m_data() + pos + len2,
               m_data() + pos + len1, how_much);
    }
    m_rep()->m_set_length_and_sharable(new_size);
}

template<typename SampleType, typename SampleTraits, typename Alloc>
void
basic_sound<SampleType, SampleTraits, Alloc>::
reserve(size_type res)
{
    if (res != this->capacity() || m_rep()->m_is_shared())
    {
        // Make sure we don't shrink below the current size
        if (res < this->size())
	    res = this->size();
        const allocator_type a = get_allocator();
        SampleType* tmp = m_rep()->m_clone(a, res - this->size());
        m_rep()->m_dispose(a);
        m_data(tmp);
    }
}

template<typename SampleType, typename SampleTraits, typename Alloc>
void
basic_sound<SampleType, SampleTraits, Alloc>::
swap(basic_sound& s)
{
    if (m_rep()->m_is_leaked())
	m_rep()->m_set_sharable();
    if (s.m_rep()->m_is_leaked())
	s.m_rep()->m_set_sharable();
    if (this->get_allocator() == s.get_allocator())
    {
        SampleType* tmp = m_data();
        m_data(s.m_data());
        s.m_data(tmp);
    }
    // The code below can usually be optimized away.
    else
    {
        const basic_sound tmp1(m_ibegin(), m_iend(),
                               s.get_allocator());
        const basic_sound tmp2(s.m_ibegin(), s.m_iend(),
                               this->get_allocator());
        *this = tmp2;
        s = tmp1;
    }
}

template<typename SampleType, typename SampleTraits, typename Alloc>
typename basic_sound<SampleType, SampleTraits, Alloc>::rep*
basic_sound<SampleType, SampleTraits, Alloc>::rep::
s_create(size_type capacity, size_type old_capacity,
         const Alloc& alloc)
{
    if (capacity > s_max_size)
        throw std::length_error("basic_sound::s_create");
    
    // The standard places no restriction on allocating more memory
    // than is strictly needed within this layer at the moment or as
    // requested by an explicit application call to reserve().
    
    // Many malloc implementations perform quite poorly when an
    // application attempts to allocate memory in a stepwise fashion
    // growing each allocation size by only 1 char.  Additionally,
    // it makes little sense to allocate less linear memory than the
    // natural blocking size of the malloc implementation.
    // Unfortunately, we would need a somewhat low-level calculation
    // with tuned parameters to get this perfect for any particular
    // malloc implementation.  Fortunately, generalizations about
    // common features seen among implementations seems to suffice.
    
    // pagesize need not match the actual VM page size for good
    // results in practice, thus we pick a common value on the low
    // side.  malloc_header_size is an estimate of the amount of
    // overhead per memory allocation (in practice seen N * sizeof
    // (void*) where N is 0, 2 or 4).  According to folklore,
    // picking this value on the high side is better than
    // low-balling it (especially when this algorithm is used with
    // malloc implementations that allocate memory blocks rounded up
    // to a size which is a power of 2).
    const size_type pagesize = 4096;
    const size_type malloc_header_size = 4 * sizeof(void*);
    
    // The below implements an exponential growth policy, necessary to
    // meet amortized linear time requirements of the library: see
    // http://gcc.gnu.org/ml/libstdc++/2001-07/msg00085.html.
    // It's active for allocations requiring an amount of memory above
    // system pagesize. This is consistent with the requirements of the
    // standard: http://gcc.gnu.org/ml/libstdc++/2001-07/msg00130.html
    if (capacity > old_capacity && capacity < 2 * old_capacity)
	capacity = 2 * old_capacity;
    
    // NB: Need an array of sample_type[capacity], plus a terminating
    // null sample_type() element, plus enough for the rep data structure.
    // Whew. Seemingly so needy, yet so elemental.
    size_type size = (capacity + 1) * sizeof(SampleType) + sizeof(rep);
    
    const size_type adj_size = size + malloc_header_size;
    if (adj_size > pagesize && capacity > old_capacity)
    {
        const size_type extra = pagesize - adj_size % pagesize;
        capacity += extra / sizeof(SampleType);
        // Never allocate a sound bigger than s_max_size.
        if (capacity > s_max_size)
	    capacity = s_max_size;
        size = (capacity + 1) * sizeof(SampleType) + sizeof(rep);
    }
    
    // NB: Might throw, but no worries about a leak, mate: rep()
    // does not throw.
    void* place = Raw_bytes_alloc(alloc).allocate(size);
    rep *p = new (place) rep;
    p->m_capacity = capacity;
    return p;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
SampleType*
basic_sound<SampleType, SampleTraits, Alloc>::rep::
m_clone(const Alloc& alloc, size_type res)
{
    // Requested capacity of the clone.
    const size_type requested_cap = this->m_length + res;
    rep* r = rep::s_create(requested_cap, this->m_capacity,
                           alloc);
    if (this->m_length)
	m_copy(r->m_refdata(), m_refdata(), this->m_length);
    
    r->m_set_length_and_sharable(this->m_length);
    return r->m_refdata();
}

template<typename SampleType, typename SampleTraits, typename Alloc>
void
basic_sound<SampleType, SampleTraits, Alloc>::
resize(size_type n, SampleType c)
{
    const size_type size = this->size();
    m_check_length(size, n, "basic_sound::resize");
    if (size < n)
	this->append(n - size, c);
    else if (n < size)
	this->erase(n);
    // else nothing (in particular, avoid calling m_mutate() unnecessarily.)
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
m_replace_aux(size_type pos1, size_type n1, size_type n2,
              SampleType c)
{
    m_check_length(n1, n2, "basic_sound::m_replace_aux");
    m_mutate(pos1, n1, n2);
    if (n2)
	m_assign(m_data() + pos1, n2, c);
    return *this;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>&
basic_sound<SampleType, SampleTraits, Alloc>::
m_replace_safe(size_type pos1, size_type n1, const SampleType* s,
               size_type n2)
{
    m_mutate(pos1, n1, n2);
    if (n2)
	m_copy(m_data() + pos1, s, n2);
    return *this;
}


template<typename SampleType, typename SampleTraits, typename Alloc>
basic_sound<SampleType, SampleTraits, Alloc>
operator+(SampleType lhs, const basic_sound<SampleType, SampleTraits, Alloc>& rhs)
{
    typedef basic_sound<SampleType, SampleTraits, Alloc>  sound_type;
    typedef typename sound_type::size_type	          size_type;
    sound_type snd;
    const size_type len = rhs.size();
    snd.reserve(len + 1);
    snd.append(size_type(1), lhs);
    snd.append(rhs);
    return snd;
}

template<typename SampleType, typename SampleTraits, typename Alloc>
typename basic_sound<SampleType, SampleTraits, Alloc>::size_type
basic_sound<SampleType, SampleTraits, Alloc>::
copy(SampleType* s, size_type n, size_type pos) const
{
    m_check(pos, "basic_sound::copy");
    n = m_limit(pos, n);
    snd_requires_sound_len(s, n);
    if (n)
	m_copy(s, m_data() + pos, n);
    // 21.3.5.7 par 3: do not append null.  (good.)
    return n;
}

} // namespace snd

#endif /* BASIC_SOUND_HPP */

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
