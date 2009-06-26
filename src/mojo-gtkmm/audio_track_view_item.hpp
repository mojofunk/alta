
#ifndef UI_AUDIO_TRACK_VIEW_ITEM
#define UI_AUDIO_TRACK_VIEW_ITEM

#include <mojo/mojo.hpp>

#include <boost/shared_ptr.hpp>

#include "track_view_item.hpp"
#include "audio_track_list_item.hpp"
#include "audio_track_canvas_item.hpp"

namespace ui {

class AudioTrackViewItem : public TrackViewItem
{
public:

	AudioTrackViewItem (mojo::Track* at);

	virtual void set_height (double height);

	virtual TrackListItem* get_track_list_item ();

	virtual TrackCanvasItem* get_track_canvas_item ();

private:

	mojo::Track* m_audio_track;

	boost::shared_ptr<AudioTrackListItem> m_audio_track_list_item;
	boost::shared_ptr<AudioTrackCanvasItem> m_audio_track_canvas_item;

};

} // namespace ui

#endif
