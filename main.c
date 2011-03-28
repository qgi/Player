/*
 *  Importer.c
 *  Player
 *
 *  Created by qgi on 28.03.11.
 *
 */


#include <stdio.h>
#include "OpenAL/alc.h"
#include "OpenAL/al.h"

#include "Globals.h"
#include "Importer.h"

ALuint uSource;
ALuint uBuffer;

void init();
void play();


int main (int argc, const char * argv[])
{	
	ERR_IMPORT err;
	
	init();
	
	err = readWavFile("mmm.wav", uBuffer);
	
	if (err != ERR_OK)
		return err;

	play();
	
	printf("Press Enter to exit!");
	scanf("...",NULL);
	
    return 0;
}

void init()
{
	
	ALCcontext* alcContext;
	ALCdevice* alcDevice = alcOpenDevice(NULL); 
	
	alcContext = alcCreateContext(alcDevice, NULL);
	alcMakeContextCurrent(alcContext);
	
	alGetError(); 
	ALfloat a_fListenerPosition[] = { 0.0, 0.0, 0.0 };
	ALfloat a_fListenerVelocity[] = { 0.0, 0.0, 0.0 };
	ALfloat a_fListenerOrientation[] = { 0.0, 0.0, -1.0, 0.0, 0.0, 0.0 };
	
	alListenerfv(AL_POSITION, a_fListenerPosition);
	alListenerfv(AL_VELOCITY, a_fListenerVelocity);
	alListenerfv(AL_ORIENTATION, a_fListenerOrientation);
	
	alGenBuffers(1, &uBuffer);
	alGenSources(1, &uSource);
	
	ALfloat a_fSourcePosition[] = { 0.0, 0.0, 0.0 };
	ALfloat a_fSourceVelocity[] = { 0.0, 0.0, 0.0 };
	
	alSourcef (uSource, AL_PITCH, 1.0f );
	alSourcef (uSource, AL_GAIN, 1.0f );
	alSourcefv(uSource, AL_POSITION, a_fSourcePosition);
	alSourcefv(uSource, AL_VELOCITY, a_fSourceVelocity);
	alSourcei (uSource, AL_LOOPING, TRUE);
	
}


void play()
{
	alSourcei (uSource, AL_BUFFER, uBuffer );
	alSourcePlay(uSource);
}


