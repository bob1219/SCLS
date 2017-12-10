/* Standard Libraries */
#include <direct.h>
#include <stdbool.h>

/* Header file */
#include "extern.h"

/*
 * command_mdir
 *
 * [Description]
 * Make a file
 *
 * [Return value]
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * -	a
 *	type:			unsigned int
 *	description:	Max of command
 *
 * -	commands
 *	type:			const char**
 *	description:	commands
 *
 * [Call from]
 * CommandProcess function
 *
 * [Call to]
 * log function
 */

int
command_mdir
(
unsigned int	a,
const char	**commands
)
{
	if(a < 2)goto mdir_error;
	
	if(!mkdir(commands[1]))
	{
		if(WriteLog)
			log('a', "Made a file \"%s\".\n", commands[1]);
		return 0;
	}
	else goto mdir_error;
	
mdir_error:;
	if(WriteLog)
		log('a', "Failed make a file \"%s\".\n", commands[1]);
	return 1;
}
