/* Standard Libraries */
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

/* Header file */
#include "macros.h"

/*
 * OutputLog
 *
 * [Description]
 * Write a log
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	mode
 *	type:			char
 *	description:	Mode of file open
 *
 * -	format
 *	type:			const char*
 *	description:	format of vfprintf
 *
 * [Call from]
 * welcome function
 * command_mdir function
 * command_rmdir function
 * command_chdir function
 * command_cudir function
 * command_rename function
 * command_mkfile function
 * command_rmfile function
 * command_cpfile function
 * command_lfile function
 * command_tview function
 * command_bview function
 * command_version function
 * command_app function
 * command_date function
 * command_time function
 * command_now function
 *
 * [Call to]
 * Nothing
 */

int
OutputLog
(
char			mode,
const char	*format,
...
)
{
	time_t	timer;
	struct tm	*local;
	char		path[FILENAME_MAX];
	FILE		*FilePointer;
	va_list	args;
	
	timer = time(NULL);
	local = localtime(&timer);
	
	sprintf(path, ".%clogs%c%u-%u-%u.log", PATH_BREAK_CHARACTER, PATH_BREAK_CHARACTER, local -> tm_mon + 1, local -> tm_mday,
		local -> tm_year + 1900);
	
	/* Open file */
	FilePointer = fopen(path, (mode == 'w') ? "w" : "a");
	
	if(!FilePointer)goto log_error;
	
	fprintf(FilePointer, "[%u/%u/%u %u:%u:%u]", local -> tm_mon + 1, local -> tm_mday, local -> tm_year + 1900, local -> tm_hour, local -> tm_min,
		local -> tm_sec);
	
	va_start(args, format);
	
	vfprintf(FilePointer, format, args);
	
	/* Close file */
	fclose(FilePointer);
	
	va_end(args);
	
	return 0;
	
log_error:;
	fprintf(stderr, "Error: Cannot open a log file \"%s\".\n", path);
	return 1;
}
