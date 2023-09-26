#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"

class AudioManager {
private:
    FMOD::System* system;                                              // FMOD System object
    std::unordered_map<std::string, FMOD::Sound*> soundMap;            // Map to store sounds by name
    FMOD::Channel* channel;                                            // Channel to play our sound
    FMOD::ChannelGroup* musicGroup;                                    // Group for music tracks
    FMOD::ChannelGroup* sfxGroup;                                      // Group for sound effects

public:
    AudioManager();
    ~AudioManager();

    void Update();                                                     // Update the FMOD system (usually called every frame)
    void LoadSound(const std::string& name, const char* filepath);     // Load a sound and associate it with a name
    void PlaySound(const std::string& name);                           // Play a previously loaded sound by its name
};
