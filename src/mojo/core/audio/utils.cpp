
namespace mojo {

std::vector<samplerate_t> get_common_samplerates()
{
	return { 8000.0,  22050.0, 24000.0,  44100.0, 48000.0,
		        88200.0, 96000.0, 176400.0, 192000.0 };
}

} // namespace mojo
