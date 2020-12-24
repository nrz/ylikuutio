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

#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <vector> // std::vector

namespace yli::ontology
{
    class Entity;
    class Scene;
    class Font2D;
    class Console;
}

namespace yli::render
{
    struct RenderStruct
    {
        yli::ontology::Scene* scene { nullptr };
        yli::ontology::Console* console { nullptr };
        std::vector<yli::ontology::Entity*>* font2D_pointer_vector { nullptr };
        SDL_Window* window { nullptr };
        bool should_ylikuutio_change_depth_test { true };
    };
}
