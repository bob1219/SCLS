/* Standard Libraries */
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

/* Header file */
#include "macros.h"

/*
 * log
 *
 * [Description]
 * Write the log
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
log
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
	
	sprintf(path, ".%clogs%c%u-%u-%u.log", PATH_BREAK_CHARACTER, PATH_BREAK_CHARACTER, local -> tm_mon + 1, local -> tm_day,
		local -> tm_year + 1900);
	
	/* Open file */
	switch(mode)
	{
	case 'w':
		FilePointer = fopen(path, "w");
		break;
		
	case 'a':
		FilePointer = fopen(path, "a");
		break;
		
	default:
		fprintf(stderr, "Error: Cannot write the log.\n");
		return 1;
	}
	
	if(!FilePointer)
	{
		fprintf(stderr, "Error: Cannot write the log.\n");
		return 1;
	}
	
	fprintf(FilePointer, "[%u/%u/%u %u:%u:%u]", local -> tm_mon + 1, local -> tm_day, local -> tm_year + 1900, local -> tm_hour, local -> tm_min,
		local -> tm_sec);
	
	va_start(args, format);
	
	vfprintf(FilePointer, format, args);
	
	/* Close file */
	fclose(FilePointer);
	
	va_end(args);
	
	return 0;
}
