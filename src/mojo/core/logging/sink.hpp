#ifndef MOJO_LOGGING_SINK_H
#define MOJO_LOGGING_SINK_H

namespace logging {

class Sink {
public:
	//virtual std::string name() = 0;

	/*
	 * The Record is only valid for the duration of call.
	 */
	virtual void handle_record(Record& record) = 0;
};

} // namespace logging

#endif // MOJO_LOGGING_SINK_H
