//---------------------------------------------------------
// File:		Audio.h
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This header file defines the classes aand functions
//              related to the audio engine.
//
// Copyright © 2023 DigiPen, All rights reserved.
//-------------------------------------------------------

#pragma once

#include "../FMOD/api/studio/inc/fmod_studio.hpp"
#include "../FMOD/api/core/inc/fmod.hpp"
#include "../FMOD/api/core/inc/fmod_errors.h"

#include "../ECS/Entity.h"
#include "AudioComponent.h"

#include <iostream>
#include <map>
#include <string>



namespace Duck 
{
    class AudioComponent;

    //Error handling for FMOD errors
    void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line);
    #define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

	class AudioSystem : public System
    {
	public:
        AudioSystem();
        ~AudioSystem();

        void init();
        void deactivate();
        void update();

        void loadSound(std::shared_ptr<AudioComponent> soundInfo);
        void playSound(std::shared_ptr<AudioComponent> soundInfo);
        void stopSound(std::shared_ptr<AudioComponent> soundInfo);
        void updateVol(std::shared_ptr< AudioComponent> soundInfo, float vol);

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