#include "audio_master.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

// Include standard headers
#include <list>          // std::list
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace audio
    {
        AudioMaster::AudioMaster()
        {
            // constructor.

            this->current_playlist = ""; // no current playlist.
            this->current_sound = "";    // no current sound.
            this->loop = true;           // loop playlist.
        }

        AudioMaster::~AudioMaster()
        {
            // destructor.
        }

        bool AudioMaster::load(const std::string& audio_file)
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

        bool AudioMaster::load_and_play(const std::string& audio_file)
        {
            if (this->load(audio_file))
            {
                if (this->sound_map.count(audio_file) == 1)
                {
                    this->sound_map[audio_file].play();
                    this->current_sound = audio_file;
                    return true;
                }
            }

            return false;
        }

        void AudioMaster::unload(const std::string& audio_file)
        {
            if (this->sound_map.count(audio_file) == 1)
            {
                if (this->current_sound.compare(audio_file) == 0)
                {
                    // The sound to be unloaded may be currently in play.
                    if (this->sound_map.count(audio_file) == 1)
                    {
                        // Stop the sound before unloading it.
                        this->sound_map[audio_file].stop();
                    }
                }

                this->sound_map.erase(audio_file);
                this->soundbuffer_pointer_map.erase(audio_file);
            }
        }

        void AudioMaster::add_to_playlist(const std::string& playlist, const std::string& audio_file)
        {
            // Playlist must have a name. Empty string is not accepted.
            if (!playlist.empty() && this->playlist_map.count(playlist) == 0)
            {
                this->playlist_map[playlist] = std::list<std::string>();
            }

            this->playlist_map[playlist].push_back(audio_file);
        }

        void AudioMaster::remove_from_playlist(const std::string& playlist, const std::string& audio_file)
        {
            if (this->playlist_map.count(playlist) == 1)
            {
                for (auto it = this->playlist_map[playlist].begin(); it != this->playlist_map[playlist].end(); it++)
                {
                    if (it->compare(audio_file) == 0)
                    {
                        this->playlist_map[playlist].erase(it);
                    }
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
            // This function checks if a playlist is running,
            // if yes, then if the the previous sound has ended, starts the next one.

            if (this->current_playlist.size() > 0)
            {
                if (this->sound_map.count(*this->current_playlist_sound_iterator) == 1)
                {
                    // OK, there is a sound which might be playing, so let's check its status.
                    sf::SoundSource::Status status = this->sound_map[*this->current_playlist_sound_iterator].getStatus();

                    if (status == sf::SoundSource::Stopped)
                    {
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
                                this->current_sound = "";    // no current sound.
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
    }
}
