/* Standard Library */
#include <stdio.h>
#include <stdbool.h>

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
	printf("Welcome to the SCLS version %s.\n", VERSION);
	
	if(WriteLog)
		log('w', "SCLS version %s\n", VERSION);
}
