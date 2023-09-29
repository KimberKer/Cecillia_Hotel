//---------------------------------------------------------
// File:		Audio.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This source file defines the classes aand functions
//              related to the audio engine.
//
// Copyright © 2023 DigiPen, All rights reserved.
//-------------------------------------------------------


#include "duckpch.h"
#include "Audio.h"



namespace Duck {

	/************************************
		Functions for class SoundInfo
	************************************/

	/*-----------------------------------------------------------
	\Brief
		Constructor for SoundInfo.

	\Param fileName
		file name of the audio asset

	\Param filePath
		file path of the audio asset
	-----------------------------------------------------------*/
	SoundInfo::SoundInfo(const char* fileName, const char* filePath) :
		fileName(fileName), filePath(filePath) {}

	/*-----------------------------------------------------------
	\Brief
		Function to get the file name of the audio asset

	\Return
		Returns file name of the audio asset
	-----------------------------------------------------------*/
	const char* SoundInfo::getFileName()
	{
		return fileName;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get the file path of the audio asset

	\Return
		Returns file path of the audio asset
	-----------------------------------------------------------*/
	const char* SoundInfo::getFilePath()
	{
		return filePath;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get the volume set for the audio asset

	\Return
		Returns volume set for the audio asset
	-----------------------------------------------------------*/
	float SoundInfo::getVolume()
	{
		return vol;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to check if the audio is loaded

	\Return
		Returns true if the audio asset is loaded.
		Otherwise, returns false.
	-----------------------------------------------------------*/
	bool SoundInfo::isLoaded()
	{
		return loaded;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to check if the audio is playing

	\Return
		Returns true if audio is playing.
		Otherwise, returns false.
	-----------------------------------------------------------*/
	bool SoundInfo::isPlaying()
	{
		return playing;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to check if the audio is looping

	\Return
		Returns true if the audio is looping.
		Otherwise, return false.
	-----------------------------------------------------------*/
	bool SoundInfo::isLoop()
	{
		return looping;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to set the volume of the audio

	\Param newVol
		Float of the new volume for the audio.
	-----------------------------------------------------------*/
	void SoundInfo::setVol(float newVol)
	{
		vol = newVol;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to set loaded to true/false

	\Param load
		Load indicates if the audio asset is loaded or not.
	-----------------------------------------------------------*/
	void SoundInfo::setLoaded(bool load)
	{
		loaded = load;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to set playing to true/false

	\Param play
		play indicates if the audio is playing or not.
	-----------------------------------------------------------*/
	void SoundInfo::setPlaying(bool play)
	{
		playing = play;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to set looping to true/false

	\Param loop
		loop indicates if the audio is looping or not.
	-----------------------------------------------------------*/
	void SoundInfo::setLoop(bool loop)
	{
		looping = loop;
	}

	

	/************************************
		Functions for class Audio
	************************************/

	/*-----------------------------------------------------------
	\Brief
		Construtor for Audio
	-----------------------------------------------------------*/
	Audio::Audio() :sounds(), loopsPlaying(), soundBanks() {}

	/*-----------------------------------------------------------
	\Brief
		Destructor for Audio
	-----------------------------------------------------------*/
	Audio::~Audio()
	{
		deactivate();
	}

	/*-----------------------------------------------------------
	\Brief
		Function to initialise FMOD. This function should be 
		called before using the audio engine.
	-----------------------------------------------------------*/
	void Audio::init()
	{
		ERRCHECK(FMOD::Studio::System::create(&studioSys));
		ERRCHECK(studioSys->getCoreSystem(&lowLevelSys));
		ERRCHECK(lowLevelSys->setSoftwareFormat(AUDIO_SAMPLE_RATE, FMOD_SPEAKERMODE_STEREO, 0));
		ERRCHECK(studioSys->initialize(MAX_AUDIO_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
		ERRCHECK(lowLevelSys->getMasterChannelGroup(&masterGroup));
	}

	/*-----------------------------------------------------------
	\Brief
		Function to deactivate FMOD. This function should be 
		called after using the audio engine.
	-----------------------------------------------------------*/
	void Audio::deactivate()
	{
		lowLevelSys->close();
		studioSys->release();
	}

	/*-----------------------------------------------------------
	\Brief
		Function to update FMOD. This function should be called 
		at the beginning of every frame.
	-----------------------------------------------------------*/
	void Audio::update()
	{
		ERRCHECK(studioSys->update());
	}

	/*-----------------------------------------------------------
	\Brief
		Function to load the audio asset into FMOD

	\Param soundInfo
		soundInfo is a shared pointer pointing to the audio asset
		that user wants to load.
	-----------------------------------------------------------*/
	void Audio::loadSound(std::shared_ptr<SoundInfo> soundInfo)
	{
		const char* fileName = soundInfo->getFileName();

		if (!soundInfo->isLoaded())
		{

			FMOD::Sound* sound;
			ERRCHECK(lowLevelSys->createSound(soundInfo->getFilePath(), FMOD_2D, 0, &sound));
			ERRCHECK(sound->setMode(soundInfo->isLoop() ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));
			
			sounds.insert({fileName, sound});

			soundInfo->setLoaded(true);
		}

		else
		{
			std::cout << fileName << " is already loaded!" << std::endl;
		}
	}

	/*-----------------------------------------------------------
	\Brief
		Function to play the audio asset.

	\Param soundInfo
		soundInfo is a shared pointer pointing to the audio asset
		that user wants to play.
	-----------------------------------------------------------*/
	void Audio::playSound(std::shared_ptr<SoundInfo> soundInfo)
	{
		const char* fileName = soundInfo->getFileName();

		if (soundInfo->isLoaded())
		{
			FMOD::Channel* channel;
			ERRCHECK(lowLevelSys->playSound(sounds[fileName], 0, true, &channel));

			channel->setVolume(soundInfo->getVolume());

			if (soundInfo->isLoop())
			{
				loopsPlaying.insert({fileName, channel});
			}

			ERRCHECK(channel->setPaused(false));

			soundInfo->setPlaying(true);
		}

		else
		{
			std::cout << fileName << ": Can't play a sound that is not loaded." << std::endl;
			soundInfo->setPlaying(false);
		}
	}

	/*-----------------------------------------------------------
	\Brief
		Function to stop playing the audio asset

	\Param soundInfo
		soundInfo is a shared pointer pointing to the audio asset
		that user wants to stop playing.
	-----------------------------------------------------------*/
	void Audio::stopSound(std::shared_ptr<SoundInfo>soundInfo)
	{
		const char* fileName = soundInfo->getFileName();

		if (soundInfo->isPlaying())
		{
			ERRCHECK(loopsPlaying[fileName]->stop());

			soundInfo->setPlaying(false);

			loopsPlaying.erase(fileName);
		}

		else 
		{
			std::cout << fileName << ": Can't stop a sound that's not playing." << std::endl;
		}
	}

	/*-----------------------------------------------------------
	\Brief
		Function to update the volume of the audio asset.

	\Param soundInfo
		soundInfo is a shared pointer pointing to the audio asset
		that user wants to update the volume of.
	-----------------------------------------------------------*/
	void Audio::updateVol(std::shared_ptr<SoundInfo> soundInfo, float newVol)
	{
		std::string fileName = soundInfo->getFileName();

		if (soundInfo->isPlaying())
		{
			FMOD::Channel* channel = loopsPlaying[fileName];
			ERRCHECK(channel->setVolume(newVol));
			soundInfo->setVol(newVol);
		}

		else
		{
			std::cout << fileName << ": Can't update volume of a sound that's not playing." << std::endl;
		}
	}

	/*-----------------------------------------------------------
	\Brief
		Function check and indicate FMOD errors

	\Param result
		Indicates the FMOD result after calling a FMOD function

	\Param file
		File name of the source file.

	\Param line
		Line where you want to check for errors.
	-----------------------------------------------------------*/
	void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD ERROR: Audio.cpp [Line " << line << "]" << result << " - " << FMOD_ErrorString(result) << std::endl;
		}
	}

}