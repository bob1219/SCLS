#ifndef	FUNCTIONS_H
#define	FUNCTIONS_H

int
prepering
(void);

void
welcome
(void);

_Noreturn
void
CommandLine
(void);

int
CommandProcess
(const char*);

int
log
(
char,
const char*,
...
);

int
command_mdir
(
unsigned int,
const char**
);

int
command_rmdir
(
unsigned int,
const char**
);

int
command_rename
(
unsigned int,
const char**
);

int
command_chdir
(
unsigned int,
const char**
);

#endif
