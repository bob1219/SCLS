/* Standard Libraries */
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

/* Header files */
#include "macros.h"
#include "extern.h"
#include "typedef.h"

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
		if(!mkdir(commands[1]))
		{
			if(WriteLog)
				log('a', "Made a file \"%s\".\n", commands[1]);
			return 0;
		}
		else
		{
			if(WriteLog)
				log('a', "Failed make a file \"%s\".\n", commands[1]);
			return 1;
		}
	}
	else if(!strcmp(commands[0], "rmdir"))
	{
		if(!rmdir(commands[1]))
		{
			if(WriteLog)
				log('a', "Removed a directory \"%s\".\n", commands[1]);
			return 0;
		}
		else
		{
			if(WriteLog)
				log('a', "Failed remove a file \"%s\".\n", commands[1]);
			return 1;
		}
	}
	else if(!strcmp(commands[0], "rename"))
	{
		if(!rename(commands[1], commands[2]))
		{
			if(WriteLog)
				log('a', "Renamed a file or directory \"%s\" -> \"%s\".\n", commands[1], commands[2]);
			return 0;
		}
		else
		{
			if(WriteLog)
				log('a', "Failed rename a file or directory \"%s\" -> \"%s\".\n", commands[1], commands[2]);
			return 1;
		}
	}
	else if(!strcmp(commands[0], "chdir"))
	{
		if(!chdir(commands[1]))
		{
			if(WriteLog)
				log('a', "Changed current directory \"%s\".\n", commands[1]);
			return 0;
		}
		else
		{
			if(WriteLog)
				log('a', "Failed change current directory \"%s\".\n", commands[1]);
			return 1;
		}
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
		
		FilePointer = fopen(commands[1], "w");
		if(!FilePointer)
		{
			if(WriteLog)
				log('a', "Failed make a file \"%s\".\n", commands[1]);
			return 1;
		}
		else
		{
			/* Close file */
			fclose(FilePointer);
			
			if(WriteLog)
				log('a', "Made a file \"%s\".\n", commands[1]);
			return 0;
		}
	}
	else if(!strcmp(commands[0], "rmfile"))
	{
		if(!remove(commands[1]))
		{
			if(WriteLog)
				log('a', "Removed a file \"%s\".\n", commands[1]);
			return 0;
		}
		else
		{
			if(WriteLog)
				log('a', "Failed remove a file \"%s\".\n", commands[1]);
			return 0;
		}
	}
	else if(!strcmp(commands[0], "cpfile"))
	{
		FILE		*FromFilePointer, *ToFilePointer;
		BYTE		b;
		
		/* Open file */
		FromFilePointer	= fopen(commands[1], "rb");
		ToFilePointer		= fopen(commands[2], "wb");
		if((!FromFilePointer) || (!ToFilePointer))
			goto error;
		
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
		
	error:;
		if(WriteLog)
			log('a', "Failed copy file \"%s\" -> \"%s\".\n", commands[1], commands[2]);
		return 1;
	}
}
