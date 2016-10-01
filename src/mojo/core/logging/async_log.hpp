#ifndef MOJO_LOGGING_ASYNC_LOG_H
#define MOJO_LOGGING_ASYNC_LOG_H

namespace logging {

class ASyncLog : public Log, public mojo::RunLoop {
public:
	ASyncLog();

	~ASyncLog();

public: // Log interface
	void add_sink(Sink* sink) override;

	void remove_sink(Sink* sink) override;

	std::set<Sink*> get_sinks() const override;

	void write_record(Record* record) override;

	Logger* get_logger(const char* const domain) override;

	std::set<Logger*> get_loggers() const override;

private: // RunLoop
	void do_work() override;

	void process_records();

private: // loggers
	void destroy_loggers();

private: // data
	// queue for Records
	using RecordQueueType = moodycamel::ConcurrentQueue<Record*>;
	RecordQueueType m_record_queue;

	std::set<Sink*> m_sinks;
	mutable std::mutex m_sinks_mutex;

	std::set<Logger*> m_loggers;
	mutable std::mutex m_loggers_mutex;

	std::thread m_record_processing_thread;
};

} // namespace logging

#endif // MOJO_LOGGING_ASYNC_LOG_H
