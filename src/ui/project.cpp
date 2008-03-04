
#include <boost/bind.hpp>

#include <mojo/project.hpp>

#include <ui/app.hpp>
#include <ui/project.hpp>
#include <ui/edit_window.hpp>

#include <ui/dialogs/new_audio_track_dialog.hpp>

namespace gmojo {

Project::Project()
	:
		m_project(new mojo::Project),
		m_edit_window(new EditWindow(this))
{
	m_edit_window->on_delete_event (
		 boost::bind (&Project::on_edit_window_delete_event, this)
		);
}

Project::~Project()
{

}

void
Project::save ()
{


}

void
Project::create_audio_track ()
{
	NewAudioTrackDialog dialog;

	NewAudioTrackDialog::Response response = dialog.run();

	if (response == NewAudioTrackDialog::Cancel) return;

}

bool
Project::on_edit_window_delete_event ()
{
	// disconnect signals connected to the EditWindow
	// although it doesn't really matter in this case

	App::close_project (this);
	
	return true;
}

} // namespace gmojo
