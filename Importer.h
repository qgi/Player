/*
 *  Importer.h
 *  Player
 *
 *  Created by qgi on 28.03.11.
 *
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "OpenAL/al.h"
#include "FileHelpers.h"

typedef enum
{
	ERR_OK,
	ERR_FILE_IO,
	ERR_HEADER,
	ERR_FORMAT,
	ERR_CHANNELS,
	ERR_BPS,
	ERR_DATA,
	ERR_MEM
	
} ERR_IMPORT;

ERR_IMPORT readWavFile(char szFileName[], ALuint uBuffer);