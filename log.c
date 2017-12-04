/* Standard Libraries */
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

/* Header file */
#include "macros.h"

int
log
(char			mode,
const char	*format, ...)
{
	time_t	timer;
	struct tm	*local;
	char		path[FILENAME_MAX];
	FILE		*FilePointer;
	va_list	args;
	
	timer = time(NULL);
	local = localtime(&timer);
	
	sprintf(path, ".%clogs%c%u-%u-%u_%u:%u:%u", PATH_BREAK_CHARACTER, PATH_BREAK_CHARACTER, local -> tm_mon + 1, local -> tm_day,
		local -> tm_year + 1900, local -> tm_hour, local -> tm_min, local -> tm_sec);
	
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
		return 1;
	}
	
	if(!FilePointer)return 1;
	
	fprintf(FilePointer, "[%u/%u/%u %u:%u:%u]", local -> tm_mon + 1, local -> tm_day, local -> tm_year + 1900, local -> tm_hour, local -> tm_min,
		local -> tm_sec);
	
	va_start(args, format);
	
	vfprintf(FilePointer, format, args);
	
	/* Close file */
	fclose(FilePointer);
	
	va_end(args);
	
	return 0;
}
