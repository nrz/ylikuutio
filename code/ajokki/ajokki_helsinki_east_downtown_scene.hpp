// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef AJOKKI_AJOKKI_HELSINKI_EAST_DOWNTOWN_SCENE_HPP_INCLUDED
#define AJOKKI_AJOKKI_HELSINKI_EAST_DOWNTOWN_SCENE_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Universe;
        class EntityFactory;
    }
}

namespace ajokki
{
    yli::ontology::Entity* create_helsinki_east_downtown_scene(
            yli::ontology::Universe& universe,
            yli::ontology::EntityFactory* const entity_factory);
}

#endif
