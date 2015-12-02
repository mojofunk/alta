
#ifndef UI_PROJECT_WINDOW_TOOLBAR
#define UI_PROJECT_WINDOW_TOOLBAR

namespace ui {

class ProjectWindowToolbar : public Gtk::HBox {
public:
	ProjectWindowToolbar(mojo::Project*);

private:
	mojo::Project* m_project;

	Gtk::ToggleButton m_activate_project_button;

	// m_show_hide_inspector_button;
	// m_show_hide_info_line_button;
	// m_show_hide_overview_button;
	// m_open_pool_button;
	// m_open_mixer_button;

	// m_transport_toolbar;

	// m_project_window_tools;

private:
	void on_activate_project_button_toggled();
	void on_activate_project_changed(mojo::Project*);
};

} // namespace ui

#endif
