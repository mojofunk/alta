namespace ui {

ObjectSelectionTool::ObjectSelectionTool()
{
}

const std::string ObjectSelectionTool::get_name() const
{
	return "Object Selection";
}

bool ObjectSelectionTool::on_item_button_press_event(
    Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* ev)
{
	LOG;
	return true;
}

bool ObjectSelectionTool::on_item_button_release_event(
    Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* ev)
{
	LOG;
	return true;
}

bool ObjectSelectionTool::on_item_motion_notify_event(
    Glib::RefPtr<Goocanvas::Item> item, GdkEventMotion* ev)
{
	LOG;
	return true;
}

bool ObjectSelectionTool::on_item_scroll_event(Glib::RefPtr<Goocanvas::Item>,
                                               GdkEventScroll*)
{
	LOG;
	return true;
}

bool ObjectSelectionTool::on_item_key_press_event(Glib::RefPtr<Goocanvas::Item>,
                                                  GdkEventKey*)
{
	LOG;
	return true;
}

bool
ObjectSelectionTool::on_item_key_release_event(Glib::RefPtr<Goocanvas::Item>,
                                               GdkEventKey*)
{
	LOG;
	return true;
}

bool ObjectSelectionTool::on_item_left_event(Glib::RefPtr<Goocanvas::Item>,
                                             GdkEventCrossing*)
{
	LOG;
	return true;
}

bool ObjectSelectionTool::on_item_entered_event(Glib::RefPtr<Goocanvas::Item>,
                                                GdkEventCrossing*)
{
	LOG;
	return true;
}

} // namespace ui
