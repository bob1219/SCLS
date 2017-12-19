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
 * type:		int
 * success:		0
 * failure:		1
 *
 * [Arguments]
 * Nothing
 *
 * [Call from]
 * main function
 *
 * [Call to]
 * Nothing
 */

bool	WriteLog = true;
char	prompt[PROMPT_MAX] = "", LogDirectory[FILENAME_MAX] = "";

int
prepering
(void)
{
	char	SettingFilePath[SETTING_FILE_PATH_MAX], *SettingFileLine, s[2], format[FORMAT_MAX], SettingName[SETTING_NAME_MAX],
			SettingContent[SETTING_MAX], RootDirectory[FILENAME_MAX];
	FILE	*SettingFilePointer;
	int	c;
	
	if(!getcwd(RootDirectory, FILENAME_MAX))
		return 1;
	if(RootDirectory[strlen(RootDirectory) - 1] == PATH_BREAK_CHARACTER)
		RootDirectory[strlen(RootDirectory) - 1] = '\0';
	sprintf(LogDirectory, "%s%clogs", RootDirectory, PATH_BREAK_CHARACTER);
	
	sprintf(SettingFilePath, ".%cSETTING", PATH_BREAK_CHARACTER);
	
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
