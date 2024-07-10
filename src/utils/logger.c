#include "logger.h"
#include "asserts.h"
#include "platform.h"

#ifdef TMWIN32
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#endif

// todo: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void report_assertion_failure(const char *expression, const char *message,
		const char *file, i32 line)
{
	log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}

void log_output(log_level level, const char *message, ...)
{
	const char *level_strings[6] =
 	{LS_FATAL, LS_ERROR, LS_WARN, LS_INFO , LS_DEBUG , LS_TRACE};
	/* {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", */
	/* "[DEBUG]: ", "[TRACE]: "}; */
	b8 is_error = level < LOG_LEVEL_WARN;

	// note: care here
	const i32 msg_length = 32000;
	char out_message[msg_length];
	memset(out_message, 0, sizeof(out_message));

	// note: microsoft bullshit so if using clang  __builtin_va_list
	va_list arg_ptr;
	va_start(arg_ptr, message);
	vsnprintf(out_message, msg_length, message, arg_ptr);
	va_end(arg_ptr);

	char out_message2[msg_length];
	sprintf(out_message2, "%s%s%s\n", level_strings[level], out_message, YU_ALL_DEFAULT);
	if (is_error)
	{
		mywrite_error(out_message2, level);
	}
	else
	{
		mywrite(out_message2, level);
	}
}
