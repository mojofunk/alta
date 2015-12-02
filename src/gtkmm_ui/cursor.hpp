
#ifndef UI_CURSOR
#define UI_CURSOR

namespace ui {

class Cursor : public Goocanvas::Polyline {
public:
	static Glib::RefPtr<Cursor> create();

	void set_position(double pos);
	void set_height(double height);

private:
	Cursor();
};

} // namespace ui

#endif // UI_CURSOR
