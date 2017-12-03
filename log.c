/* Standard Libraries */
#include <time.h>
#include <stdio.h>

int
log
(void)
{
	FILE		*LogFilePointer;
	time_t	timer;
	struct tm	*local;
	char		path[FILENAME_MAX];
	
	timer = time(NULL);
	local = localtime(&timer);

	sprintf(path, ".%clogs%c%u-%u-%u_%u:%u:%u.log", PATH_BREAK_CHARACTER, PATH_BREAK_CHARACTER, local -> tm_mon + 1, local -> tm_mday,
		local -> tm_year + 1900, local -> tm_hour, local -> tm_min, local -> tm_sec);
	
	/* Open file */
	LogFilePointer = fopen(path, "w");
	if(!LogFilePointer)return 1;
	
	fprintf(LogFilePointer, "[%u/%u/%u %u:%u:%u]SCLS version %s\n", local -> tm_mon + 1, local -> tm_mday, local -> tm_year + 1900,
		local -> tm_hour, local -> tm_min, local -> tm_sec);
	
	/* Close file */
	fclose(LogFilePointer);
	
	return 0;
}
