/* Standard Libraries */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Header files */
#include "macros.h"
#include "extern.h"
#include "functions.h"

/*
 * CommandLine
 *
 * [Description]
 * Input command from standard-input
 *
 * [Return value]
 * Nothing
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * main function
 *
 * [Call to]
 * CommandProcess function
 */

_Noreturn
void
CommandLine
(void)
{
	char	command[COMMAND_MAX];
	
	while(1)
	{
		printf("%s", prompt);
		
		if(!fgets(command, sizeof(command), stdin))
		{
			fprintf(stderr, "Failed input.\n");
			abort();
		}
		if(command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';
		else while(getchar() != '\n');
		
		if(!CommandProcess(command))printf("succeeded.\n");
		else fprintf(stderr, "failed.\n");
		
		putchar('\n');
	}
}
