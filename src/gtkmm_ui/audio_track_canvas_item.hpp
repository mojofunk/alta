
#ifndef UI_AUDIO_TRACK_CANVAS_ITEM
#define UI_AUDIO_TRACK_CANVAS_ITEM

namespace ui {

class AudioTrackCanvasItem : public TrackCanvasItem {
protected:
	AudioTrackCanvasItem(mojo::Track*);

public:
	static Glib::RefPtr<AudioTrackCanvasItem> create(mojo::Track*);

public:
	virtual void set_height(int height);

	virtual uint32_t get_height() const;

	virtual void set_width(int width);

	virtual uint32_t get_width() const;

	virtual void set_selected(bool);

	virtual bool get_selected() const;

private:
	mojo::Track* m_audio_track;

	Glib::RefPtr<Goocanvas::Rect> m_rect;
};

} // namespace ui

#endif
