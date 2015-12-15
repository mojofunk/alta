#ifndef MOJO_LOGGING_ASYNC_LOG_H
#define MOJO_LOGGING_ASYNC_LOG_H

namespace logging {

class ASyncLog : public Log, public mojo::Worker {
public:
	ASyncLog();

	~ASyncLog();

public: // Log interface
	void add_sink(std::shared_ptr<Sink> sink) override;

	void remove_sink(std::shared_ptr<Sink> sink) override;

	void write_record(Record* record) override;

	std::shared_ptr<Logger> make_logger(const char* const domain) override;

	std::set<std::shared_ptr<Logger>> get_loggers() const override;

private: // RunLoop
	void do_work() override;

	void process_records();

private: // data

	// queue for Records
	using RecordQueueType = moodycamel::ConcurrentQueue<Record*>;
	RecordQueueType m_record_queue;

	std::set<std::shared_ptr<Sink>> m_sinks;
	mutable std::mutex m_sinks_mutex;

	std::set<std::shared_ptr<Logger>> m_loggers;
	mutable std::mutex m_loggers_mutex;

	std::thread m_record_processing_thread;
};

} // namespace logging

#endif // MOJO_LOGGING_ASYNC_LOG_H
