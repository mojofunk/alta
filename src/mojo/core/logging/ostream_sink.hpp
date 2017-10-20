#ifndef MOJO_LOGGING_OSTREAM_SINK_H
#define MOJO_LOGGING_OSTREAM_SINK_H

namespace logging
{

class OStreamSink : public Sink
{
public:
	void handle_record(Record& record) override;
};

} // namespace logging

#endif // MOJO_LOGGING_OSTREAM_SINK_H
