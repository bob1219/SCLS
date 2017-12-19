/* Standard Libraries */
#include <stdio.h>
#include <string.h>

/* Header files */
#include "macros.h"
#include "functions.h"

/*
 * script
 *
 * [Description]
 * Run a script
 *
 * [Return value]
 * type:        int
 * success:     0
 * failure:     1
 *
 * [Arguments]
 * -	CommandNumber
 *		type:			int
 *		description:	Number of command
 *
 * -    filename
 *      type:           const char*
 *      description:    Name of file
 *
 * [Call from]
 * main function
 * CommandProcess function
 *
 * [Call to]
 * CommandProcess function
 */

int
script
(
int			CommandNumber,
const char	*filename
)
{
	FILE	*FilePointer;
	char	FileLine[FILE_LINE_MAX];
	
	if(CommandNumber < 2)return 1;

	/* Open file */
	FilePointer = fopen(filename, "r");
	if(!FilePointer)
	{
		fprintf(stderr, "Error: Cannot open file \"%s\".\n", filename);
		return 1;
	}

	while(fgets(FileLine, FILE_LINE_MAX, FilePointer))
	{
		if(FileLine[strlen(FileLine) - 1] == '\n')
		FileLine[strlen(FileLine) - 1] = '\0';

		if(!CommandProcess(FileLine))printf("succeeded.\n");
		else fprintf(stderr, "failed.\n");
	}

	/* Close file */
	fclose(FilePointer);

	return 0;
}

