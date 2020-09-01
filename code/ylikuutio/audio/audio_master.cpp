// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "audio_master.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

#include "SDL.h"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <list>          // std::list
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli::audio
{
    yli::audio::AudioMaster* AudioMaster::audio_master;

    AudioMaster::AudioMaster(yli::ontology::Universe* const universe)
    {
        // constructor.
        this->universe = universe;

        this->wav_pointer = nullptr;
        SDL_AtomicSet(&this->remaining_length, 0);

        this->current_playlist = ""; // no current playlist.
        this->loop = true;           // loop playlist.

        this->audio_spec.freq = 44100; // 44100 Hz.
        this->audio_spec.format = AUDIO_F32;
        this->audio_spec.channels = 2;
        this->audio_spec.silence = 0;        // dummy value.
        this->audio_spec.padding = 0;        // dummy value.
        this->audio_spec.samples = 4096;
        this->audio_spec.size = 0;           // dummy value.
        this->audio_spec.callback = yli::audio::AudioMaster::play_audio_callback;
        this->audio_spec.userdata = nullptr; // this is a pointer that is passed to the callback.

        // initialize `device` member variable.
        SDL_AudioSpec wav_spec = SDL_AudioSpec();
        this->device = SDL_OpenAudioDevice(nullptr, 0, &wav_spec, &this->audio_spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
        SDL_PauseAudioDevice(this->device, 1); // stop playing.

        this->audio_master = this;   // `this` is the `AudioMaster`. Do not create more than 1 `AudioMaster`!
    }

    AudioMaster::~AudioMaster()
    {
        // destructor.

        if (this->universe != nullptr && !this->universe->get_is_headless())
        {
            SDL_CloseAudioDevice(this->device);
        }
    }

    bool AudioMaster::load_and_play(const std::string& audio_file)
    {
        if (this->wav_buffer_pointer_map.count(audio_file) == 1)
        {
            // There is already a sound with that filename. It's not OK.
            return false;
        }

        // There's no sound with that filename loaded yet, so load it now.
        if (this->universe != nullptr && !this->universe->get_is_headless())
        {
            SDL_AudioSpec wav_spec = SDL_AudioSpec();
            uint32_t wav_length;
            uint8_t* wav_buffer;

            if (SDL_LoadWAV(audio_file.c_str(), &wav_spec, &wav_buffer, &wav_length) == nullptr)
            {
                // Loading the sound failed.
                std::cerr << "Loading WAV file " << audio_file << " failed.\n";
                return false;
            }

            // https://wiki.libsdl.org/SDL_OpenAudioDevice
            wav_spec.channels = 2;
            wav_spec.samples = 4096;
            wav_spec.callback = yli::audio::AudioMaster::play_audio_callback;

            this->device = SDL_OpenAudioDevice(nullptr, 0, &wav_spec, &this->audio_spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

            if (this->device == 0)
            {
                SDL_Log("Failed to open audio: %s", SDL_GetError());
            }
            else
            {
                if (this->audio_spec.format != wav_spec.format)
                {
                    SDL_Log("Float32 audio format was not available.");
                }
            }

            this->wav_pointer = wav_buffer;
            SDL_AtomicSet(&this->remaining_length, wav_length);
            this->wav_buffer_pointer_map[audio_file] = wav_buffer;
            SDL_PauseAudioDevice(this->device, 0); // start playing.
        }

        return true;
    }

    void AudioMaster::unload(const std::string& audio_file)
    {
        if (this->universe != nullptr && !this->universe->get_is_headless())
        {
            if (this->wav_buffer_pointer_map.count(audio_file) == 1)
            {
                if (*current_playlist_sound_iterator == audio_file)
                {
                    // Stop the sound before unloading it.
                    SDL_PauseAudioDevice(this->device, 1); // stop playing.
                }

                SDL_FreeWAV(this->wav_buffer_pointer_map[audio_file]);
                this->wav_buffer_pointer_map.erase(audio_file);
            }
        }
    }

    void AudioMaster::add_to_playlist(const std::string& playlist, const std::string& audio_file)
    {
        // Playlist must have a name. Empty string is not accepted.
        if (!playlist.empty() && this->playlist_map.count(playlist) == 0)
        {
            this->playlist_map[playlist] = std::list<std::string>();
        }

        this->playlist_map[playlist].emplace_back(audio_file);
    }

    void AudioMaster::remove_from_playlist(const std::string& playlist, const std::string& audio_file)
    {
        if (this->playlist_map.count(playlist) == 1)
        {
            for (auto it = this->playlist_map[playlist].begin(); it != this->playlist_map[playlist].end(); )
            {
                if (it->compare(audio_file) == 0)
                {
                    this->playlist_map[playlist].erase(it--);
                }

                it++;
            }
        }
    }

    void AudioMaster::play_playlist(const std::string& playlist)
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

    void AudioMaster::update()
    {
        if (this->universe != nullptr && !this->universe->get_is_headless())
        {
            // This function checks if a playlist is running.
            // if yes, then if the the previous sound has ended,
            // its memory gets freed and a new sound gets started.
            if (this->current_playlist.size() > 0)
            {
                if (this->wav_buffer_pointer_map.count(*this->current_playlist_sound_iterator) == 1)
                {
                    // OK, there is a sound which might be playing, so let's check its status.
                    const int remaining_length = this->get_remaining_length();

                    if (remaining_length == 0)
                    {
                        SDL_PauseAudioDevice(this->device, 1); // stop playing.
                        this->unload(*this->current_playlist_sound_iterator);

                        // play the next sound.

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
                }
            }
        }
    }

    void AudioMaster::pause()
    {
        // TODO: implement pause!
    }

    void AudioMaster::continue_after_pause()
    {
        // TODO: implement continue after pause!
    }

    void AudioMaster::clear_playlist(const std::string& playlist)
    {
        // TODO: implement clear playlist!
    }

    void AudioMaster::erase_playlist(const std::string& playlist)
    {
        // TODO: implement erase playlist!
    }

    int AudioMaster::get_remaining_length()
    {
        // This function is not `const` due to use of `SDL_AtomicGet`.
        return SDL_AtomicGet(&this->remaining_length);
    }

    void AudioMaster::play_audio(void* userdata, uint8_t* stream, int length)
    {
        if (this->universe != nullptr && !this->universe->get_is_headless())
        {
            // TODO: mix audio with `SDL_MixAudioFormat`!
            // https://wiki.libsdl.org/SDL_MixAudioFormat
            int remaining_length = this->get_remaining_length();

            if (remaining_length == 0)
            {
                // there's nothing to play.
                return;
            }

            if (length > remaining_length)
            {
                length = remaining_length;
            }

            SDL_memset(stream, 0, length);
            SDL_MixAudioFormat(stream, this->wav_pointer, AUDIO_F32, length, SDL_MIX_MAXVOLUME);
            this->wav_pointer += length;

            remaining_length -= length;
            SDL_AtomicSet(&this->remaining_length, remaining_length);
        }
    }

    void AudioMaster::play_audio_callback(void* userdata, uint8_t* stream, int length)
    {
        yli::audio::AudioMaster* audio_master = yli::audio::AudioMaster::audio_master;
        audio_master->play_audio(userdata, stream, length);
    }
}
