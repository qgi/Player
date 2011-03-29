/*
 *  Importer.c
 *  Player
 *
 *  Created by qgi on 28.03.11.
 *
 */

#include "Importer.h"

#define PCM 0x0001

//forward declarations
ALenum alGetBufferFormat(unsigned short usBitsPerSample, unsigned short usChannels);

#pragma pack(1)
struct WAVE_FORMAT
{
	unsigned int		uHeaderLength;
	unsigned short int	usFormat;
	unsigned short int	usChannels;
	unsigned int		uSamplingRate;
	unsigned int		uBytesPerSecond;
	unsigned short int	usBlockAlign;
	unsigned short int	usBitsPerSample;
} waveFormat;

ERR_IMPORT readWavFile(const char szFileName[], ALuint uBuffer)
{
	
	char *pDataBuffer;
	unsigned int uDataBufferLength;
	FILE* pFile;
	long lFileSize;
	ALenum alBufferFormat;
	
	pFile = fopen(szFileName, "rb");
	if (!pFile)
		return ERR_FILE_IO;

	lFileSize = lGetFileSize(pFile);
	
	if(!bSkipPast(pFile, lFileSize, "WAVE") || !bSkipPast(pFile, lFileSize, "fmt "))
		return ERR_HEADER;

	fread(&waveFormat, sizeof(char), sizeof(waveFormat), pFile);

	if (waveFormat.usFormat != PCM)
		return ERR_FORMAT;
	
	alBufferFormat = alGetBufferFormat(waveFormat.usBitsPerSample, waveFormat.usChannels);
	if (alBufferFormat == AL_NONE)
		return ERR_FORMAT;

	if (!bSkipPast(pFile, lFileSize, "data"))
		ERR_DATA;
	
	fread(&uDataBufferLength, sizeof(uDataBufferLength), 1, pFile);
	
	if (uDataBufferLength<1)
		return ERR_DATA;
	
	pDataBuffer = (char*) malloc (uDataBufferLength);
	if (pDataBuffer==NULL)
		return ERR_MEM;
	
	fread(pDataBuffer, sizeof(char), uDataBufferLength, pFile);
	alBufferData(uBuffer, alBufferFormat, pDataBuffer, uDataBufferLength, waveFormat.uSamplingRate);
	free(pDataBuffer);
	fclose(pFile);

	return ERR_OK;
}

ALenum alGetBufferFormat(unsigned short usBitsPerSample, unsigned short usChannels)
{
	
	if (usBitsPerSample == 8)
	{
		if (usChannels == 1)
			return AL_FORMAT_MONO8;
		else if (usChannels == 2)
			return AL_FORMAT_STEREO8;
	}
	else if (usBitsPerSample == 16)
	{
		if (usChannels == 1)
			return AL_FORMAT_MONO16;
		else if (usChannels == 2)
			return AL_FORMAT_STEREO16;
	}
	return AL_NONE;
	
}

