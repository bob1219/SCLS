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
	{
		DIR			*DirectoryPointer;
		struct dirent	*directory;
		
		if(a < 2)goto lfile_error;
		
		/* Open directory */
		DirectoryPointer = opendir(commands[1]);
		if(!DirectoryPointer)return 1;
		
		while(directory = readdir(DirectoryPointer))
			printf("%s\n", directory -> d_name);
		
		/* Close directory */
		closedir(DirectoryPointer);
		
		if(WriteLog)
			log('a', "Printed list of file in directory \"%s\".\n", commands[1]);
		return 0;
		
	lfile_error:;
		if(WriteLog)
			log('a', "Failed print list of file in directory \"%s\".\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "tview"))
	{
		FILE	*FilePointer;
		char	FileLine[FILE_LINE_MAX];
		
		/* Open file */
		FilePointer = fopen(commands[1], "r");
		if(!FilePointer)goto tview_error;
		
		for(unsigned int a = 1 ; fgets(FileLine, FILE_LINE_MAX, FilePointer) ; a++)
			printf("%u:\t%s", a, FileLine);
		
		/* Close file */
		fclose(FilePointer);
		
		if(WriteLog)
			log('a', "Printed contents of a file \"%s\" in text mode.\n", commands[1]);
		return 0;
		
	tview_error:;
		if(WriteLog)
			log('a', "Failed print contents of a file \"%s\" in text mode.\n"), commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "bview"))
	{
		FILE		*FilePointer;
		BYTE		b;
		
		/* Open file */
		FilePointer = fopen(commands[1], "r");
		if(!FilePointer)goto bview_error;
		
		for(unsigned int a = 1 ; fread(&b, sizeof(BYTE), 1, FilePointer) ; a++)
		{
			if(a != 1)putchar('-');
			printf("%x", b);
		}
		
		/* Close file */
		fclose(FilePointer);
		
		if(WriteLog)
			log('a', "Printed contents of a file \"%s\" in binary mode.\n", commands[1]);
		return 0;
		
	bview_error:;
		if(WriteLog)
			log('a', "Failed print contents of a file \"%s\" in binary mode.\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "version"))
	{
		printf("SCLS version %s\n", VERSION);
		return 0;
	}
	else if(!strcmp(commands[0], "app"))
	{
		char	*cmd = (char*)calloc(COMMAND_MAX, sizeof(char));
		
		if(!system(NULL))goto app_error;
		
		if(!cmd)goto app_error;
		
		for(unsigned int i = 1 ; i <= a ; i++)
		{
			if((strlen(cmd) + 1 + strlen(commands[i]) + 1) > COMMAND_MAX)
			{
				char	*temp;
				
				temp = (char*)realloc(cmd, strlen(cmd) + 1 + strlen(commands[i]) + 1);
				if(!temp)goto app_error;
				cmd = temp;
			}
			
			sprintf(cmd, "%s %s", cmd, command[i]);
		}
		
		system(cmd);
		
		/* Free memory */
		free(cmd);
		
		if(WriteLog)
			log('a', "Executed a software \"%s\".\n", commands[1]);
		return 0;
		
	app_error:;
		if(WriteLog)
			log('a', "Failed execution a software \"%s\".\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "date"))
	{
		time_t	timer;
		struct tm	*local;
		
		timer = time(NULL);
		local = localtime(&timer);
		
		printf("%u/%u/%u\n", local -> tm_mon + 1, local -> tm_mday, local -> tm_year + 1900);
		
		return 0;
	}
	else if(!strcmp(commands[0], "time"))
	{
		time_t	timer;
		struct tm	*local;
		
		timer = time(NULL);
		local = localtime(&timer);
		
		printf("%u:%u:%u\n", local -> tm_hour, local -> tm_min, local -> tm_sec);
		
		return 0;
	}
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
