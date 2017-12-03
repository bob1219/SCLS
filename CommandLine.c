/* Standard Libraries */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
		
		if(!CommandProcess(command))printf("succeeded.\n");
		else fprintf(stderr, "failed.\n");
		
		putchar('\n');
	}
}
