#ifndef	MACROS_H
#define	MACROS_H

#define SETTING_FILE_PATH_MAX	10
#define FILE_LINE_MAX		10000
#define FORMAT_MAX		61
#define SETTING_NAME_MAX	9
#define SETTING_MAX		992
#define PROMPT_MAX		SETTING_MAX
#define VERSION			"2.1"
#define COMMAND_MAX		100
#define COMMAND_NUMBER_MAX	21
#define MONTH_MAX		10
#define DAY_MAX			5
#define TEXT_MAX		COMMAND_MAX
#define EXECUTABLE_FILE_NAME	"scls.exe"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS) || defined(_CONSOLE)
	#define PATH_BREAK_CHARACTER	'\\'
#else
	#define PATH_BREAK_CHARACTER	'/'
#endif /* #if defined(_WIN32) || ... */

#endif /* #ifndef MACROS_H */
