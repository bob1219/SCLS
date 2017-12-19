/* Standard Libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Header file */
#include "macros.h"
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
 *	type:		const char*
 *	description:	command
 *
 * [Call from]
 * CommandLine function
 *
 * [Call to]
 * command_mdir function
 * command_rdir function
 * command_chdir function
 * command_cudir function
 * command_rename function
 * command_mfile function
 * command_rfile function
 * command_cpfile function
 * command_lfile function
 * command_tview function
 * command_bview function
 * command_version function
 * command_app function
 * command_date function
 * command_time function
 * command_now function
 * script function
 */

int
CommandProcess
(const char *command)
{
	int	CommandNumber;
	char	commands[COMMAND_NUMBER_MAX][COMMAND_MAX], format[FORMAT_MAX], *a[COMMAND_NUMBER_MAX];
	
	sprintf(format, "%%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us", COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX,
			COMMAND_MAX, COMMAND_MAX, COMMAND_MAX,COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX);
	
	CommandNumber = sscanf(command, format, commands[0], commands[1], commands[2], commands[3], commands[4], commands[5], commands[6], commands[7], commands[8], commands[9], commands[10], commands[11], commands[12], commands[13],
			commands[14], commands[15], commands[16], commands[17], commands[18], commands[19], commands[20]);
	
	for(unsigned int i = 0 ; i < COMMAND_NUMBER_MAX ; i++)
		a[i] = commands[i];
	
	if(!strcmp(commands[0], "mdir"))
		return command_mdir(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "rdir"))
		return command_rdir(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "rename"))
		return command_rename(CommandNumber, commands[1], commands[2]);
	else if(!strcmp(commands[0], "chdir"))
		return command_chdir(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "cudir"))
		return command_cudir();
	else if(!strcmp(commands[0], "mfile"))
		return command_mfile(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "rfile"))
		return command_rfile(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "cpfile"))
		return command_cpfile(CommandNumber, commands[1], commands[2]);
	else if(!strcmp(commands[0], "lfile"))
		return command_lfile(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "tview"))
		return command_tview(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "bview"))
		return command_bview(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "version"))
		return command_version();
	else if(!strcmp(commands[0], "app"))
		return command_app(CommandNumber, (const char**)a);
	else if(!strcmp(commands[0], "date"))
		return command_date();
	else if(!strcmp(commands[0], "time"))
		return command_time();
	else if(!strcmp(commands[0], "now"))
		return command_now();
	else if(!strcmp(commands[0], "exit"))
		exit(EXIT_SUCCESS);
	else if(!strcmp(commands[0], "echo"))
		return command_echo(CommandNumber, (const char**)a);
	else if(!strcmp(commands[0], "script"))
		return script(CommandNumber, commands[1]);
	else if(!strcmp(commands[0], "pause"))
		return command_pause();
	else
	{
		fprintf(stderr, "Unknown command \"%s\".\n", commands[0]);
		return 1;
	}
}
