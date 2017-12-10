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

int
command_cudir
(void);

int
command_mkfile
(
unsigned int,
const char**
);

int
command_rmfile
(
unsigned int,
const char**
);

int
command_cpfile
(
unsigned int,
const char**
);

int
command_lfile
(
unsigned int,
const char**
);

int
command_tview
(
unsigned int,
const char**
);

int
command_bview
(
unsigned int,
const char**
);

int
command_version
(void);

#endif
