#ifndef LOGGER_H
#define LOGGER_H

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#define YU_ALL_DEFAULT "\x1b[0m"
#define YU_BOLD "\x1b[1m"
#define YU_FG_BLACK "\x1b[30m"
#define YU_FG_RED "\x1b[31m"
#define YU_FG_GREEN "\x1b[32m"
#define YU_FG_YELLOW "\x1b[33m"
#define YU_FG_BLUE "\x1b[34m"
#define YU_FG_MAGENTA "\x1b[35m"
#define YU_FG_CYAN "\x1b[36m"
#define YU_FG_WHITE "\x1b[37m"
#define YU_FG_EXTENDED "\x1b[38m"
#define YU_FG_DEFAULT "\x1b[39m"
#define YU_BG_BLACK "\x1b[40m"
#define YU_BG_RED "\x1b[41m"
#define YU_BG_GREEN "\x1b[42m"
#define YU_BG_YELLOW "\x1b[43m"
#define YU_BG_BLUE "\x1b[44m"
#define YU_BG_MAGENTA "\x1b[45m"
#define YU_BG_CYAN "\x1b[46m"
#define YU_BG_WHITE "\x1b[47m"
#define YU_BG_EXTENDED "\x1b[48m"
#define YU_BG_DEFAULT "\x1b[49m"

#define LS_FATAL YU_BG_RED YU_FG_BLACK "[FATAL]: "
#define LS_ERROR YU_FG_RED "[ERROR]: "
#define LS_WARN YU_FG_YELLOW "[WARN]: "
#define LS_INFO YU_FG_GREEN "[INFO]: "
#define LS_DEBUG YU_FG_BLUE "[DEBUG]: "
#define LS_TRACE YU_FG_MAGENTA "[TRACE]: "

 #if TMRELEASE == 1
 #define LOG_DEBUG_ENABLED 0
 #define LOG_TRACE_ENABLED 0
 #endif

typedef enum log_level
{
     LOG_LEVEL_FATAL = 0,
	 LOG_LEVEL_ERROR = 1,
	 LOG_LEVEL_WARN = 2,
	 LOG_LEVEL_INFO = 3,
	 LOG_LEVEL_DEBUG = 4,
	 LOG_LEVEL_TRACE = 5
} log_level;

b8 		initialize_logging(void);
void	shutdown_logging(void);

void log_output(log_level level, const char* message, ...);

#define TMFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef TMERROR
#define TMERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define TMWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
#define TMWARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define TMINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define TMINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define TMDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define TMDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define TMTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define TMTRACE(message, ...)

#endif

#endif // LOGGER_H
