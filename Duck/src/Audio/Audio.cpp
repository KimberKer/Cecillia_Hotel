#include "Audio.h"



namespace AudioMgr {

	/*****************
		SoundInfo
	******************/

	SoundInfo::SoundInfo(const char* fileName, const char* filePath) :
		fileName(fileName), filePath(filePath) {}

	const char* SoundInfo::getFileName()
	{
		return fileName;
	}

	const char* SoundInfo::getFilePath()
	{
		return filePath;
	}

	float SoundInfo::getVolume()
	{
		return vol;
	}

	bool SoundInfo::isLoaded()
	{
		return loaded;
	}

	bool SoundInfo::isPlaying()
	{
		return playing;
	}

	bool SoundInfo::isLoop()
	{
		return looping;
	}

	void SoundInfo::setVol(float newVol)
	{
		vol = newVol;
	}

	void SoundInfo::setLoaded(bool load)
	{
		loaded = load;
	}

	void SoundInfo::setPlaying(bool play)
	{
		playing = play;
	}

	void SoundInfo::setLoop(bool loop)
	{
		looping = loop;
	}

	

	/*****************
		Audio
	******************/

	Audio::Audio() :sounds(), loopsPlaying(), soundBanks() {}

	Audio::~Audio()
	{
		deactivate();
	}

	void Audio::init()
	{
		ERRCHECK(FMOD::Studio::System::create(&studioSys));
		ERRCHECK(studioSys->getCoreSystem(&lowLevelSys));
		ERRCHECK(lowLevelSys->setSoftwareFormat(AUDIO_SAMPLE_RATE, FMOD_SPEAKERMODE_STEREO, 0));
		ERRCHECK(studioSys->initialize(MAX_AUDIO_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
		ERRCHECK(lowLevelSys->getMasterChannelGroup(&masterGroup));
	}

	void Audio::deactivate()
	{
		lowLevelSys->close();
		studioSys->release();
	}

	void Audio::update()
	{
		ERRCHECK(studioSys->update());
	}

	void Audio::loadSound(SoundInfo& soundInfo)
	{
		const char* fileName = soundInfo.getFileName();

		if (!soundInfo.isLoaded())
		{
			FMOD::Sound* sound;
			ERRCHECK(lowLevelSys->createSound(soundInfo.getFilePath(), FMOD_2D, 0, &sound));
			ERRCHECK(sound->setMode(soundInfo.isLoop() ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));
			
			sounds.insert({fileName, sound});

			soundInfo.setLoaded(true);
		}

		else
		{
			std::cout << fileName << " is already loaded!" << std::endl;
		}
	}

	void Audio::playSound(SoundInfo& soundInfo)
	{
		const char* fileName = soundInfo.getFileName();

		if (soundInfo.isLoaded())
		{
			FMOD::Channel* channel;
			ERRCHECK(lowLevelSys->playSound(sounds[fileName], 0, true, &channel));

			channel->setVolume(soundInfo.getVolume());

			if (soundInfo.isLoop())
			{
				loopsPlaying.insert({fileName, channel});
			}

			ERRCHECK(channel->setPaused(false));

			soundInfo.setPlaying(true);
		}

		else
		{
			std::cout << fileName << ": Can't play a sound that is not loaded." << std::endl;
			soundInfo.setPlaying(false);
		}
	}

	void Audio::stopSound(SoundInfo& soundInfo)
	{
		const char* fileName = soundInfo.getFileName();

		if (soundInfo.isPlaying())
		{
			ERRCHECK(loopsPlaying[fileName]->stop());

			soundInfo.setPlaying(false);

			loopsPlaying.erase(fileName);
		}

		else 
		{
			std::cout << fileName << ": Can't stop a sound that's not playing." << std::endl;
		}
	}

	void Audio::updateVol(SoundInfo& soundInfo, float newVol)
	{
		std::string fileName = soundInfo.getFileName();

		if (soundInfo.isPlaying())
		{
			FMOD::Channel* channel = loopsPlaying[fileName];
			ERRCHECK(channel->setVolume(newVol));
			soundInfo.setVol(newVol);
		}

		else
		{
			std::cout << fileName << ": Can't update volume of a sound that's not playing." << std::endl;
		}
	}

	//Error handling for FMOD errors
	void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD ERROR: Audio.cpp [Line " << line << "]" << result << " - " << FMOD_ErrorString(result) << std::endl;
		}
	}

}