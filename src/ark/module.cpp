#include <ark/module.hpp>

#include <iostream>

using namespace std;

namespace ark {

Module::Module(const string& module_file_path)
{
	m_module = g_module_open ( module_file_path.c_str(), G_MODULE_BIND_LAZY );

	if ( !m_module )
	{
		cerr << "module == NULL:" << g_module_error() << endl;
		throw;
	} 

	const string descriptor_name ("ark_descriptor");

	typedef Descriptor* (*descriptor_func_t) ();

	descriptor_func_t desc_func;

	if ( !g_module_symbol (m_module, descriptor_name.c_str(),
				(gpointer*)&desc_func) || desc_func == NULL)
	{
		cerr << "error resolving" << endl;
		throw;
	}

	m_desc = desc_func();
}

Module::~Module()
{
	delete m_desc;

	g_module_close(m_module);
}

ModuleInfo
Module::get_info() const
{
	return m_desc->get_info();
}

ArchiveReader*
Module::new_reader ()
{
	return m_desc->create_reader ();
}

ArchiveWriter*
Module::new_writer ()
{
	return m_desc->create_writer ();
}

} // namespace ark
