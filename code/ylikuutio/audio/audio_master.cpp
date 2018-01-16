#include "audio_master.hpp"

#include <SFML/Audio.hpp>

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace ylikuutio
{
    namespace audio
    {
        AudioMaster::AudioMaster()
        {
            // constructor.
        }

        AudioMaster::~AudioMaster()
        {
            // destructor.
        }

        bool AudioMaster::load(std::string& audio_file)
        {
            if (this->sound_map.count(audio_file) == 1)
            {
                // There is already a sound with that filename. It's OK.
                return true;
            }

            // There's no sound with that filename loaded yet, so load it now.
            sf::SoundBuffer* soundbuffer_pointer = new sf::SoundBuffer();

            if (!soundbuffer_pointer->loadFromFile(audio_file))
            {
                // Loading the sound failed.
                delete soundbuffer_pointer;
                return false;
            }

            sf::Sound sound;
            sound.setBuffer(*soundbuffer_pointer);
            this->soundbuffer_pointer_map[audio_file] = soundbuffer_pointer;
            this->sound_map[audio_file] = sound;
            return true;
        }

        bool AudioMaster::load_and_play(std::string& audio_file)
        {
            if (this->load(audio_file))
            {
                if (this->sound_map.count(audio_file) == 1)
                {
                    this->sound_map[audio_file].play();
                    return true;
                }
            }

            return false;
        }

        void AudioMaster::unload(std::string& audio_file)
        {
            if (this->sound_map.count(audio_file) == 1)
            {
                this->sound_map.erase(audio_file);
                this->soundbuffer_pointer_map.erase(audio_file);
            }
        }
    }
}
