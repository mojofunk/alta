PortmidiMIDIDriverModule::~PortmidiMIDIDriverModule()
{
}

PortmidiMIDIDriverModule::PortmidiMIDIDriverModule()
{
}

std::string PortmidiMIDIDriverModule::get_author()
{
	return "Tim Mayberry";
}

std::string PortmidiMIDIDriverModule::get_description()
{
	return "Portmidi module";
}

std::string PortmidiMIDIDriverModule::get_version()
{
	return "0.0.1";
}

MIDIDriverSP PortmidiMIDIDriverModule::create_driver() const
{
	return MIDIDriverSP(new PortmidiMIDIDriver);
}

MOJO_CAPI void* mojo_module_factory(void)
{
	return new PortmidiMIDIDriverModule;
}
