/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Header file */
#include "macros.h"

int
prepering
(void)
{
	char		SettingFilePath[SETTING_FILE_PATH_MAX], *SettingFileLine, *temp, s[2], format[FORMAT_MAX], SettingName[SETTING_NAME_MAX],
			setting[SETTING_MAX], prompt[PROMPT_MAX]
	FILE		*SettingFilePointer;
	int		c;
	bool		WriteLog;
	
	sprintf(SettingFilePath, ".%cSETTING", PATH_BREAK_CHARACTER);
	
	/* Open setting file */
	SettingFilePointer = fopen(SettingFilePath, "r");
	if(!SettingFilePointer)return 1;
	
	SettingFileLine = (char*)calloc(FILE_LINE_MAX, sizeof(char));
	if(!SettingFileLine)return 1;
	
	while(1)
	{
		strcpy(SettingFileLine, "");
		
		while(1)
		{
			/* Read character from setting file */
			c = fgetc(SettingFilePointer);
			if(c == '\n')break;
			if(c == EOF)goto endread;
			
			/* Buffer >= FILE_LINE_MAX */
			if((strlen(SettingFileLine) + 2) >= FILE_LINE_MAX)
			{
				temp = (char*)realloc(SettingFileLine, strlen(SettingFileLine) + 2);
				if(!temp)
				{
					free(SettingFileLine);
					return 1;
				}
				
				SettingFileLine = temp;
				free(temp);
			}
			
			s = {c, '\0'}
			
			strcat(SettingFileLine, s);
		}
		
		if(!strcmp(SettingFileLine, ""))break;
		
		sprintf(format, "%%%u[^=]=%%%us", SETTING_NAME_MAX, SETTING_MAX);
		sscanf(SettingFileLine, format, SettingName, setting);
		
		if(!strcmp(SettingName, "prompt"))strcpy(prompt, setting);
		else if(!strcmp(SettingName, "WriteLog"))
		{
			if(!strcmp(setting, "true"))WriteLog = true;
			else if(!strcmp(setting, "false"))WriteLog = false;
			else
			{
				free(SettingFileLine);
				return 1;
			}
		}
		else
		{
			free(SettingFileLine);
			return 1;
		}
	}
	
endread:;
	
	/* Close file */
	fclose(SettingFilePointer);
	
	/* Free memory */
	free(SettingFileLine);
	
	return 0;
}
