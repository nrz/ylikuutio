#ifndef __AUDIO_MASTER_HPP_INCLUDED
#define __AUDIO_MASTER_HPP_INCLUDED

#include "SDL.h"

// Include standard headers
#include <list>          // std::list
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli
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

                int get_remaining_length();

            private:
                void play_audio(void* userdata, uint8_t* stream, int length);
                static void play_audio_callback(void* userdata, uint8_t* stream, int length);
                static yli::audio::AudioMaster* audio_master;

                SDL_AudioSpec audio_spec;
                SDL_AudioDeviceID device;

                uint8_t* wav_pointer;
                SDL_atomic_t remaining_length;

                std::unordered_map<std::string, uint8_t*> wav_buffer_pointer_map;     // filename is the key.
                std::unordered_map<std::string, std::list<std::string>> playlist_map; // key: name of playlist, value: list of filenames.
                std::string current_playlist;                                         // name of current playlist.
                std::list<std::string>::iterator current_playlist_sound_iterator;
                bool loop;
        };
    }
}

#endif
