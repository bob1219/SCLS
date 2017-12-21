/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/* Header file */
#include "macros.h"

/*
 * prepering
 *
 * [Description]
 * Prepering SCLS
 *
 * [Return value]
 * type:	int
 * success:	0
 * failure:	1
 *
 * [Arguments]
 * -	ExecutableFileName
 *  	type:		const char*
 *  	description:	Name of executable-file
 *
 * [Call from]
 * main function
 *
 * [Call to]
 * Nothing
 */

bool	WriteLog = true;
char	prompt[PROMPT_MAX] = "", LogDirectory[FILENAME_MAX] = "", RootDirectory[FILENAME_MAX];

int
prepering
(const char	*ExecutableFileName)
{
	char	SettingFilePath[SETTING_FILE_PATH_MAX], *SettingFileLine, s[2], format[FORMAT_MAX], SettingName[SETTING_NAME_MAX],
		SettingContent[SETTING_MAX], *r;
	FILE	*SettingFilePointer;
	int	c;

	strcpy(RootDirectory, ExecutableFileName);

	r = strstr(RootDirectory, EXECUTABLE_FILE_NAME);
	if(!r)return 1;

	RootDirectory[(int)(r - RootDirectory)] = '\0';

	sprintf(LogDirectory, "%slogs", RootDirectory);
	
	sprintf(SettingFilePath, "%sSETTING", RootDirectory);
	
	/* Open file */
	SettingFilePointer = fopen(SettingFilePath, "r");
	if(!SettingFilePointer)return 1;
	
	SettingFileLine = (char*)calloc(FILE_LINE_MAX, sizeof(char));
	if(!SettingFileLine)return 1;
	
	while(1)
	{
		while(1)
		{
			/* Read a character from setting file */
			c = fgetc(SettingFilePointer);
			if(c == '\n')break;
			if(c == EOF)goto endread;
			
			/* Buffer >= FILE_LINE_MAX */
			if((strlen(SettingFileLine) + 2) > FILE_LINE_MAX)
			{
				char	*temp = (char*)realloc(SettingFileLine, sizeof(char) * (strlen(SettingFileLine) + 2));
				
				if(!temp)return 1;
				SettingFileLine = temp;
				free(temp);
			}
			
			s[0] = c;
			s[1] = '\0';
			
			strcat(SettingFileLine, s);
		}
		
		sprintf(format, "%%%u[^=]=%%%us", SETTING_NAME_MAX, SETTING_MAX);
		sscanf(SettingFileLine, format, SettingName, SettingContent);
		
		if(!strcmp(SettingName, "prompt"))
			strcpy(prompt, SettingContent);
		else if(!strcmp(SettingName, "WriteLog"))
		{
			if(!strcmp(SettingContent, "true"))WriteLog = true;
			else if(!strcmp(SettingContent, "false"))WriteLog = false;
			else return 1;
		}
		else return 1;
		
		strcpy(SettingFileLine, "");
	}
	
endread:;
	
	/* Close file */
	fclose(SettingFilePointer);
	
	/* Free memory */
	free(SettingFileLine);
	
	return 0;
}
