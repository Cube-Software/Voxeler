

/*
    AudioVoxelaux - A very simple OpenAL-based audio engine
    Created by MCL

    -------------------------------
    Copyright (c) 2021-2022 MCL Software
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef VOXELAUX
#define VOXELAUX

#include <AL/al.h>
#include <AL/alc.h>
#include <stdlib.h>
#include <sndfile.h>
#include "../core/log.hpp"

namespace fr::audio
{
	class AudioVoxelaux
	{
		private:		
			ALCdevice *device;
			ALuint source;
			ALuint source1;
			ALuint musicSource;
			ALuint buffer;
			ALCcontext *context;

			void voxelauxLogToFile(std::string logText, int type)
			{
				switch(type)
				{
					case 1:
						fr::log::WarnLog("Warning from Voxelaux: " + logText + "\n");
						break;
					case 2:
						fr::log::ErrorLog("Voxelaux has ran into the following error: " + logText + "\n");
						break;
					case 3:
						fr::log::InfoLog("Voxelaux says, \"" + logText + "\"\n");
				}
			}

		public:
			AudioVoxelaux()
			{
				device = alcOpenDevice(NULL);
				if(!device)
				{
					voxelauxLogToFile("Failed to open audio device", 2);
					return;
				}
				context = alcCreateContext(device, NULL);
				if(!context)
				{
					voxelauxLogToFile("Failed to create audio context", 2);
					return;
				}
				else{
					alGenSources((ALuint)1, &source);
					checkForErrors();

					alSourcef(source, AL_PITCH, 1);
					checkForErrors();

					alSourcef(source, AL_GAIN, 1);
					checkForErrors();

					alSource3f(source, AL_POSITION, 0, 0, 0);
					checkForErrors();

					alSource3f(source, AL_VELOCITY, 0, 0, 0);
					checkForErrors();

					// Create the second sound effect source
					alGenSources((ALuint)1, &source1);
					checkForErrors();

					alSourcef(source1, AL_PITCH, 1);
					checkForErrors();

					alSourcef(source1, AL_GAIN, 1);
					checkForErrors();

					alSource3f(source1, AL_POSITION, 0, 0, 0);
					checkForErrors();

					alSource3f(source1, AL_VELOCITY, 0, 0, 0);
					checkForErrors();

					// Create the music source
					alGenSources((ALuint)1, &musicSource);
					checkForErrors();

					alSourcef(musicSource, AL_PITCH, 1);
					checkForErrors();

					alSourcef(musicSource, AL_GAIN, 1);
					checkForErrors();

					alSource3f(musicSource, AL_POSITION, 0, 0, 0);
					checkForErrors();

					alSource3f(musicSource, AL_VELOCITY, 0, 0, 0);
					checkForErrors();
				}
				alcMakeContextCurrent(context);
				alGenSources(1, &source);
				alGenSources(1, &source1);
				alGenSources(1, &musicSource);
				alGenBuffers(1, &buffer);
				voxelauxLogToFile("Voxelaux has been initialized", 3);
			}

			~AudioVoxelaux()
			{
				alDeleteSources(1, &source);
				alDeleteSources(1, &source1);
				alDeleteSources(1, &musicSource);
				alDeleteBuffers(1, &buffer);
				alcDestroyContext(context);
				alcCloseDevice(device);
				voxelauxLogToFile("Voxelaux has been destroyed", 3);
			}

			static AudioVoxelaux& Ref() {
				static AudioVoxelaux ref;
				return ref;
			}

			ALuint playSound(ALuint sourceToUse, int loop, ALuint buffer){
				ALuint source = sourceToUse;
				alSourcei(source, AL_BUFFER, buffer);
				alSourcei(source, AL_LOOPING, loop);
				alSourcePlay(source);
				return source;
			}
			
			ALuint playSound(int sourceToUse, int loop, ALuint buffer){
						switch(sourceToUse)
				{
					case 0:
						alSourceStop(musicSource); // Stop the music that's currently playing.

						alSourcei(musicSource, AL_LOOPING, loop); // Make the sound looped / not looped
						alSourcei(musicSource, AL_BUFFER, buffer); // Add buffer to source
						alSourcePlay(musicSource); // Play the music

					case 1:
						alSourceStop(source); // Stop the sound that's currently playing

						alSourcei(source, AL_LOOPING, loop); // Make the sound looped / not looped
						alSourcei(source, AL_BUFFER, buffer); // Add buffer to source
						alSourcePlay(source); // Play the sound

					case 2:
						alSourceStop(source1); // Stop the sound that's currently playing

						alSourcei(source1, AL_LOOPING, loop); // Make the sound looped / not looped
						alSourcei(source1, AL_BUFFER, buffer); // Add buffer to source
						alSourcePlay(source1); // Play the sound
				}

			}

			ALuint loadSound(const std::string& path){
				ALenum format;
				SNDFILE *sndFile;
				SF_INFO sfInfo;
				short *memoryBuffer;
				sf_count_t numFrames;
				ALsizei numBytes;

				// Try to open and decode the passed file path
				sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);
				if(!sndFile)
					voxelauxLogToFile("Couldn't open file" + path, 2);
				else
					voxelauxLogToFile("OK: File loaded successfully!", 0);

				if(sfInfo.channels == 1)
				{
					voxelauxLogToFile("OK: File has 1 channel.", 0);
					format = AL_FORMAT_MONO16; // One channel, 16-bits
				}
				else if(sfInfo.channels == 2)
				{
					voxelauxLogToFile("OK: File has 2 channels.", 0);
					format = AL_FORMAT_STEREO16;
				}
				else
				{
					voxelauxLogToFile("Unknown # of channels.", 2);
				}

				memoryBuffer = (short*)malloc((size_t)(sfInfo.frames * sfInfo.channels) * sizeof(short));

				numFrames = sf_readf_short(sndFile, memoryBuffer, sfInfo.frames);
				numBytes = (ALsizei)(numFrames * sfInfo.channels) * (ALsizei)sizeof(short);

				buffer = 0;

				alGenBuffers((ALuint)1, &buffer);
				alBufferData(buffer, format, memoryBuffer, numBytes, sfInfo.samplerate);


				checkForErrors();

				free(memoryBuffer);
				sf_close(sndFile);

				return buffer;
			}

			void checkForErrors(){
				ALCenum error = alGetError();
				if (error != AL_NO_ERROR)
					voxelauxLogToFile("OpenAL Error; alGetError() returned false!", 2);
				else
					voxelauxLogToFile("All good.", 0);
			}
	};
}

#endif