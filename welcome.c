/* Standard Library */
#include <stdio.h>

/* Header files */
#include "macros.h"
#include "extern.h"
#include "functions.h"

/*
 * welcome
 *
 * [Description]
 * Print welcome message
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
 * log function
 */

void
welcome
(void)
{
	printf("Welcome to SCLS version %s.\n", VERSION);
	
	if(WriteLog)
		log('w', "SCLS version %s\n", VERSION);
}
