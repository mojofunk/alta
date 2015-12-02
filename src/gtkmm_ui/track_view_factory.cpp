namespace ui {

TrackView* TrackViewFactory::create(mojo::Project* proj)
{
	return new TrackView(proj);
}

} // namespace ui
