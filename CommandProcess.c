/* Standard Libraries */
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Header files */
#include "macros.h"
#include "extern.h"
#include "typedef.h"
#include "functions.h"

/*
 * CommandProcess
 *
 * [Description]
 * Process a command
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	command
 *	type:			const char*
 *	description:	command
 *
 * [Call from]
 * CommandLine function
 *
 * [Call to]
 * Nothing
 */

int
CommandProcess
(const char *command)
{
	char			commands[COMMAND_NUMBER_MAX][COMMAND_MAX], command2[COMMAND_MAX], format[FORMAT_MAX];
	unsigned int	a;
	
	strcpy(command2, command);
	sprintf(format, "%%%us %%%u[^\n]", COMMAND_MAX, COMMAND_MAX);
	
	for(a = 0 ; (a <= COMMAND_NUMBER_MAX) || (strcmp(command2, "\n")) ; a++)
		sscanf(command2, format, commands[a], command2);
	
	a--;
	
	if(!strcmp(commands[0], "mdir"))
		return command_mdir(a, commands);
	else if(!strcmp(commands[0], "rmdir"))
		return command_rmdir(a, commands);
	else if(!strcmp(commands[0], "rename"))
		return command_rename(a, commands);
	else if(!strcmp(commands[0], "chdir"))
		return command_chdir(a, commands);
	else if(!strcmp(commands[0], "cudir"))
		return command_cudir();
	else if(!strcmp(commands[0], "mkfile"))
		return command_mkfile(a, commands);
	else if(!strcmp(commands[0], "rmfile"))
		return command_rmfile(a, commands);
	else if(!strcmp(commands[0], "cpfile"))
		return command_cpfile(a, commands);
	else if(!strcmp(commands[0], "lfile"))
		return command_lfile(a, commands);
	else if(!strcmp(commands[0], "tview"))
		return command_tview(a, commands);
	else if(!strcmp(commands[0], "bview"))
		return command_bview(a, commands);
	else if(!strcmp(commands[0], "version"))
		return command_version();
	else if(!strcmp(commands[0], "app"))
		return command_app(a, commands);
	else if(!strcmp(commands[0], "date"))
		return command_date();
	else if(!strcmp(commands[0], "time"))
		return command_time();
	else if(!strcmp(commands[0], "now"))
	{
		time_t	timer;
		struct tm	*local;
		
		timer = time(NULL);
		local = localtime(&timer);
		
		printf("%u/%u/%u %u:%u:%u\n", local -> tm_mon + 1, local -> tm_mday, local -> tm_year + 1900, local -> tm_hour, local -> tm_min,
			local -> tm_sec);
		
		return 0;
	}
	else if(!strcmp(commands[0], "exit"))
		exit(EXIT_SUCCESS);
}
