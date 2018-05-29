#ifndef __AUDIO_MASTER_HPP_INCLUDED
#define __AUDIO_MASTER_HPP_INCLUDED

#include <SFML/Audio.hpp>

// Include standard headers
#include <list>          // std::list
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

                bool load(const std::string& audio_file);
                bool load_and_play(const std::string& audio_file);
                void unload(const std::string& audio_file);
                void add_to_playlist(const std::string& playlist, const std::string& audio_file);
                void remove_from_playlist(const std::string& playlist, const std::string& audio_file);
                void play_playlist(const std::string& playlist);
                void update();
                void pause();
                void continue_after_pause();
                void clear_playlist(const std::string& playlist);
                void erase_playlist(const std::string& playlist);

            private:
                std::unordered_map<std::string, sf::Sound> sound_map;
                std::unordered_map<std::string, sf::SoundBuffer*> soundbuffer_pointer_map;
                std::unordered_map<std::string, std::list<std::string>> playlist_map;
                std::string current_playlist;
                std::string current_sound;
                std::list<std::string>::iterator current_playlist_sound_iterator;
                bool loop;
        };
    }
}

#endif
