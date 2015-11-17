WinMMEMIDIDriverModule::~WinMMEMIDIDriverModule()
{
}

WinMMEMIDIDriverModule::WinMMEMIDIDriverModule()
{
}

std::string WinMMEMIDIDriverModule::get_author()
{
	return "Tim Mayberry";
}

std::string WinMMEMIDIDriverModule::get_description()
{
	return "WinMME module";
}

std::string WinMMEMIDIDriverModule::get_version()
{
	return "0.0.1";
}

MIDIDriverSP WinMMEMIDIDriverModule::create_driver() const
{
	return MIDIDriverSP(new WinMMEMIDIDriver);
}

MOJO_CAPI void* mojo_module_factory(void)
{
	return new WinMMEMIDIDriverModule;
}
