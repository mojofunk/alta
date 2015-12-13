namespace logging {

using MemoryWriter = fmt::BasicMemoryWriter<char, Allocator<char>>;

String
format(Allocator<char>& alloc, fmt::StringRef format_str, fmt::ArgList args)
{
	MemoryWriter writer(alloc);
	writer.write(format_str, args);
	return String(writer.data(), writer.size(), alloc);
}

} // namespace logging
