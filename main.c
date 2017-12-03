/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>

/* Header file */
#include "functions.h"

int
main
(int	argc,
char	**argv)
{
	if(!prepering())
	{
		fprintf(stderr, "Failed prepering.\n");
		abort();
	}
	
	welcome();
	putchar('\n');
	
	CommandLine();
}
