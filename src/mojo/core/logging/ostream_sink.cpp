namespace logging {

void OStreamSink::handle_record(Record& record)
{
	std::cout << "Logger: " << record.logger_name
	          << ", Log Message: " << record.message
	          << ", Thread: " << record.thread_name
	          << ", Timestamp: " << record.timestamp << ", Line: " << record.line
	          << ", File Name: " << record.file_name
	          << ", Function: " << record.function_name << std::endl;
}

} // namespace logging
