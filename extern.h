#ifndef	EXTERN_H
#define	EXTERN_H

/* Standard Libraries */
#include <stdbool.h>
#include <stdio.h>

/* Header file */
#include "macros.h"

extern char	prompt[PROMPT_MAX], LogDirectory[FILENAME_MAX];
extern bool	WriteLog;

#endif
