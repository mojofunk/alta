using namespace ui;

int main(int argc, char* argv[])
{
	Gtk::Main app(argc, argv);

	mojo::Application mojo_app;

	App::init(argc, argv);

	App::run();

	App::cleanup();

	return 0;
}
