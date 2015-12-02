#ifndef UI_TRANSPORT_TOOLBAR
#define UI_TRANSPORT_TOOLBAR

namespace ui {

class TransportToolbar : public Gtk::HBox {
public:
	TransportToolbar(mojo::Project*);

private:
	void update_transport_buttons();

	void on_loop_button_toggled();
	void on_play_button_toggled();

private:
	mojo::Project* m_project;

	Gtk::HButtonBox m_button_box;

	Gtk::ToggleButton m_loop_button;
	Gtk::ToggleButton m_play_button;
};

} // namespace ui

#endif
