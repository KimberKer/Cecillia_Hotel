#include "duckpch.h"
#include "AudioManager.h"

AudioManager::AudioManager()
    : system(nullptr), channel(nullptr), musicGroup(nullptr), sfxGroup(nullptr) {
    FMOD::System_Create(&system);               // Create the main system object
    system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD

    system->createChannelGroup("Music", &musicGroup);
    system->createChannelGroup("SFX", &sfxGroup);
}

AudioManager::~AudioManager() {
    for (auto& pair : soundMap) {
        pair.second->release();
    }
    system->close();
    system->release();
}

void AudioManager::Update() {
    system->update();
}

void AudioManager::LoadSound(const std::string& name, const char* filepath) {
    FMOD::Sound* sound;
    system->createSound(filepath, FMOD_DEFAULT, 0, &sound);
    soundMap[name] = sound;
}

void AudioManager::PlaySound(const std::string& name) {
    auto it = soundMap.find(name);
    if (it != soundMap.end()) {
        system->playSound(it->second, nullptr, false, &channel);
        channel->setChannelGroup(musicGroup);  // Example, you can choose sfxGroup or others depending on your design
    }
}
