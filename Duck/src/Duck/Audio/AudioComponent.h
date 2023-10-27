#pragma once

#include "Duck/Audio/Audio.h"

namespace Duck
{

    class AudioComponent
    {

    public:
        AudioComponent() = default;
        AudioComponent(const std::string& name, const std::string& path, bool play = false, float vol = 1.0) :
            filename(name), filepath(path), playing(play), volume(vol) {}

        const std::string& getFileName() { return filename; }
        const std::string& getFilePath() { return filepath; }
        float getVolume() { return volume; }

        bool isLoaded() { return loaded; }
        bool isPlaying() { return playing; }
        bool isLoop() { return looping; }

        void setVol(float newVol) { volume = newVol; }
        void setLoaded(bool load) { loaded = load; }
        void setPlaying(bool play) { playing = play; }
        void setLoop(bool loop) { looping = loop; }

        std::shared_ptr<AudioComponent> getSound() { return sound; }
        void setSound(std::shared_ptr<AudioComponent> newSound) { sound = newSound; }


    private:
        std::shared_ptr<AudioComponent> sound = nullptr;

        std::string filename;
        std::string filepath;
        float volume = 1.0f; //default volume

        bool loaded = false;
        bool playing = true;
        bool looping = false;

    };

}