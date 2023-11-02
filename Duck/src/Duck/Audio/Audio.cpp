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
#include "Duck/KeyCodes.h"
#include "Duck/Platform/Windows/WindowsInput.h"



namespace Duck {

	/*-----------------------------------------------------------
	\Brief
		Construtor for Audio
	-----------------------------------------------------------*/
	AudioSystem::AudioSystem() :sounds(), loopsPlaying(), soundBanks() {}

	/*-----------------------------------------------------------
	\Brief
		Destructor for Audio
	-----------------------------------------------------------*/
	AudioSystem::~AudioSystem()
	{
		deactivate();
	}

	/*-----------------------------------------------------------
	\Brief
		Function to deactivate FMOD. This function should be 
		called after using the audio engine.
	-----------------------------------------------------------*/
	void AudioSystem::deactivate()
	{
		lowLevelSys->close();
		studioSys->release();
	}

	/*-----------------------------------------------------------
	\Brief
		Function to load the audio asset into FMOD

	\Param soundInfo
		soundInfo is a shared pointer pointing to the audio asset
		that user wants to load.
	-----------------------------------------------------------*/
	void AudioSystem::loadSound(std::shared_ptr<AudioComponent> soundInfo)
	{
		const char* fileName = soundInfo->getFileName().c_str();

		if (!soundInfo->isLoaded())
		{

			FMOD::Sound* sound;
			ERRCHECK(lowLevelSys->createSound(soundInfo->getFilePath().c_str(), FMOD_2D, 0, &sound));
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
	void AudioSystem::playSound(std::shared_ptr<AudioComponent> soundInfo)
	{
		const char* fileName = soundInfo->getFileName().c_str();

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
	void AudioSystem::stopSound(std::shared_ptr<AudioComponent>soundInfo)
	{
		const char* fileName = soundInfo->getFileName().c_str();

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
	void AudioSystem::updateVol(std::shared_ptr<AudioComponent> soundInfo, float newVol)
	{
		std::string fileName = soundInfo->getFileName().c_str();

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
		Function to initialise FMOD. This function should be
		called before using the audio engine.
	-----------------------------------------------------------*/
	void AudioSystem::init()
	{
		ERRCHECK(FMOD::Studio::System::create(&studioSys));
		ERRCHECK(studioSys->getCoreSystem(&lowLevelSys));
		ERRCHECK(lowLevelSys->setSoftwareFormat(AUDIO_SAMPLE_RATE, FMOD_SPEAKERMODE_STEREO, 0));
		ERRCHECK(studioSys->initialize(MAX_AUDIO_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
		ERRCHECK(lowLevelSys->getMasterChannelGroup(&masterGroup));
	}

	/*-----------------------------------------------------------
	\Brief
		Function to update FMOD. This function should be called
		at the beginning of every frame.
	-----------------------------------------------------------*/
	void AudioSystem::audioInputHandler()
	{
		for (auto &entity : m_Entities)
		{
			auto sound = ecs.getComponent<AudioComponent>(entity);

			/*
			input handling

			key z -> oof
			key x -> ooz
			key c -> pew
			*/
			if (WindowsInput::IsKeyPressed(Key::Z))
			{
				if (sound.getFileName() == "oof" && !sound.isPlaying())
				{
					sound.setPlaying(true);
				}
			}

			else if (WindowsInput::IsKeyPressed(Key::X))
			{
				if (sound.getFileName() == "ooz" && !sound.isPlaying())
				{
					sound.setPlaying(true);
				}
			}

			else if (WindowsInput::IsKeyPressed(Key::C))
			{
				if (sound.getFileName() == "pew" && !sound.isPlaying())
				{
					sound.setPlaying(true);
				}
			}

			else
			{
				sound.setPlaying(false);
			}
		}
	}

	/*-----------------------------------------------------------
	\Brief
		Function to update FMOD. This function should be called
		at the beginning of every frame.
	-----------------------------------------------------------*/
	void AudioSystem::update()
	{
		ERRCHECK(studioSys->update());


		for (auto const& entity : m_Entities)
		{
			auto& sound = ecs.getComponent<AudioComponent>(entity);
			std::shared_ptr<AudioComponent> sharedSound = std::make_shared<AudioComponent>(sound.getFileName(), sound.getFilePath());
			sound.setSound(sharedSound);

			//load sounds
			if (!sharedSound->isLoaded())
			{
				loadSound(sharedSound);
			}

			//play sounds
			if (sharedSound->isPlaying())
			{
				playSound(sharedSound);
			}

			/*
			input handling

			key z -> oof
			key x -> ooz
			key c -> pew
			*/
			if (WindowsInput::IsKeyPressed(Key::Z))
			{
				if (sharedSound->getFileName() == "oof" && !sharedSound->isPlaying())
				{
					sharedSound->setPlaying(true);
				}
			}

			else if (WindowsInput::IsKeyPressed(Key::X))
			{
				if (sharedSound->getFileName() == "ooz" && !sharedSound->isPlaying())
				{
					sharedSound->setPlaying(true);
				}
			}

			else if (WindowsInput::IsKeyPressed(Key::C))
			{
				if (sharedSound->getFileName() == "pew" && !sharedSound->isPlaying())
				{
					sharedSound->setPlaying(true);
				}
			}

			else
			{
				sharedSound->setPlaying(false);
			}

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