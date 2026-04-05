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
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

// Include standard headers
#include <iostream> // std::cerr
#include <list>     // std::list
#include <string>   // std::string

namespace yli::audio
{
    AudioSystem::AudioSystem(yli::ontology::Universe& universe)
        : universe { universe }
    {
        this->init();
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

    bool AudioSystem::init()
    {
        if (!MIX_Init())
        {
            std::cerr << "ERROR: `AudioSystem::init`: initializing SDL_mixer library failed!\n";
            yli::sdl::print_sdl_error();
            return false;
        }

        this->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

        if (this->mixer == nullptr)
        {
            std::cerr << "ERROR: `AudioSystem::init`: creating mixer failed!\n";
            yli::sdl::print_sdl_error();
            return false;
        }

        this->music_track = MIX_CreateTrack(this->mixer);

        if (this->music_track == nullptr)
        {
            std::cerr << "ERROR: `AudioSystem::init`: creating music track failed!\n";
            yli::sdl::print_sdl_error();
            return false;
        }

        return true;
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
            char* audio_file_path = nullptr;
            SDL_asprintf(&audio_file_path, "%s%s", SDL_GetBasePath(), audio_file.c_str());
            MIX_Audio* const audio = MIX_LoadAudio(this->mixer, audio_file_path, false);
            if (audio == nullptr)
            {
                std::cerr << "ERROR: `AudioSystem::load_and_play`: loading audio file " << std::string(audio_file_path) << " failed!\n";
                yli::sdl::print_sdl_error();
                return false;
            }

            SDL_free(audio_file_path);

            MIX_SetTrackAudio(this->music_track, audio);
            MIX_PlayTrack(this->music_track, 0); // Play the track!
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

            if (!MIX_TrackPlaying(this->music_track))
            {
                // Song ended.
                this->next_song_from_playlist();
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
