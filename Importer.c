/*
 *  Importer.c
 *  Player
 *
 *  Created by qgi on 28.03.11.
 *
 */

#include "Importer.h"

#define PCM 0x0001

ERR_IMPORT readWavFile(char szFileName[], ALuint uBuffer)
{
	
	char *pDataBuffer;
	long uDataBufferLength;

	FILE* pFile;
	long lFileSize;
	unsigned short int	usFormat;
	unsigned short int	usChannels;
	unsigned int		uSamplingRate;
	unsigned short int	usBitsPerSample;
	ALenum alBufferFormat;
	pFile = fopen(szFileName, "rb");
	
	if (!pFile)
		return ERR_FILE_IO;

	lFileSize = lGetFileSize(pFile);
	
	if(!bSkipPast(pFile, lFileSize, "WAVE") || !bSkipPast(pFile, lFileSize, "fmt "))
		return ERR_HEADER;
	
	//skip header length (4bytes)
	skipBytes(pFile, 4);
	
	usFormat = (unsigned int) iReadChunk(pFile, 2, TRUE);
	
	if (usFormat != PCM)
		return ERR_FORMAT;
	
	usChannels = (unsigned short int) iReadChunk(pFile, 2, TRUE);
	if (usChannels<1 || usChannels >2)
		return ERR_CHANNELS;
	
	uSamplingRate = (unsigned int) iReadChunk(pFile, 4, TRUE);
	skipBytes(pFile, 6);
	
	usBitsPerSample = (unsigned short int) iReadChunk(pFile, 2, TRUE);
	
	if (usBitsPerSample == 8)
	{
		if (usChannels == 1)
			alBufferFormat = AL_FORMAT_MONO8;
		else 
			alBufferFormat = AL_FORMAT_STEREO8;
	}
	else if (usBitsPerSample == 16)
	{
		if (usChannels == 1)
			alBufferFormat = AL_FORMAT_MONO16;
		else
			alBufferFormat = AL_FORMAT_STEREO16;
	}
	else
	{
		return ERR_BPS;
	}
	
	if (!bSkipPast(pFile, lFileSize, "data"))
		ERR_DATA;
		
	uDataBufferLength = (unsigned int) iReadChunk(pFile, 4, TRUE);
	if (uDataBufferLength<1)
		return ERR_DATA;
	
	pDataBuffer = (char*) malloc (uDataBufferLength);
	if (pDataBuffer==NULL)
		return ERR_MEM;
	
	fread(pDataBuffer, sizeof(char), uDataBufferLength, pFile);
	alBufferData(uBuffer, alBufferFormat, pDataBuffer, uDataBufferLength, uSamplingRate);
	free(pDataBuffer);
	
	return ERR_OK;
}
