// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_AUDIO_AUDIO_SYSTEM_HPP_INCLUDED
#define YLIKUUTIO_AUDIO_AUDIO_SYSTEM_HPP_INCLUDED

#include "code/ylikuutio/memory/constructible_module.hpp"

#include "soloud.h"
#include "soloud_wavstream.h"

// Include standard headers
#include <cstddef>       // std::size_t
#include <list>          // std::list
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
}

namespace yli::audio
{
    class AudioSystem final
    {
        public:
            explicit AudioSystem(yli::ontology::Universe& universe);

            AudioSystem(const AudioSystem&) = delete;            // Delete copy constructor.
            AudioSystem& operator=(const AudioSystem&) = delete; // Delete copy assignment.

            ~AudioSystem();

            void terminate();

            bool load_and_play(const std::string& audio_file);
            void add_to_playlist(const std::string& playlist, const std::string& audio_file);
            void remove_from_playlist(const std::string& playlist, const std::string& audio_file);
            void play_playlist(const std::string& playlist);
            void update();
            void pause();
            void continue_after_pause();
            void clear_playlist(const std::string& playlist);
            void erase_playlist(const std::string& playlist);

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            yli::memory::ConstructibleModule constructible_module;

            yli::ontology::Universe& universe;

            SoLoud::Soloud soloud;        // SoLoud engine.
            SoLoud::WavStream wav_stream; // Audio stream (from a file).

            int sound_handle { 0 };

            std::unordered_map<std::string, std::list<std::string>> playlist_map; // key: name of playlist, value: list of filenames.
            std::string current_playlist;                                         // name of current playlist.
            std::list<std::string>::iterator current_playlist_sound_iterator;
            bool loop { false };
    };
}

#endif
