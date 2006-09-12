#ifndef SOUNDFWD_HPP
#define SOUNDFWD_HPP

// XXX temporary.
namespace std
{
  template<typename Alloc>
  class allocator;
}

namespace snd
{
 
  template<class SampleType>
  struct sample_traits;
  
  template<typename SampleType, typename Traits = sample_traits<SampleType>,
	   typename Alloc = std::allocator<SampleType> >
  class basic_sound;
  
  template<> struct sample_traits<float>;
  
  typedef basic_sound<float> sound;
  
} // namespace snd

#endif	// SOUNDFWD_HPP
