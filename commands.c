/* Standard Libraries */
#include <direct.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

/* Header file */
#include "extern.h"

/*
 * command_mdir
 *
 * [Description]
 * Make a directory
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_mdir
(
unsigned int	a,
const char	**commands
)
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

/*
 * command_rmdir
 *
 * [Description]
 * Remove a directory
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_rmdir
(
unsigned int	a,
const char	**commands
)
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

/*
 * command_rename
 *
 * [Description]
 * Rename a file or directory
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_rename
(
unsigned int	a,
const char	**commands
)
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

/*
 * command_chdir
 *
 * [Description]
 * Change current directory
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_chdir
(
unsigned int	a,
const char	**commands
)
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

/*
 * command_cudir
 *
 * [Description]
 * Print current directory
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_cudir
(void)
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

/*
 * command_mkfile
 *
 * [Description]
 * Make a file
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_mkfile
(
unsigned int	a,
const char	**commands
)
{
	FILE	*FilePointer;
	
	if(a < 2)return 1;
	
	/* Open file */
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

/*
 * command_rmfile
 *
 * [Description]
 * Remove a file
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_rmfile
(
unsigned int	a,
const char	**commands
)
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
	return 1;
}

/*
 * command_cpfile
 *
 * [Description]
 * Copy a file
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_cpfile
(
unsigned int	a,
const char	**commands
)
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

/*
 * command_lfile
 *
 * [Description]
 * Print list of in current directory
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_lfile
(
unsigned int	a,
const char	**commands
)
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
