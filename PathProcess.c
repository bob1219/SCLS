/* Standard Libraries */
#include <stdio.h>
#include <string.h>

/* Header files */
#include "macros.h"
#include "extern.h"

/*
 * PathProcess
 *
 * [Description]
 * Run a process of path
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	filename
 *  		type:		const char*
 *  		description:	Name of file
 *
 * -	result
 *  		type:		char*
 *  		description:	Pointer of result variable
 *
 * -	size
 *  		type:		size_t
 *  		description:	Size of "result"
 *
 * [Call from]
 * command_rfile function
 * command_cpfile function
 * command_tview function
 * command_bview function
 * command_app function
 * script function
 *
 * [Call to]
 * Nothing
 */

int
PathProcess
(
const char	*filename,
char		*result,
size_t		size
)
{
	char	TargetFileName[FILENAME_MAX], PathFileName[FILENAME_MAX], fileline[FILE_LINE_MAX];
	FILE	*TargetFilePointer, *PathFilePointer;

	if((strlen(".") + sizeof(PATH_BREAK_CHARACTER) + strlen(filename) + 1) > sizeof(TargetFileName))
		return 1;

	sprintf(TargetFileName, ".%c%s", PATH_BREAK_CHARACTER, filename);

	TargetFilePointer = fopen(TargetFileName, "rb");
	if(TargetFilePointer)
	{
		fclose(TargetFilePointer);

		if((strlen(".") + 1) > size)
			return 1;

		strcpy(result, ".");
		return 0;
	}
	else
	{
		if((strlen(RootDirectory) + strlen("PATH") + 1) > sizeof(PathFileName))
			return 1;

		sprintf(PathFileName, "%sPATH", RootDirectory);
		
		PathFilePointer = fopen(PathFileName, "r");
		if(!PathFilePointer)return 1;

		while(fgets(fileline, sizeof(fileline), PathFilePointer))
		{
			if(fileline[strlen(fileline) - 1] == '\n')
				fileline[strlen(fileline) - 1] = '\0';

			if((strlen(fileline) + sizeof(PATH_BREAK_CHARACTER) + strlen(filename) + 1) > sizeof(TargetFileName))
				return 1;

			sprintf(TargetFileName, "%s%c%s", fileline, PATH_BREAK_CHARACTER, filename);

			TargetFilePointer = fopen(TargetFileName, "rb");
			if(TargetFilePointer)
			{
				fclose(PathFilePointer);
				fclose(TargetFilePointer);

				if((strlen(fileline) + 1) > size)
					return 1;

				strcpy(result, fileline);
				return 0;
			}
		}

		fclose(PathFilePointer);

		return 1;
	}
}
