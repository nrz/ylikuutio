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

#include "audio_system.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

#include <SDL3/SDL.h>

// Include standard headers
#include <iostream> // std::cerr
#include <list>     // std::list
#include <string>   // std::string

namespace yli::audio
{
    AudioSystem::AudioSystem(yli::ontology::Universe& universe)
        : universe { universe }
    {
        this->current_playlist = ""; // no current playlist.
        this->loop = true;           // loop playlist.
    }

    AudioSystem::~AudioSystem()
    {
        this->terminate();

        if (!this->universe.get_is_silent())
        {
            // TODO: Deinit if needed!
        }
    }

    void AudioSystem::terminate()
    {
        this->constructible_module.alive = false;
    }

    bool AudioSystem::load_and_play(const std::string& audio_file)
    {
        // There's no sound with that filename loaded yet, so load it now.
        if (!this->universe.get_is_silent())
        {
            char* wav_path = nullptr;
            SDL_asprintf(&wav_path, "%s%s", SDL_GetBasePath(), audio_file.c_str());
            if (!SDL_LoadWAV(wav_path, &this->spec, &this->wav_data, &this->wav_data_len))
            {
                std::cerr << "ERROR: `AudioSystem::load_and_play`: loading WAV file " << std::string(wav_path) << " failed!\n";
                return false;
            }

            this->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &this->spec, nullptr, nullptr);
            if (this->stream == nullptr)
            {
                std::cerr << "ERROR: `AudioSystem::load_and_play`: creating audio stream for file " << std::string(wav_path) << " failed!\n";
                return false;
            }

            // Start playing the stream.
            SDL_ResumeAudioStreamDevice(this->stream);
        }

        return true;
    }

    void AudioSystem::add_to_playlist(const std::string& playlist, const std::string& audio_file)
    {
        // Playlist must have a name. Empty string is not accepted.
        if (!playlist.empty() && this->playlist_map.count(playlist) == 0)
        {
            this->playlist_map[playlist] = std::list<std::string>();
        }

        this->playlist_map[playlist].emplace_back(audio_file);
    }

    void AudioSystem::remove_from_playlist(const std::string& playlist, const std::string& audio_file)
    {
        if (this->playlist_map.count(playlist) == 1)
        {
            for (auto it = this->playlist_map[playlist].begin(); it != this->playlist_map[playlist].end(); )
            {
                if (it->compare(audio_file) == 0)
                {
                    this->playlist_map[playlist].erase(it--);
                }

                ++it;
            }
        }
    }

    void AudioSystem::play_playlist(const std::string& playlist)
    {
        // This function starts playing the playlist "from the top".
        // Playlist must have a name. Empty string is not accepted.
        if (!playlist.empty() && this->playlist_map.count(playlist) == 1 && this->playlist_map.size() > 0)
        {
            this->current_playlist = playlist;
            this->current_playlist_sound_iterator = this->playlist_map[playlist].begin();
            this->load_and_play(*this->current_playlist_sound_iterator);
        }
    }

    void AudioSystem::update()
    {
        if (!this->universe.get_is_silent() && this->current_playlist.size() > 0)
        {
            // This function checks if a playlist is running.
            // if yes, then if the the previous sound has ended,
            // its memory gets freed and a new sound gets started.

            const int bytes_queued = SDL_GetAudioStreamQueued(this->stream);

            if (bytes_queued == 0 && this->bytes_put == this->wav_data_len) [[unlikely]]
            {
                // Song ended.
                SDL_FlushAudioStream(this->stream);
                SDL_ClearAudioStream(this->stream);
                this->bytes_put = 0;

                // Release memory.
                SDL_free(this->wav_data);

                this->next_song_from_playlist();
            }
            else if (bytes_queued == -1) [[unlikely]]
            {
                // ERROR!
                // TODO: log the error!
            }
            else if (bytes_queued < static_cast<int>(this->wav_data_len))
            {
                // Feed more data to the stream.
                SDL_PutAudioStreamData(this->stream, this->wav_data, this->wav_data_len - this->bytes_put);
                this->bytes_put = this->wav_data_len;
            }
        }
    }

    void AudioSystem::next_song_from_playlist()
    {
        // Next song from the playlist.

        if (++this->current_playlist_sound_iterator != this->playlist_map[this->current_playlist].end())
        {
            // Next sound.
            this->load_and_play(*this->current_playlist_sound_iterator);
        }
        else
        {
            // The previous sound was the last sound.
            if (this->loop)
            {
                // Start from the first.
                this->current_playlist_sound_iterator = this->playlist_map[this->current_playlist].begin();
                this->load_and_play(*this->current_playlist_sound_iterator);
            }
            else
            {
                this->current_playlist = ""; // no current playlist.
            }
        }
    }

    void AudioSystem::pause()
    {
        // TODO: implement pause!
    }

    void AudioSystem::continue_after_pause()
    {
        // TODO: implement continue after pause!
    }

    void AudioSystem::clear_playlist(const std::string& /* playlist */)
    {
        // TODO: implement clear playlist!
    }

    void AudioSystem::erase_playlist(const std::string& /* playlist */)
    {
        // TODO: implement erase playlist!
    }
}
