/* Standard Library */
#include <stdio.h>
#include <stdbool.h>

/* Header files */
#include "macros.h"
#include "extern.h"
#include "functions.h"

void
welcome
(void)
{
	printf("Welcome to the SCLS version %s.\n", VERSION);
	
	if(WriteLog)
	{
		if(log('w', "SCLS version %s\n", VERSION))
			fprintf(stderr, "Error: Cannot write the log.\n");
	}
}
