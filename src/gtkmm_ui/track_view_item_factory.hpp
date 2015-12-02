#ifndef UI_TRACK_VIEW_ITEM_FACTORY
#define UI_TRACK_VIEW_ITEM_FACTORY

namespace ui {

class Track;

class TrackViewItemFactory {
public:
	static TrackViewItem* create(mojo::Track* track);
};

} // namespace ui

#endif
