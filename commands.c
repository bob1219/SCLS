/* Standard Libraries */
#include <direct.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>

/* Header files */
#include "extern.h"
#include "functions.h"
#include "macros.h"
#include "typedef.h"

/*
 * command_mdir
 *
 * [Description]
 * Make a directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	DirectoryName
 *		type:		const char*
 *		description:	Name of directory
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_mdir
(
int		CommandNumber,
const char	*DirectoryName
)
{
	if(CommandNumber < 2)goto mdir_error;
	
	if(!mkdir(DirectoryName))
	{
		if(WriteLog)
			OutputLog('a', "Made a directory \"%s\".\n", DirectoryName);
		return 0;
	}
	else goto mdir_error;
	
mdir_error:;
	if(WriteLog)
		OutputLog('a', "Failed make a directory.\n");
	return 1;
}

/*
 * command_rdir
 *
 * [Description]
 * Remove a directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	DirectoryName
 *		type:		const char*
 *		description:	Name of directory
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_rdir
(
int		CommandNumber,
const char	*DirectoryName
)
{
	if(CommandNumber < 2)goto rdir_error;
	
	if(!rmdir(DirectoryName))
	{
		if(WriteLog)
			OutputLog('a', "Removed a directory \"%s\".\n", DirectoryName);
		return 0;
	}
	else goto rdir_error;
	
rdir_error:;
	if(WriteLog)
		OutputLog('a', "Failed remove a directory.\n");
	return 1;
}

/*
 * command_rename
 *
 * [Description]
 * Rename a file or directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	oldname
 *		type:		const char*
 *		description:	Old name of target directory or file
 *
 * -	newname
 *		type:		const char*
 *		description:	New name of target directory or file
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_rename
(
int		CommandNumber,
const char	*oldname,
const char	*newname
)
{
	if(CommandNumber < 3)goto rename_error;
	
	if(!rename(oldname, newname))
	{
		if(WriteLog)
			OutputLog('a', "Renamed \"%s\" -> \"%s\".\n", oldname, newname);
		return 0;
	}
	else goto rename_error;
	
rename_error:;
	if(WriteLog)
		OutputLog('a', "Failed rename.\n");
	return 1;
}

/*
 * command_chdir
 *
 * [Description]
 * Change current directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	DirectoryName
 *		type:		const char*
 *		description:	Name of directory
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_chdir
(
int		CommandNumber,
const char	*DirectoryName
)
{
	if(CommandNumber < 2)goto chdir_error;
	
	if(!chdir(DirectoryName))
	{
		if(WriteLog)
			OutputLog('a', "Changed current directory to \"%s\".\n", DirectoryName);
		return 0;
	}
	else goto chdir_error;
	
chdir_error:;
	if(WriteLog)
		OutputLog('a', "Failed change current directory.\n");
	return 1;
}

/*
 * command_cudir
 *
 * [Description]
 * Print current directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_cudir
(void)
{
	char	CurrentDirectory[FILENAME_MAX];
	
	if(!getcwd(CurrentDirectory, FILENAME_MAX))
	{
		if(WriteLog)
			OutputLog('a', "Failed get current directory.\n");
		return 1;
	}
	else
	{
		printf("current directory: \"%s\"\n", CurrentDirectory);
		
		if(WriteLog)
			OutputLog('a', "Current directory is \"%s\".\n", CurrentDirectory);
		return 0;
	}
}

/*
 * command_mfile
 *
 * [Description]
 * Make a file
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	FileName
 *		type:		const char*
 *		description:	Name of file
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_mfile
(
int		CommandNumber,
const char	*FileName
)
{
	FILE	*FilePointer;
	
	if(CommandNumber < 2)goto mfile_error;
	
	/* Open file */
	FilePointer = fopen(FileName, "w");
	if(!FilePointer)goto mfile_error;
	
	/* Close file */
	fclose(FilePointer);
	
	if(WriteLog)
		OutputLog('a', "Made a file \"%s\".\n", FileName);
	return 0;
	
mfile_error:;
	if(WriteLog)
		OutputLog('a', "Failed make a file.\n");
	return 1;
}

/*
 * command_rfile
 *
 * [Description]
 * Remove a file
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	FileName
 *		type:		const char*
 *		description:	Name of file
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_rfile
(
int		CommandNumber,
const char	*FileName
)
{
	char	CurrentDirectory[FILENAME_MAX], result[FILENAME_MAX];
	int	r;

	if(CommandNumber < 2)goto rfile_error;

	if(!remove(FileName))
	{
		if(WriteLog)
			OutputLog('a', "Removed a file \"%s\".\n", FileName);
		return 0;
	}
	else goto rfile_error;
	
rfile_error:;
	if(WriteLog)
		OutputLog('a', "Failed remove a file.\n");
	return 1;
}

/*
 * command_cpfile
 *
 * [Description]
 * Copy a file
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	from
 *		type:		const char*
 *		description:	Name of copy source file
 *
 * -	to
 *		type:		const char*
 *		description:	Name of copy destination file
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_cpfile
(
int		CommandNumber,
const char	*from,
const char	*to
)
{
	FILE	*FromFilePointer, *ToFilePointer;
	BYTE	b;
	char	CurrentDirectory[FILENAME_MAX], result[FILENAME_MAX];
	
	if(CommandNumber < 3)goto cpfile_error;

	if(!getcwd(CurrentDirectory, sizeof(CurrentDirectory)))
		goto cpfile_error;

	if(PathProcess(from, result, sizeof(result)))
		goto cpfile_error;

	if(chdir(result))goto cpfile_error;

	/* Open file */
	FromFilePointer = fopen(from, "rb");
	ToFilePointer = fopen(to, "wb");
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
	
	if(chdir(CurrentDirectory))goto cpfile_error;

	if(WriteLog)
		OutputLog('a', "Copied file \"%s\" -> \"%s\".\n", from, to);
	return 0;
	
cpfile_error:;
	if(WriteLog)
		OutputLog('a', "Failed copy file.\n");
	return 1;
}

/*
 * command_lfile
 *
 * [Description]
 * Print list of in current directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	DirectoryName
 *		type:		const char*
 *		description:	Name of directory
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_lfile
(
int		CommandNumber,
const char	*DirectoryName
)
{
	DIR		*DirectoryPointer;
	struct dirent	*directory;
	
	if(CommandNumber < 2)goto lfile_error;
	
	/* Open directory */
	DirectoryPointer = opendir(DirectoryName);
	if(!DirectoryPointer)goto lfile_error;
	
	while(directory = readdir(DirectoryPointer))
		printf("%s\n", directory -> d_name);
	
	/* Close directory */
	closedir(DirectoryPointer);
	
	if(WriteLog)
		OutputLog('a', "Printed list of files in directory \"%s\".\n", DirectoryName);
	return 0;
	
lfile_error:;
	if(WriteLog)
		OutputLog('a', "Failed print list of file.\n");
	return 1;
}

/*
 * command_tview
 *
 * [Description]
 * Print contents of a text file
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	FileName
 *		type:		const char*
 *		description:	Name of file
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_tview
(
int		CommandNumber,
const char	*FileName
)
{
	FILE	*FilePointer;
	char	FileLine[FILE_LINE_MAX], CurrentDirectory[FILENAME_MAX], result[FILENAME_MAX];
	
	if(CommandNumber < 2)goto tview_error;
	
	if(!getcwd(CurrentDirectory, sizeof(CurrentDirectory)))
		goto tview_error;

	if(PathProcess(FileName, result, sizeof(result)))
		goto tview_error;

	if(chdir(result))goto tview_error;

	/* Open file */
	FilePointer = fopen(FileName, "r");
	if(!FilePointer)goto tview_error;
	
	for(unsigned int i = 1 ; fgets(FileLine, sizeof(FileLine), FilePointer) ; i++)
	{
		if(FileLine[strlen(FileLine) - 1] == '\n')
			FileLine[strlen(FileLine) - 1] = '\0';
		printf("%u:\t%s\n", i, FileLine);
	}
	
	/* Close file */
	fclose(FilePointer);
	
	if(chdir(CurrentDirectory))goto tview_error;

	if(WriteLog)
		OutputLog('a', "Printed contents of a text-file \"%s\".\n", FileName);
	return 0;
	
tview_error:;
	if(WriteLog)
		OutputLog('a', "Failed print contents of a text-file.\n");
	return 1;
}

/*
 * command_bview
 *
 * [Description]
 * Print list of in current directory
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	FileName 
 *		type:		const char*
 *		description:	Name of file
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_bview
(
int		CommandNumber,
const char	*FileName
)
{
	FILE	*FilePointer;
	BYTE	b;
	char	CurrentDirectory[FILENAME_MAX], result[FILENAME_MAX];
	
	if(CommandNumber < 2)goto bview_error;
	
	if(!getcwd(CurrentDirectory, sizeof(CurrentDirectory)))
		goto bview_error;

	if(PathProcess(FileName, result, sizeof(result)))
		goto bview_error;

	if(chdir(result))goto bview_error;

	/* Open file */
	FilePointer = fopen(FileName, "rb");
	if(!FilePointer)goto bview_error;
	
	for(unsigned int a = 1 ; fread(&b, sizeof(BYTE), 1, FilePointer) ; a++)
	{
		if(a != 1)putchar('-');
		printf("%02X", b);
	}
	
	/* Close file */
	fclose(FilePointer);
	
	putchar('\n');
	
	if(chdir(CurrentDirectory))goto bview_error;

	if(WriteLog)
		OutputLog('a', "Printed contents of a binary-file \"%s\".\n", FileName);
	return 0;
	
bview_error:;
	if(WriteLog)
		OutputLog('a', "Failed print contents of a binary-file.\n");
	return 1;
}

/*
 * command_version
 *
 * [Description]
 * Print version of SCLS
 *
 * [Return value]
 * type:	int
 * success:	0
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
 * Execution a application
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:		int
 *		description:	Number of command
 *
 * -	commands
 *		type:		const char**
 *		description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_app
(
int		CommandNumber,
const char	**commands
)
{
	char	cmd[COMMAND_MAX] = "", CurrentDirectory[FILENAME_MAX], result[FILENAME_MAX];
	int	r;
	
	if(!system(NULL))goto app_error;
	
	if(!getcwd(CurrentDirectory, sizeof(CurrentDirectory)))
		goto app_error;

	if(PathProcess(commands[1], result, sizeof(result)))
		goto app_error;

	if(chdir(result))goto app_error;

	for(unsigned int i = 1 ; i < CommandNumber ; i++)
	{
		if(i == 1)
		{
			if((strlen(commands[i]) + 1) > sizeof(cmd))
				return 1;

			strcpy(cmd, commands[i]);
		}
		else
		{
			if((strlen(cmd) + strlen(" ") + strlen(commands[i]) + 1) > sizeof(cmd))
				return 1;

			sprintf(cmd, "%s %s", cmd, commands[i]);
		}
	}
	
	r = system(cmd);
	
	if(chdir(CurrentDirectory))goto app_error;

	if(WriteLog)
		OutputLog('a', "Executed a application \"%s\", Return value is %d.\n", commands[1], r);
	return r;
	
app_error:;
	if(WriteLog)
		OutputLog('a', "Failed execution a application.\n");
	return 1;
}

/*
 * command_date
 *
 * [Description]
 * Print current date
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
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
	time_t		timer;
	struct tm	*local;
	char		month[MONTH_MAX], day[DAY_MAX];
	
	timer = time(NULL);
	local = localtime(&timer);
	
	switch(local -> tm_mon)
	{
	case 0:
		strcpy(month, "January");
		break;
		
	case 1:
		strcpy(month, "February");
		break;
		
	case 2:
		strcpy(month, "March");
		break;
		
	case 3:
		strcpy(month, "April");
		break;
		
	case 4:
		strcpy(month, "May");
		break;
		
	case 5:
		strcpy(month, "June");
		break;
		
	case 6:
		strcpy(month, "July");
		break;
		
	case 7:
		strcpy(month, "August");
		break;
		
	case 8:
		strcpy(month, "September");
		break;
		
	case 9:
		strcpy(month, "October");
		break;
		
	case 10:
		strcpy(month, "November");
		break;
		
	case 11:
		strcpy(month, "December");
		break;
	}
	
	switch(local -> tm_mday)
	{
	case 1:
	case 21:
	case 31:
		sprintf(day, "%dst", local -> tm_mday);
		break;
		
	case 2:
	case 22:
		sprintf(day, "%dnd", local -> tm_mday);
		break;
		
	case 3:
	case 23:
		sprintf(day, "%drd", local -> tm_mday);
		break;
		
	default:
		sprintf(day, "%dth", local -> tm_mday);
		break;
	}
	
	printf("%s %s, %d\n", month, day, local -> tm_year + 1900);
	
	return 0;
}

/*
 * command_time
 *
 * [Description]
 * Print current time
 *
 * [Return value]
 * type:	int
 * success:	0
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
	time_t		timer;
	struct tm	*local;
	
	timer = time(NULL);
	local = localtime(&timer);
	
	printf("%d:%02d:%02d\n", local -> tm_hour, local -> tm_min, local -> tm_sec);
	
	return 0;
}

/*
 * command_now
 *
 * [Description]
 * Print current date and time
 *
 * [Return value]
 * type:	int
 * success:	0
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
	time_t		timer;
	struct tm	*local;
	char		month[MONTH_MAX], day[DAY_MAX];
	
	timer = time(NULL);
	local = localtime(&timer);
	
	switch(local -> tm_mon)
	{
	case 0:
		strcpy(month, "January");
		break;
		
	case 1:
		strcpy(month, "February");
		break;
		
	case 2:
		strcpy(month, "March");
		break;
		
	case 3:
		strcpy(month, "April");
		break;
		
	case 4:
		strcpy(month, "May");
		break;
		
	case 5:
		strcpy(month, "June");
		break;
		
	case 6:
		strcpy(month, "July");
		break;
		
	case 7:
		strcpy(month, "August");
		break;
		
	case 8:
		strcpy(month, "September");
		break;
		
	case 9:
		strcpy(month, "October");
		break;
		
	case 10:
		strcpy(month, "November");
		break;
		
	case 11:
		strcpy(month, "December");
		break;
	}
	
	switch(local -> tm_mday)
	{
	case 1:
	case 21:
	case 31:
		sprintf(day, "%dst", local -> tm_mday);
		break;
		
	case 2:
	case 22:
		sprintf(day, "%dnd", local -> tm_mday);
		break;
		
	case 3:
	case 23:
		sprintf(day, "%drd", local -> tm_mday);
		break;
		
	default:
		sprintf(day, "%dth", local -> tm_mday);
		break;
	}
	
	printf("%s %s, %d %d:%02d:%02d\n", month, day, local -> tm_year + 1900, local -> tm_hour, local -> tm_min, local -> tm_sec);
	
	return 0;
}

/*
 * command_echo
 *
 * [Description]
 * Print a text
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *  	type:		int
 *  	description:	Number of command
 *
 * -	commands
 *  	type:		const char**
 *  	description:	commands
 *
 * [Call from]
 * ComamndProcess function
 *
 * [Call to]
 * Nothing
 */

int
command_echo
(
int		CommandNumber,
const char	**commands
)
{
	char	text[TEXT_MAX];

	for(unsigned int i = 1 ; i < CommandNumber ; i++)
	{
		if(i == 1)strcpy(text, commands[i]);
		else sprintf(text, "%s %s", text, commands[i]);
	}

	printf("%s\n", text);

	return 0;
}

/*
 * command_pause
 *
 * [Description]
 * Pause
 *
 * [Return value]
 * type:	int
 * success:	0
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
command_pause
(void)
{
	printf("Press ENTER key to continue...");
	getchar();

	return 0;
}

/*
 * command_path
 *
 * [Description]
 * Setting path
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	CommandNumber
 *  	type:		int
 *  	description:	Number of command
 *
 * -	command
 *  	type:		const char*
 *  	description:	Command of path
 *
 * -	argument
 *  	type:		const char*
 *  	description:	Argument of path
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * OutputLog function
 */

int
command_path
(
int		CommandNumber,
const char	*command,
const char	*argument
)
{
	FILE	*FilePointer;
	char	filename[FILENAME_MAX];

	sprintf(filename, "%sPATH", RootDirectory);

	if(!strcmp(command, "clear"))
	{
		FilePointer = fopen(filename, "w");
		if(!FilePointer)
		{
			if(WriteLog)
				OutputLog('a', "Failed clear path setting file.\n");
			return 1;
		}
		else
		{
			fclose(FilePointer);
			if(WriteLog)
				OutputLog('a', "Cleared path setting file.\n");
			return 0;
		}
	}
	else if(!strcmp(command, "list"))
	{
		char	fileline[FILE_LINE_MAX];

		/* Open file */
		FilePointer = fopen(filename, "r");
		if(!FilePointer)
		{
			if(WriteLog)
				OutputLog('a', "Failed print list of path.\n");
			return 1;
		}

		for(unsigned int i = 1 ; fgets(fileline, sizeof(fileline), FilePointer) ; i++)
		{
			if(fileline[strlen(fileline) - 1] == '\n')
				fileline[strlen(fileline) - 1] = '\0';

			printf("%u:\t%s\n", i, fileline);
		}

		/* Close file */
		fclose(FilePointer);

		if(WriteLog)
			OutputLog('a', "Printed list of path.\n");
		return 0;
	}
	else if(!strcmp(command, "add"))
	{
		/* Open file */
		FilePointer = fopen(filename, "a");
		if(!FilePointer)
		{
			if(WriteLog)
				OutputLog('a', "Failed addition setting of path.\n");
			return 1;
		}

		fprintf(FilePointer, "%s\n", argument);

		/* Close file */
		fclose(FilePointer);

		if(WriteLog)
			OutputLog('a', "Additioned setting of path.\n");
		return 0;
	}
}
