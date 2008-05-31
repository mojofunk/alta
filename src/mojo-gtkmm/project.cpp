
#include "project.hpp"
#include "audio_track.hpp"

#include <iostream>

using namespace std;

namespace ui {

Project::Project ()
{

}

void
Project::save ()
{
	cout << "Project::save called" << endl;
}

void
Project::create_audio_track ()
{
	cout << "Project::create_audio_track called" << endl;
}

} // namespace ui
