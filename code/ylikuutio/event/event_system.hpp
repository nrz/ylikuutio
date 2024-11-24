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

#ifndef YLIKUUTIO_EVENT_EVENT_SYSTEM_HPP_INCLUDED
#define YLIKUUTIO_EVENT_EVENT_SYSTEM_HPP_INCLUDED

#include "code/ylikuutio/memory/constructible_module.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class InputMode;
}

namespace yli::event
{
    class EventSystem
    {
        public:
            explicit EventSystem(yli::ontology::Universe& universe);

            void poll_events(const yli::ontology::InputMode& input_mode);

            EventSystem& get();

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            yli::memory::ConstructibleModule constructible_module;

            yli::ontology::Universe& universe;
    };
}

#endif

