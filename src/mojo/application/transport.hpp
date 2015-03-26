#ifndef MOJO_TRANSPORT_H
#define MOJO_TRANSPORT_H

#ifndef MOJO_APPLICATION_AMALGAMATED
#include "mojo/core/audio/types.hpp"
#endif

namespace mojo {

class Transport {
public:
	void start();
	void stop();

	void set_speed(float speed);
	float get_speed();

	void set_position(count_t);
	count_t get_position();

	void set_record(bool);
	bool get_record();

private:
	// reference to time/clock source?

	float speed;
	count_t position;
	bool record;
};

} // namespace mojo

#endif // MOJO_TRANPSPORT_H
