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
		log('w', "SCLS version %s\n", VERSION);
}
