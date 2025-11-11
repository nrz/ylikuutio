// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_MASTER_OF_INPUT_MODES_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MASTER_OF_INPUT_MODES_MODULE_HPP_INCLUDED

#include "generic_master_module.hpp"

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    class Registry;
    class GenericMasterModule;
    class Entity;
    class InputMode;

    class MasterOfInputModesModule final : public GenericMasterModule
    {
        public:
            MasterOfInputModesModule(
                    Entity& generic_master,
                    Registry* const registry,
                    const std::string& name) noexcept;

            MasterOfInputModesModule(const MasterOfInputModesModule&) = delete;            // Delete copy constructor.
            MasterOfInputModesModule& operator=(const MasterOfInputModesModule&) = delete; // Delete copy assignment.

            ~MasterOfInputModesModule() = default;

            bool has_current_input_mode() const;
            void set_current_input_mode(InputMode* const input_mode);
            InputMode* get_current_input_mode() const;
            void activate_current_input_mode();
            void deactivate_current_input_mode();

        private:
            InputMode* current_input_mode { nullptr };
    };
}

#endif
