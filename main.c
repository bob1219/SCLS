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
 * type:	int
 * success:	EXIT_SUCCESS
 * failure:	EXIT_FAILURE
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
 * script function
 */

int
main
(
int	argc,
char	**argv
)
{
	if(prepering(argv[0]))
	{
		fprintf(stderr, "Failed prepering.\n");
		abort();
	}

	if(argc > 1)
	{
		if(!script(argc, argv[1]))
			return EXIT_SUCCESS;
		else return EXIT_FAILURE;
	}
	
	welcome();
	putchar('\n');
	
	CommandLine();
}
