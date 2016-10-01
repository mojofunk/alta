#ifndef MOJO_PRIVATE_LOGGERS_H
#define MOJO_PRIVATE_LOGGERS_H

namespace core {

M_DECLARE_LOGGER(Init);
M_DECLARE_LOGGER(RunLoop);
M_DECLARE_LOGGER(StringConvert);

void initialize_loggers();

} // namespace core

#endif
