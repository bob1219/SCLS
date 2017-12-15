/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>

/* Header file */
#include "functions.h"

/*
 * main
 *
 * [Description]
 * Nothing
 *
 * [Return value]
 * type: int
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * Operating System
 *
 * [Call to]
 * prepering function
 * welcome function
 * CommandLine function
 */

int
main
(void)
{
	if(prepering())
	{
		fprintf(stderr, "Failed prepering.\n");
		abort();
	}
	
	welcome();
	putchar('\n');
	
	CommandLine();
}
