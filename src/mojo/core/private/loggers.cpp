namespace core
{

M_DEFINE_LOGGER(Init);
M_DEFINE_LOGGER(RunLoop);
M_DEFINE_LOGGER(StringConvert);

void
initialize_loggers()
{
	M_GET_LOGGER(Init);
	M_GET_LOGGER(RunLoop);
	M_GET_LOGGER(StringConvert);
}

} // namespace core
