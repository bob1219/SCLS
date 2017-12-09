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
	sprintf(format, "%%%us %%%u[^\0]", COMMAND_MAX, COMMAND_MAX);
	
	for(a = 0 ; (a <= COMMAND_NUMBER_MAX) || (strcmp(command2, ";")) ; a++)
		sscanf(command2, format, commands[a], command2);
	
	a--;
	
	if(!strcmp(commands[0], "mdir"))
	{
		if(a < 2)goto mdir_error;
		
		if(!mkdir(commands[1]))
		{
			if(WriteLog)
				log('a', "Made a file \"%s\".\n", commands[1]);
			return 0;
		}
		else goto mdir_error;
		
	mdir_error:;
		if(WriteLog)
			log('a', "Failed make a file \"%s\".\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "rmdir"))
	{
		if(a < 2)goto rmdir_error;
		
		if(!rmdir(commands[1]))
		{
			if(WriteLog)
				log('a', "Removed a directory \"%s\".\n", commands[1]);
			return 0;
		}
		else goto rmdir_error;
		
	rmdir_error:;
		if(WriteLog)
			log('a', "Failed remove a file \"%s\".\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "rename"))
	{
		if(a < 3)goto rename_error;
		
		if(!rename(commands[1], commands[2]))
		{
			if(WriteLog)
				log('a', "Renamed a file or directory \"%s\" -> \"%s\".\n", commands[1], commands[2]);
			return 0;
		}
		else goto rename_error;
		
	rename_error:;
		if(WriteLog)
			log('a', "Failed rename a file or directory \"%s\" -> \"%s\".\n", commands[1], commands[2]);
		return 1;
	}
	else if(!strcmp(commands[0], "chdir"))
	{
		if(a < 2)goto chdir_error;
		
		if(!chdir(commands[1]))
		{
			if(WriteLog)
				log('a', "Changed current directory \"%s\".\n", commands[1]);
			return 0;
		}
		else goto chdir_error;
		
	chdir_error:;
		if(WriteLog)
			log('a', "Failed change current directory \"%s\".\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "cudir"))
	{
		char	CurrentDirectory[FILENAME_MAX];
		
		if(!getcwd(CurrentDirectory, FILENAME_MAX))
		{
			printf("current directory: \"%s\"\n", CurrentDirectory);
			
			if(WriteLog)
				log('a', "Current directory is \"%s\".\n", CurrentDirectory);
			return 0;
		}
		else
		{
			if(WriteLog)
				log('a', "Failed get current directory.\n");
			return 1;
		}
	}
	else if(!strcmp(commands[0], "mkfile"))
	{
		FILE	*FilePointer;
		
		if(a < 2)return 1;
		
		FilePointer = fopen(commands[1], "w");
		if(!FilePointer)goto mkfile_error;
		else
		{
			/* Close file */
			fclose(FilePointer);
			
			if(WriteLog)
				log('a', "Made a file \"%s\".\n", commands[1]);
			return 0;
		}
		
	mkfile_error:;
		if(WriteLog)
			log('a', "Failed make a file \"%s\".\n", commands[1]);
		return 1;
	}
	else if(!strcmp(commands[0], "rmfile"))
	{
		if(a < 2)goto rmfile_error;
		
		if(!remove(commands[1]))
		{
			if(WriteLog)
				log('a', "Removed a file \"%s\".\n", commands[1]);
			return 0;
		}
		else goto rmfile_error;
		
	rmfile_error:;
		if(WriteLog)
			log('a', "Failed remove a file \"%s\".\n", commands[1]);
		return 0;
	}
	else if(!strcmp(commands[0], "cpfile"))
	{
		FILE		*FromFilePointer, *ToFilePointer;
		BYTE		b;
		
		if(a < 3)goto cpfile_error;
		
		/* Open file */
		FromFilePointer	= fopen(commands[1], "rb");
		ToFilePointer		= fopen(commands[2], "wb");
		if((!FromFilePointer) || (!ToFilePointer))
			goto cpfile_error;
		
		while(1)
		{
			if(fread(&b, sizeof(BYTE), 1, FromFilePointer) != 1)break;
			if(fwrite(&b, sizeof(BYTE), 1, ToFilePointer) != 1)break;
		}
		
		/* Close file */
		fclose(FromFilePointer);
		fclose(ToFilePointer);
		
		if(WriteLog)
			log('a', "Copied file \"%s\" -> \"%s\".\n", commands[1], commands[2]);
		return 0;
		
	cpfile_error:;
		if(WriteLog)
			log('a', "Failed copy file \"%s\" -> \"%s\".\n", commands[1], commands[2]);
		return 1;
	}
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
