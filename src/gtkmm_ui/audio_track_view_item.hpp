
#ifndef UI_AUDIO_TRACK_VIEW_ITEM
#define UI_AUDIO_TRACK_VIEW_ITEM

namespace ui {

class AudioTrackViewItem : public TrackViewItem {
public:
	AudioTrackViewItem(mojo::Track* at);

	virtual TrackListItem* get_track_list_item();

	virtual Glib::RefPtr<TrackCanvasItem> get_track_canvas_item();

private:
	// maybe this should go into TVI
	void on_track_canvas_item_height_changed();

private:
	mojo::Track* m_audio_track;

	std::shared_ptr<AudioTrackListItem> m_audio_track_list_item;
	Glib::RefPtr<AudioTrackCanvasItem> m_audio_track_canvas_item;
};

} // namespace ui

#endif
