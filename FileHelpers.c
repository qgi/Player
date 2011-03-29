/*
 *  FileHelpers.c
 *  Player
 *
 *  Created by qgi on 27.03.11.
 *
 */

#include "FileHelpers.h"

long fileSize;


bool bSkipPast(FILE * pFile, long filesize, char identifier[])
{
	int i,j;
	
	j=0;
	for (i=0;i<fileSize;i++)
	{
		char b = fgetc(pFile);
		
		if (b == identifier[j])
		{
			j++;
			if (identifier[j]==0)
				return TRUE;
		}
		else
		{
			j=0;
		}

	}
	return FALSE;
}

long lGetFileSize(FILE* pFile)
{
	fseek (pFile, 0, SEEK_END);
	fileSize = ftell (pFile);
	rewind (pFile);
	return fileSize;
}