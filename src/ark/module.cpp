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
	
	if ( !g_module_symbol (m_module, descriptor_name.c_str(),
				(gpointer*)&m_desc) || m_desc == NULL)
	{
		cerr << "error resolving" << endl;
		throw;
	}
}

Module::~Module()
{
	g_module_close(m_module);
}

ModuleInfo
Module::get_info() const
{
	return m_desc->get_info();

}

ArchiveReader*
Module::new_reader (const ArchiveFormat& format)
{
	return m_desc->create_reader ();
}

ArchiveWriter*
Module::new_writer (const ArchiveFormat& format)
{
	return m_desc->create_writer ();
}

} // namespace ark
