namespace mojo {

using LogMemoryWriter = fmt::BasicMemoryWriter<char, LogAllocator<char>>;

LogString log_format(LogAllocator<char>& alloc,
                     fmt::StringRef format_str,
                     fmt::ArgList args)
{
	LogMemoryWriter writer(alloc);
	writer.write(format_str, args);
	return LogString(writer.data(), writer.size(), alloc);
}

} // namespace mojo
