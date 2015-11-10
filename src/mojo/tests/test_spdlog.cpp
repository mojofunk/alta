#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_sdplog
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/spdlog/spdlog.h"
#include "mojo/core/string/compose.hpp"

#include "test_common.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

#include <iostream>

std::shared_ptr<spdlog::logger> s_application_log;
std::shared_ptr<spdlog::logger> s_project_log;
std::shared_ptr<spdlog::logger> s_audio_clip_log;

std::shared_ptr<spdlog::logger>& application_log()
{
	return s_application_log;
}

std::shared_ptr<spdlog::logger>& project_log()
{
	return s_project_log;
}

std::shared_ptr<spdlog::logger>& audio_clip_log()
{
	return s_audio_clip_log;
}

void initialize_loggers()
{
	spdlog::set_pattern("[%n] [thread %t] [%fus] %v");
	s_application_log = spdlog::stdout_logger_mt("Application");
	s_project_log = spdlog::stdout_logger_mt("Project");
	s_audio_clip_log = spdlog::stdout_logger_mt("AudioClip");
}

void deinitialize_loggers()
{
	s_application_log.reset();
	s_project_log.reset();
	s_audio_clip_log.reset();
}

#define APP_LOG(Str) application_log()->info(Str);

#define PROJECT_LOG(Str) project_log()->info(Str);

#define AUDIO_CLIP_LOG(Str) audio_clip_log()->info(Str);

BOOST_AUTO_TEST_CASE(test_spdlog_domain_loggers)
{
	initialize_loggers();

	APP_LOG("An Application log message with a custom format");
	APP_LOG(
	    compose("An Application log message with a custom format % %", 1, 5.0f));

	PROJECT_LOG("An Project log message with a custom format");
	PROJECT_LOG(
	    compose("An Project log message with a custom format % %", 1, 5.0f));

	AUDIO_CLIP_LOG("An AudioClip log message with a custom format");
	AUDIO_CLIP_LOG(
	    compose("An AudioClip log message with a custom format % %", 1, 5.0f));
}

BOOST_AUTO_TEST_CASE(test_spdlog_example)
{
	namespace spd = spdlog;
	try {
		// Create console, multithreaded logger
		auto console = spd::stdout_logger_mt("console");
		console->info("Welcome to spdlog!");
		console->info("An info message example {}..", 1);
		console->info() << "Streams are supported too  " << 1;

		// Formatting examples
		console->info("Easy padding in numbers like {:08d}", 12);
		console->info("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}",
		              42);
		console->info("Support for floats {:03.2f}", 1.23456);
		console->info("Positional args are {1} {0}..", "too", "supported");

		console->info("{:<30}", "left aligned");
		console->info("{:>30}", "right aligned");
		console->info("{:^30}", "centered");

		//
		// Runtime log levels
		//
		spd::set_level(spd::level::info); // Set global log level to info
		console->debug("This message shold not be displayed!");
		console->set_level(spd::level::debug); // Set specific logger's log level
		console->debug("Now it should..");

		//
		// Create a file rotating logger with 5mb size max and 3 rotated files
		//
		auto file_logger =
		    spd::rotating_logger_mt("file_logger", "mylogfile", 1048576 * 5, 3);
		for (int i = 0; i < 10; ++i)
			file_logger->info("{} * {} equals {:>10}", i, i, i * i);

		//
		// Create a daily logger - a new file is created every day on 2:30am
		//
		auto daily_logger = spd::daily_logger_mt("daily_logger", "daily", 2, 30);

		//
		// Customize msg format for all messages
		//
		spd::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");
		file_logger->info("This is another message with custom format");

		spd::get("console")->info("loggers can be retrieved from a global registry "
		                          "using the spdlog::get(logger_name) function");

		//
		// Compile time debug or trace macros.
		// Enabled #ifdef SPDLOG_DEBUG_ON or #ifdef SPDLOG_TRACE_ON
		//
		spd::set_pattern("[%n] [thread %t] [%fus] %v");

		SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
		SPDLOG_DEBUG(
		    console, "Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);

		// Asynchronous logging is very fast..
		// Just call spdlog::set_async_mode(q_size) and all created loggers from now
		// on will be asynchronous..
		//
		size_t q_size = 1048576; // queue size must be power of 2
		spdlog::set_async_mode(q_size);
		auto async_file = spd::daily_logger_st("async_file_logger", "async_log.txt");
		async_file->info() << "This is async log.."
		                   << "Should be very fast!";
		spdlog::drop_all(); // Close all loggers
	}
	catch (const spd::spdlog_ex& ex) {
		std::cout << "Log failed: " << ex.what() << std::endl;
	}
}
