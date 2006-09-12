#ifndef SND_DEBUG_HPP
#define SND_DEBUG_HPP

#ifdef SND_DEBUG
#include <cassert>
#define SND_DEBUG_ASSERT(ACondition) assert(ACondition)
#else
#define SND_DEBUG_ASSERT(ACondition)

#endif // END_DEBUG

#endif // SND_DEBUG_HPP
