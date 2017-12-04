/* Standard Library */
#include <stdio.h>
#include <stdbool.h>

/* Header files */
#include "macros.h"
#include "extern.h"

void
welcome
(void)
{
	printf("Welcome to the SCLS version %s.\n", VERSION);
	
	if(WriteLog)
	{
		if(log)fprintf(stderr, "Error: Cannot write the log.\n");
	}
}
