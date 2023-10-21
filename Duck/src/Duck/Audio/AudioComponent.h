#pragma once

#include "Duck/Audio/Audio.h"

namespace Duck
{

    class AudioComponent
    {

    public:
        AudioComponent() = default;
        AudioComponent(const std::string& name, const std::string& path) :
            filename(name), filepath(path) {}

        const std::string& getFileName() { return filename; }
        const std::string& getFilePath() { return filepath; }
        float getVolume() { return vol; }

        bool isLoaded() { return loaded; }
        bool isPlaying() { return playing; }
        bool isLoop() { return looping; }

        void setVol(float newVol) { vol = newVol; }
        void setLoaded(bool load) { loaded = load; }
        void setPlaying(bool play) { playing = play; }
        void setLoop(bool loop) { looping = loop; }

        std::shared_ptr<AudioComponent> getSound() { return sound; }
        void setSound(std::shared_ptr<AudioComponent> newSound) { sound = newSound; }


    private:
        std::shared_ptr<AudioComponent> sound = nullptr;

        std::string filename;
        std::string filepath;
        float vol = 1.0f; //default volume

        bool loaded = false;
        bool playing = true;
        bool looping = false;

    };

}