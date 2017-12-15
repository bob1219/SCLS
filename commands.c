/* Standard Libraries */
#include <direct.h>
#include <stdio.h>
#include <unistd.h>

/* Header files */
#include "extern.h"
#include "functions.h"
#include "macros.h"

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
 * -	CommandNumber
 *	type:			int
 *	description:	Number of command
 *
 * -	DirectoryName
 *	type:			const char*
 *	description:	Name of directory
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
int			CommandNumber,
const char	*DirectoryName
)
{
	if(CommandNumber < 2)goto mdir_error;
	
	if(!mkdir(DirectoryName))
	{
		if(WriteLog)
			log('a', "Made a directory \"%s\".\n", DirectoryName);
		return 0;
	}
	else goto mdir_error;
	
mdir_error:;
	if(WriteLog)
		log('a', "Failed make a directory \"%s\".\n", DirectoryName);
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
 * -	CommandNumber
 *	type:			int
 *	description:	Number of command
 *
 * -	DirectoryName
 *	type:			const char*
 *	description:	Name of directory
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
int			CommandNumber,
const char	*DirectoryName
)
{
	if(CommandNumber < 2)goto rmdir_error;
	
	if(!rmdir(DirectoryName))
	{
		if(WriteLog)
			log('a', "Removed a directory \"%s\".\n", DirectoryName);
		return 0;
	}
	else goto rmdir_error;
	
rmdir_error:;
	if(WriteLog)
		log('a', "Failed remove a directory \"%s\".\n", DirectoryName);
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
 * -	CommandNumber
 *	type:			int
 *	description:	Number of command
 *
 * -	oldname
 *	type:			const char*
 *	description:	Old name of target directory or file
 *
 * -	newname
 *	type:			const char*
 *	description:	New name of target directory or file
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
int			CommandNumber,
const char	*oldname
const char	*newname
)
{
	if(CommandNumber < 3)goto rename_error;
	
	if(!rename(oldname, newname))
	{
		if(WriteLog)
			log('a', "Renamed \"%s\" -> \"%s\".\n", oldname, newname);
		return 0;
	}
	else goto rename_error;
	
rename_error:;
	if(WriteLog)
		log('a', "Failed rename \"%s\" -> \"%s\".\n", oldname, newname);
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
 * -	CommandNumber
 *	type:			int
 *	description:	Number of command
 *
 * -	DirectoryName
 *	type:			const char*
 *	description:	Name of directory
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
int			CommandNumber,
const char	*DirectoryName
)
{
	if(CommandNumber < 2)goto chdir_error;
	
	if(!chdir(DirectoryName))
	{
		if(WriteLog)
			log('a', "Changed current directory to \"%s\".\n", DirectoryName);
		return 0;
	}
	else goto chdir_error;
	
chdir_error:;
	if(WriteLog)
		log('a', "Failed change current directory to \"%s\".\n", DirectoryName);
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
	
	if(a < 1)return 1;
	
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
	if(a < 1)goto rmfile_error;
	
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
command_cpfile
(
unsigned int	a,
const char	**commands
)
{
	FILE		*FromFilePointer, *ToFilePointer;
	BYTE		b;
	
	if(a < 2)goto cpfile_error;
	
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
	
	if(a < 1)goto lfile_error;
	
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

/*
 * command_tview
 *
 * [Description]
 * Print contents of a text file
 *
 * [Return value]
 * type:		int
 * success:	0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:		unsigned int
 *	description:	Number of command
 *
 * -	commands
 *	type:		const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_tview
(
unsigned int	a,
const char	**commands
)
{
	FILE	*FilePointer;
	char	FileLine[FILE_LINE_MAX];
	
	if(a < 1)goto tview_error;
	
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

/*
 * command_bview
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
command_bview
(
unsigned int	a,
const char	**commands
)
{
	FILE		*FilePointer;
	BYTE	b;
	
	if(a < 1)goto bview_error;
	
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

/*
 * command_version
 *
 * [Description]
 * Print version of SCLS
 *
 * [Return value]
 * type:		int
 * success:		0
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * Nothing
 */

int
command_version
(void)
{
	printf("SCLS version %s\n", VERSION);
	return 0;
}

/*
 * command_app
 *
 * [Description]
 * Execution a software
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
command_app
(
unsigned int	a,
const char	**commands
)
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

/*
 * command_date
 *
 * [Description]
 * Print current date
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
 * Nothing
 */

int
command_date
(void)
{
	time_t	timer;
	struct tm	*local;
	
	timer = time(NULL);
	local = localtime(&timer);
	
	printf("%u/%u/%u\n", local -> tm_mon + 1, local -> tm_mday, local -> tm_year + 1900);
	
	return 0;
}

/*
 * command_time
 *
 * [Description]
 * Print current time
 *
 * [Return value]
 * type:		int
 * success:		0
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * Nothing
 */

int
command_time
(void)
{
	time_t	timer;
	struct tm	*local;
	
	timer = time(NULL);
	local = localtime(&timer);
	
	printf("%u:%u:%u\n", local -> tm_hour, local -> tm_min, local -> tm_sec);
	
	return 0;
}

/*
 * command_now
 *
 * [Description]
 * Print current date and time
 *
 * [Return value]
 * type:		int
 * success:		0
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * Nothing
 */

int
command_now
(void)
{
	time_t	timer;
	struct tm	*local;
	
	timer = time(NULL);
	local = localtime(&timer);
	
	printf("%u/%u/%u %u:%u:%u\n", local -> tm_mon + 1, local -> tm_mday, local -> tm_year + 1900, local -> tm_hour, local -> tm_min,
		local -> tm_sec);
	
	return 0;
}
