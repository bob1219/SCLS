#ifndef	FUNCTIONS_H
#define	FUNCTIONS_H

int
prepering
(const char*);

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
OutputLog
(
char,
const char*,
...
);

int
command_mdir
(
int,
const char*
);

int
command_rdir
(
int,
const char*
);

int
command_rename
(
int,
const char*,
const char*
);

int
command_chdir
(
int,
const char*
);

int
command_cudir
(void);

int
command_mfile
(
int,
const char*
);

int
command_rfile
(
int,
const char*
);

int
command_cpfile
(
int,
const char*,
const char*
);

int
command_lfile
(
int,
const char*
);

int
command_tview
(
int,
const char*
);

int
command_bview
(
int,
const char*
);

int
command_version
(void);

int
command_app
(
int,
const char**
);

int
command_date
(void);

int
command_time
(void);

int
command_now
(void);

int
command_echo
(
int,
const char**
);

int
script
(
int,
const char*
);

int
command_pause
(void);

#endif
