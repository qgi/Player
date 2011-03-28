/*
 *  FileHelpers.h
 *  Player
 *
 *  Created by qgi on 27.03.11.
 *
 */

#pragma once

#include <stdio.h>
#include "Globals.h"

bool bSkipPast(FILE * pFile, long filesize, char identifier[]);

long lGetFileSize(FILE* pFile);

int iReadChunk(FILE* pFile, char nBytes, bool bLittleEndian);

void skipBytes(FILE* pFile, int nBytes);