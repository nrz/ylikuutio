#include <SFML/Audio.hpp>

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace ylikuutio
{
    namespace audio
    {
        class AudioMaster
        {
            public:
                // constructor.
                AudioMaster();

                // destructor.
                ~AudioMaster();

                bool load(std::string& audio_file);
                bool load_and_play(std::string& audio_file);
                void unload(std::string& audio_file);

            private:
                std::unordered_map<std::string, sf::Sound> sound_map;
                std::unordered_map<std::string, sf::SoundBuffer*> soundbuffer_pointer_map;
        };
    }
}
