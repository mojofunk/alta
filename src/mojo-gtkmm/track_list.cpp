
#include "track_list.hpp"

#include "track_list_item.hpp"

namespace ui {

TrackList::TrackList ()
{

}

void
TrackList::add (TrackListItem* item)
{
	pack_start(*item);
}

void
TrackList::remove (TrackListItem* item)
{

}

}
