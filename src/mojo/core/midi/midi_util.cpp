namespace mojo {

int get_midi_msg_length(uint8_t status_byte)
{
	// define these with meaningful names
	switch (status_byte & 0xf0) {
	case 0x80:
	case 0x90:
	case 0xa0:
	case 0xb0:
	case 0xe0:
		return 3;
	case 0xc0:
	case 0xd0:
		return 2;
	case 0xf0:
		switch (status_byte) {
		case 0xf0:
			return 0;
		case 0xf1:
		case 0xf3:
			return 2;
		case 0xf2:
			return 3;
		case 0xf4:
		case 0xf5:
		case 0xf7:
		case 0xfd:
			break;
		default:
			return 1;
		}
	}
	return -1;
}

} // namespace mojo
