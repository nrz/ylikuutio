// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __YLIKUUTIO_AUDIO_AUDIO_MASTER_HPP_INCLUDED
#define __YLIKUUTIO_AUDIO_AUDIO_MASTER_HPP_INCLUDED

#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <list>          // std::list
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli::ontology
{
    class Universe;
}

namespace yli::audio
{
    class AudioMaster
    {
        public:
            // constructor.
            explicit AudioMaster(yli::ontology::Universe* const universe);

            AudioMaster(const AudioMaster&) = delete;            // Delete copy constructor.
            AudioMaster& operator=(const AudioMaster&) = delete; // Delete copy assignment.

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

            int get_remaining_length(); // This function is not `const` due to use of `SDL_AtomicGet`.

        private:
            void play_audio(void* userdata, uint8_t* stream, int length);
            static void play_audio_callback(void* userdata, uint8_t* stream, int length);
            static yli::audio::AudioMaster* audio_master;

            yli::ontology::Universe* const universe { nullptr };

            SDL_AudioSpec audio_spec;
            SDL_AudioDeviceID device;

            uint8_t* wav_pointer { nullptr };
            SDL_atomic_t remaining_length { 0 };

            std::unordered_map<std::string, uint8_t*> wav_buffer_pointer_map;     // filename is the key.
            std::unordered_map<std::string, std::list<std::string>> playlist_map; // key: name of playlist, value: list of filenames.
            std::string current_playlist;                                         // name of current playlist.
            std::list<std::string>::iterator current_playlist_sound_iterator;
            bool loop { false };
    };
}

#endif
