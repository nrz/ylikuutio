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

#ifndef YLIKUUTIO_INPUT_INPUT_MODE_APPRENTICE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_INPUT_INPUT_MODE_APPRENTICE_MODULE_HPP_INCLUDED

#include "apprentice_module.hpp"

namespace yli::ontology
{
    class MasterOfInputModesModule;
    class Entity;

    class InputModeApprenticeModule final : public yli::ontology::ApprenticeModule
    {
        public:
            InputModeApprenticeModule(
                    yli::ontology::MasterOfInputModesModule* const master_of_input_modes_module,
                    yli::ontology::Entity* const apprentice);
    };
}

#endif
