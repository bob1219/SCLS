SCLS
====
SCLS is a command-line-shell project.

Development Environment
-----------------------------
* Programming Language: C  
* Operating System: Microsoft Windows 10  
* Compiler: gcc (MinGW)  

Usage
-------
* mdir  
Make a directory  
`mdir [directory-name]`  

* rdir  
Remove a directory  
`rdir [directory-name]`  

* chdir  
Change current directory  
`chdir [directory-name]`  

* cudir  
Print current directory  
`cudir`  

* rename  
Rename a file or directory  
`rename [oldname] [newname]`  

* mfile  
Make a file  
`mfile [file-name]`  

* rfile  
Remove a file  
`rfile [file-name]`  

* cpfile  
Copy file  
`cpfile [file-name] [file-name]`  

* lfile  
Print list of files and directories in a directory  
`lfile [directory-name]`  

* tview  
Print contents of a text-file  
`tview [file-name]`  

* bview  
Print contents of binary-file  
`bview [file-name]`  

* version  
Print current version  
`version`  

* app  
Execute a application  
`app [application-name] <arguments>`  

* date  
Print current date  
`date`  

* time  
Print current time  
`time`  

* now  
Print current date and time  
`now`  

* exit  
Exit SCLS  
`exit`  

* echo  
Print a text  
`echo [text]`  

* pause
Pause  
`pause`  

* script  
Run a script  
`script [file-name]`  

* path  
Setting path  
`path [command] <argument>`  

files and directories
---------------------
* logs/  
log directory  

* .gitignore  
(Git's file)  

* CommandLine.c  
Source file  

* CommandProcess.c  
Source file  

* commands.c  
Source file  

* extern.h  
Header file  

* functions.h  
Header file  

* LICENSE  
License file  

* macros.h  
Header file  

* main.c  
Source file  

* OutputLog.c  
Source file  

* prepering.c  
Source file  

* scls.exe  
Executable file  

* SETTING  
Setting file  

* typedef.h  
Header file  

* welcome.c  
Source file  

* script.c  
Source file  

* PATH  
Path setting file  

* PathProcess.c  
Source file  

History
--------
* Version 1.0 (December 16th, 2017)  
	* First version  

* Version 1.1 (December 16th, 2017)  
	* Addition a process of unknown command  

* Version 1.2 (December 17th, 2017)  
	* Modify format of output in OutputLog command  
	* Modify format of output in date command  
	* Modify format of output in time command  
	* Modify format of output in now command  
	* Delete needless VLA in app command 
	
* Version 2.0 (December 19th, 2017)  
	* Addition echo command  
	* Addition pause command  
	* Addition script command   

* Version 2.1 (December 20th, 2017)  
	* Bugfix prepering function
	* Bugfix CommandProcess function

* Version 3.0 (December 25th, 2017)  
	* Addition path command
