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

#include "gtest/gtest.h"
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/audio_track.hpp"
#include "code/ylikuutio/ontology/audio_track_struct.hpp"

TEST(audio_tracks_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::AudioTrackStruct audio_track_struct("419588__greek555__dreaming-of-me.ogg");
    audio_track_struct.global_name = "dreaming_of_me";
    yli::ontology::AudioTrack* const audio_track = application.get_generic_entity_factory().create_audio_track(
            audio_track_struct);
    ASSERT_NE(audio_track, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(audio_track) % alignof(yli::ontology::AudioTrack), 0);

    // `Entity` member functions.
    ASSERT_EQ(audio_track->get_childID(), 0);
    ASSERT_EQ(audio_track->get_type(), "yli::ontology::AudioTrack*");
    ASSERT_TRUE(audio_track->get_can_be_erased());
    ASSERT_EQ(audio_track->get_scene(), nullptr);
    ASSERT_EQ(audio_track->get_parent(), &application.get_universe());
    ASSERT_EQ(audio_track->get_number_of_non_variable_children(), 0);
}
