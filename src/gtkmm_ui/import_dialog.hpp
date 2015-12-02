
#ifndef UI_IMPORT_DIALOG
#define UI_IMPORT_DIALOG

namespace ui {

class ImportDialog {
public:
	ImportDialog();

	~ImportDialog();

	int run();

private:
	BuilderGPtr m_builder;

	Gtk::Dialog* m_dialog;
};

} // namespace ui

#endif
