#pragma once

#include "../FMOD/api/studio/inc/fmod_studio.hpp"
#include "../FMOD/api/core/inc/fmod.hpp"
#include "../FMOD/api/core/inc/fmod_errors.h"

#include <iostream>
#include <map>
#include <string>



namespace AudioMgr 
{
    //Error handling for FMOD errors
    void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line);
    #define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

    class SoundInfo 
    {

    public:
        SoundInfo(const char* fileName, const char* filePath);

        const char* getFileName();
        const char* getFilePath();
        float getVolume();

        bool isLoaded();
        bool isPlaying();
        bool isLoop();

        void setVol(float newVol);
        void setLoaded(bool load);
        void setPlaying(bool play);
        void setLoop(bool loop);
        

    private:
        const char* fileName;
        const char* filePath;
        float vol = 1.0f; //defaut volume

        bool loaded = false;
        bool playing = false;
        bool looping = false;

    };



	class Audio 
    {

	public:
        Audio();
        ~Audio();

        void init();
        void deactivate();
        void update();

        void loadSound(SoundInfo& soundInfo);
        void playSound(SoundInfo& soundInfo);
        void stopSound(SoundInfo& soundInfo);
        void updateVol(SoundInfo& soundInfo, float vol);

        // The audio sampling rate of the audio engine
        static const int AUDIO_SAMPLE_RATE = 44100;

    private:
        static const unsigned int MAX_AUDIO_CHANNELS = 1024;

        FMOD::Studio::System* studioSys = nullptr;
        FMOD::System* lowLevelSys = nullptr;

        FMOD::ChannelGroup* masterGroup = 0;

        std::map<std::string, FMOD::Sound*> sounds;
        std::map<std::string, FMOD::Channel*> loopsPlaying;
        std::map<std::string, FMOD::Studio::Bank*> soundBanks;

        bool muted = false;
 
	};

}