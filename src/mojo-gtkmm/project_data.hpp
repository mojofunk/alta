
#ifndef UI_PROJECT_DATA_INCLUDED
#define UI_PROJECT_DATA_INCLUDED

#include <set>

#include <boost/shared_ptr.hpp>

#include "track.hpp"

namespace ui {

typedef boost::shared_ptr<Track> TrackSPtr;
typedef std::set<TrackSPtr> TrackSet;

struct ProjectData
{
	bool playing;
	bool looping;

	TrackSet tracks;
};

} // namespace ui

#endif 
