
#ifndef TRACK_VIEW_DATA
#define TRACK_VIEW_DATA

#include <list>

#include <boost/shared_ptr.hpp>

namespace ui {

class TrackViewItem;
class Project;
class TrackCanvas;

typedef boost::shared_ptr<TrackViewItem> TrackViewItemSPtr;
typedef std::list<TrackViewItemSPtr> TrackViewItemList;

struct TrackViewData
{
	Project* project;
	TrackViewItemList track_view_items;
	TrackCanvas* canvas;
};

} // namespace ui

#endif
