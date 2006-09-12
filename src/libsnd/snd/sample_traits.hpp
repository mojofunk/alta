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

#ifndef SAMPLE_TRAITS_HPP
#define SAMPLE_TRAITS_HPP

#include <algorithm> // min, max
#include <limits>
#include <cstddef> // for std::size_t
#include <cmath>
#include <cstring> // for memmove, memset
#include "postypes.hpp"

// #include <liboil.h> or other simd library.

namespace snd
{

template <class SampleT>
struct Sample_types
{
    typedef snd::streampos  pos_type;
    typedef snd::streamoff  off_type;
};

template<typename SampleT>
struct sample_traits
{
    typedef SampleT                                     sample_type;
    typedef typename Sample_types<SampleT>::pos_type    pos_type;
    typedef typename Sample_types<SampleT>::off_type    off_type;

    static void
    assign(SampleT& s1, const SampleT& s2)
    { s1 = s2; }

    static bool
    eq(const SampleT& s1, const SampleT& s2)
    { return s1 == s2; }
    
    static bool
    lt(const SampleT& s1, const SampleT& s2)
    { return s1 < s2; }

    /**
       what is considered to be close enough to
       minimum as to count as minimum.
    */
    static bool
    is_zero(const SampleT s)
    {
        return (std::abs(s) == 0);
    }

    static const SampleT
    zero() { return 0; }

    static SampleT*
    silence(SampleT* s, std::size_t n);
    
    static const SampleT
    max()
    { return std::numeric_limits<SampleT>::max(); }
    
    static const SampleT
    min()
    { return std::numeric_limits<SampleT>::min(); }

    // find absolute max and min
    static const SampleT
    find_max(const SampleT* s, std::size_t n);
    
    static const SampleT
    find_min(const SampleT* s, std::size_t n);
    
    static bool
    compare(const SampleT* s1, const SampleT* s2, std::size_t n);
    
    static SampleT*
    copy(SampleT* dest, const SampleT* src, std::size_t n);
       
    static SampleT*
    move(SampleT* s1, const SampleT* s2, std::size_t n);

    static SampleT*
    assign(SampleT* dest, std::size_t n, SampleT scalar);
    
    static SampleT*
    add(SampleT* dest, const SampleT* src, std::size_t n);
    
    static SampleT*
    multiply(SampleT* dest, const SampleT* src, std::size_t n);
    
    static SampleT*
    scalar_multiply(SampleT* dest, std::size_t n, SampleT scalar);
    
};

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
silence(SampleT* s, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) {
        s[i] = zero();
    }
    
    return s;
}

template<typename SampleT>
const SampleT
sample_traits<SampleT>::
find_max(const SampleT* s, std::size_t n)
{
    SampleT abs_max = zero();
    
    for (std::size_t i = 0; i < n; ++i) {
        abs_max = std::max(std::abs(s[i]), abs_max);
    }
    
    return SampleT(abs_max);
}

template<typename SampleT>
const SampleT
sample_traits<SampleT>::
find_min(const SampleT* s, std::size_t n)
{
    SampleT abs_min = max();
    
    for (std::size_t i = 0; i < n; ++i) {
        abs_min = std::min(std::abs(s[i]), abs_min);
    }
    
    return SampleT(abs_min);
}

template<typename SampleT>
bool
sample_traits<SampleT>::
compare(const SampleT* s1, const SampleT* s2, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) {
        if(!eq(s1[i], s2[i])) return false; 
    }				       
    return true;
}

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
copy(SampleT* dest, const SampleT* src, std::size_t n)
{
    std::copy(src, src + n, dest);
        
    return dest;
}

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
move(SampleT* s1, const SampleT* s2, std::size_t n)
{
    return static_cast<SampleT*>(std::memmove(s1, s2,
                                              n * sizeof(SampleT)));
}

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
assign(SampleT* s, std::size_t n, SampleT scalar)
{
    std::fill_n(s,n,scalar);
    return s;
}

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
add(SampleT* dest, const SampleT* src, std::size_t n)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] += src[i];
    }
    return dest;
}

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
multiply(SampleT* dest, const SampleT* src, std::size_t n)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] *= src[i];
    }
    return dest;
}

template<typename SampleT>
SampleT*
sample_traits<SampleT>::
scalar_multiply(SampleT* dest, std::size_t n, SampleT scalar)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] *= scalar;
    }
    return dest;
}

// sample_traits specialization for float
template<>
struct sample_traits<float>
{    
    typedef float                              sample_type;
    typedef Sample_types<float>::pos_type      pos_type;
    typedef Sample_types<float>::off_type      off_type;

    static void
    assign(float& s1, const float& s2)
    { s1 = s2; }
     
    static bool
    eq(const float& s1, const float& s2)
    { return s1 == s2; }
    
    static bool
    lt(const float& s1, const float& s2)
    { return s1 < s2; }
    
    static const float
    zero()
    { return 0.0f; }
    
    /**
       what is considered to be close enough to
       zero to count as zero.
    */
    static bool
    is_zero(const float s)
    {
        return (std::abs(s) <= 0.0000001f); // or whatever.
    }
    
    static float*
    silence(float* s, std::size_t n);
    
    static const float
    max()
    { return 1.0f; }
    
    static const float
    min()
    { return -1.0f; }

    static const float
    find_max(const float* s, std::size_t n);
    
    static const float
    find_min(const float* s, std::size_t n);
    
    static bool
    compare(const float* s1, const float* s2, std::size_t n);
    
    static float*
    copy(float* dest, const float* src, std::size_t n);
    
    static float*
    move(float* s1, const float* s2, std::size_t n);
    
    static float*
    assign(float* dest, std::size_t n, float scalar);
    
    static float*
    add(float* dest, const float* src, std::size_t n);
    
    static float*
    multiply(float* dest, const float* src, std::size_t n);
    
    static float*
    scalar_multiply(float* dest, std::size_t n, float scalar);
};

float*
sample_traits<float>::
silence(float* s, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) {
        s[i] = zero();
    }
    
    return s;
}

const float
sample_traits<float>::
find_max(const float* s, std::size_t n)
{
    float abs_max = zero();
    
    for (std::size_t i = 0; i < n; ++i) {
        abs_max = std::max(std::abs(s[i]), abs_max);
    }
    
    return float(abs_max);
}

const float
sample_traits<float>::
find_min(const float* s, std::size_t n)
{
    float abs_min = max();
    
    for (std::size_t i = 0; i < n; ++i) {
        abs_min = std::min(std::abs(s[i]), abs_min);
    }
    
    return float(abs_min);
}

bool
sample_traits<float>::
compare(const float* s1, const float* s2, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) {
        if(!eq(s1[i], s2[i])) return false; 
    }				       
    return true;
}

float*
sample_traits<float>::
copy(float* dest, const float* src, std::size_t n)
{
    std::copy(src, src + n, dest);
    
    return dest;
}

float*
sample_traits<float>::
move(float* s1, const float* s2, std::size_t n)
{
    return static_cast<float*>(std::memmove(s1, s2,
                                              n * sizeof(float)));
}

float*
sample_traits<float>::
assign(float* s, std::size_t n, float scalar)
{
    std::fill_n(s,n,scalar);
    return s;
}

float*
sample_traits<float>::
add(float* dest, const float* src, std::size_t n)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] += src[i];
    }
    return dest;
}

float*
sample_traits<float>::
multiply(float* dest, const float* src, std::size_t n)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] *= src[i];
    }
    return dest;
}

float*
sample_traits<float>::
scalar_multiply(float* dest, std::size_t n, float scalar)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] *= scalar;
    }
    return dest;
}

// sample_traits specialization for double.
template<>
struct sample_traits<double>
{
    typedef double                            sample_type;
    typedef Sample_types<double>::pos_type    pos_type;
    typedef Sample_types<double>::off_type    off_type;

    static void
    assign(double& s1, const double& s2)
    { s1 = s2; }
    
    static bool
    eq(const double& s1, const double& s2)
    { return s1 == s2; }
    
    static bool
    lt(const double& s1, const double& s2)
    { return s1 < s2; }
    
    static const double
    zero()
    { return 0.0f; }
    
    /**
       what is considered to be close enough to
       zero to count as zero.
    */
    static bool
    is_zero(const double s)
    {
        return (std::abs(s) <= 0.000000001f); // or whatever.
    }
    
    static double*
    silence(double* s, std::size_t n);
    
    static const double
    max()
    { return 1.0f; }
    
    static const double
    min()
    { return -1.0f; }
    
    static const double
    find_max(const double* s, std::size_t n);
    
    static const double
    find_min(const double* s, std::size_t n);
    
    static bool
    compare(const double* s1, const double* s2, std::size_t n);
    
    static double*
    copy(double* dest, const double* src, std::size_t n);
       
    static double*
    move(double* s1, const double* s2, std::size_t n);
    
    static double*
    assign(double* dest, std::size_t n, double scalar);
    
    static double*
    add(double* dest, const double* src, std::size_t n);
    
    static double*
    multiply(double* dest, const double* src, std::size_t n);
        
    static double*
    scalar_multiply(double* dest, std::size_t n, double scalar);
};


double*
sample_traits<double>::
silence(double* s, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) {
        s[i] = zero();
    }
    
    return s;
}

const double
sample_traits<double>::
find_max(const double* s, std::size_t n)
{
    double abs_max = zero();
    
    for (std::size_t i = 0; i < n; ++i) {
        abs_max = std::max(std::abs(s[i]), abs_max);
    }
    
    return double(abs_max);
}

const double
sample_traits<double>::
find_min(const double* s, std::size_t n)
{
    double abs_min = max();
    
    for (std::size_t i = 0; i < n; ++i) {
        abs_min = std::min(std::abs(s[i]), abs_min);
    }
    
    return double(abs_min);
}

bool
sample_traits<double>::
compare(const double* s1, const double* s2, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i) {
        if(!eq(s1[i], s2[i])) return false; 
    }				       
    return true;
}

double*
sample_traits<double>::
copy(double* dest, const double* src, std::size_t n)
{
    std::copy(src, src + n, dest);
    
    return dest;
}

double*
sample_traits<double>::
move(double* s1, const double* s2, std::size_t n)
{
    return static_cast<double*>(std::memmove(s1, s2,
                                             n * sizeof(double)));
}

double*
sample_traits<double>::
assign(double* s, std::size_t n, double scalar)
{
    std::fill_n(s,n,scalar);
    return s;
}

double*
sample_traits<double>::
add(double* dest, const double* src, std::size_t n)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] += src[i];
    }
    return dest;
}

double*
sample_traits<double>::
multiply(double* dest, const double* src, std::size_t n)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] *= src[i];
    }
    return dest;
}

double*
sample_traits<double>::
scalar_multiply(double* dest, std::size_t n, double scalar)
{
    for(std::size_t i = 0; i < n; ++i) {
        dest[i] *= scalar;
    }
    return dest;
}

} // namespace snd

#endif // SAMPLE_TRAITS_HPP

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
