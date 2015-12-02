namespace ui {

Glib::RefPtr<Cursor> Cursor::create()
{
	return Glib::RefPtr<Cursor>(new Cursor());
}

Cursor::Cursor()
    : Goocanvas::Polyline(0.0, 0.0, 0.0, 1.0)
{
	// property_width () = 1;
	// property_stroke_color_rgba () = 0;
}

void Cursor::set_position(double pos)
{
	if (pos == property_x()) return;

	Goocanvas::Points points = property_points();
	double x, y;

	points.get_coordinate(0, x, y);
	points.set_coordinate(0, pos, y);
	points.get_coordinate(1, x, y);
	points.set_coordinate(1, pos, y);

	property_points() = points;
}

void Cursor::set_height(double height)
{
	Goocanvas::Points points = property_points();
	double current_x, current_y;
	points.get_coordinate(0, current_x, current_y);
	points.set_coordinate(1, current_x, current_y + height);
	property_points() = points;
}

} // namespace ui
