namespace ui {

TrackViewItem* TrackViewItemFactory::create(mojo::Track* track)
{
	if (mojo::Application::is_audio_track(track)) {
		return new AudioTrackViewItem(track);
	}
	return 0;
}

} // namespace ui
