// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "input_mode_apprentice_module.hpp"
#include "master_of_input_modes_module.hpp"
#include "input_mode.hpp"
#include "console.hpp"

// Include standard headers
#include <stdexcept> // std::runtime_error

namespace yli::ontology
{
    class Entity;

    InputModeApprenticeModule::InputModeApprenticeModule(
            yli::ontology::MasterOfInputModesModule* const master_of_input_modes_module,
            yli::ontology::Entity* const apprentice)
        : ApprenticeModule(master_of_input_modes_module, apprentice)
    {
        if (master_of_input_modes_module != nullptr)
        {
            // Make the `InputMode` of this `InputModeApprenticeModule`
            // the input mode of the `Console`.
            yli::ontology::Console* const console = static_cast<yli::ontology::Console*>(
                    master_of_input_modes_module->get_generic_master());

            [[unlikely]]
            if (console == nullptr)
            {
                throw std::runtime_error("ERROR: `InputModeApprenticeModule::InputModeApprenticeModule`: `console` is `nullptr`!");
            }

            console->set_input_mode(static_cast<yli::ontology::InputMode*>(this->get_apprentice()));
        }
    }
}
