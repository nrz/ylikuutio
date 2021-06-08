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

#ifndef __GPGPU_TEST_GPGPU_TEST_SCENE_HPP_INCLUDED
#define __GPGPU_TEST_GPGPU_TEST_SCENE_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class Entity;
        class EntityFactory;
    }
}

namespace gpgpu_test
{
    yli::ontology::Entity* create_gpgpu_test_scene(yli::ontology::EntityFactory* const entity_factory);
}

#endif
