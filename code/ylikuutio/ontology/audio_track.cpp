// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "audio_track.hpp"
#include "universe.hpp"
#include "audio_track_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Scene;

    const std::string& AudioTrack::get_filename() const
    {
        return this->filename;
    }

    yli::ontology::Entity* AudioTrack::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    AudioTrack::AudioTrack(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::AudioTrackStruct& audio_track_struct,
            yli::ontology::GenericParentModule* const universe_parent_module)
        : Entity(application, universe, audio_track_struct),
        child_of_universe(universe_parent_module, *this),
        filename { audio_track_struct.filename }
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::AudioTrack*";
        this->can_be_erased = true;
    }

    std::size_t AudioTrack::get_number_of_children() const
    {
        return 0; // `AudioTrack` has no children.
    }

    std::size_t AudioTrack::get_number_of_descendants() const
    {
        return 0; // `AudioTrack` has no children.
    }

    yli::ontology::Scene* AudioTrack::get_scene() const
    {
        // `AudioTrack` does not belong in any `Scene`.
        return nullptr;
    }
}
