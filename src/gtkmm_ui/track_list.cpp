#include "track_list.hpp"

#include "track_list_item.hpp"

namespace ui {

TrackList::TrackList()
{
	set_size_request(s_min_width, s_min_height);
}

void TrackList::add(TrackListItem* item)
{
	pack_start(*item, false, false);
}

void TrackList::remove(TrackListItem* item)
{
}
}
