/* Standard Libraries */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Header files */
#include "macros.h"
#include "extern.h"

_Noreturn
void
CommandLine
(void)
{
	char	command[COMMAND_MAX];
	
	while(1)
	{
		printf("%s", prompt);
		
		if(!fgets(command, COMMAND_MAX, stdin))
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
