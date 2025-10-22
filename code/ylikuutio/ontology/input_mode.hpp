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

#ifndef YLIKUUTIO_INPUT_INPUT_MODE_HPP_INCLUDED
#define YLIKUUTIO_INPUT_INPUT_MODE_HPP_INCLUDED

#include "entity.hpp"
#include "input_mode_child_module.hpp"
#include "input_mode_apprentice_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class ParentOfInputModesModule;
    class GenericMasterModule;
    class Universe;
    class GenericCallbackEngine;
    struct InputModeStruct;

    template<typename Type>
        struct Request;

    class InputMode final : public Entity
    {
        private:
            InputMode(
                    yli::core::Application& application,
                    Universe& universe,
                    const InputModeStruct& input_mode_struct,
                    ParentOfInputModesModule* const parent_module,
                    GenericMasterModule* const console_master_module);

            ~InputMode() = default;

        public:
            void activate() override;
            void deactivate();

            GenericCallbackEngine* get_keypress_callback_engine(const uint32_t keycode) const;
            GenericCallbackEngine* get_keyrelease_callback_engine(const uint32_t keycode) const;
            GenericCallbackEngine* get_continuous_keypress_callback_engine(const uint32_t keycode) const;

            void set_keypress_callback_engine(const uint32_t keycode, const Request<GenericCallbackEngine>& callback_engine);
            void set_keyrelease_callback_engine(const uint32_t keycode, const Request<GenericCallbackEngine>& callback_engine);
            void set_continuous_keypress_callback_engine(const uint32_t keycode, const Request<GenericCallbackEngine>& callback_engine);

            const std::vector<GenericCallbackEngine*>* get_keypress_callback_engines() const;
            const std::vector<GenericCallbackEngine*>* get_keyrelease_callback_engines() const;
            const std::vector<GenericCallbackEngine*>* get_continuous_keypress_callback_engines() const;

            Entity* get_parent() const override;
            Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            InputModeChildModule child_of_universe;
            InputModeApprenticeModule apprentice_of_console;

        private:
            InputMode(const InputMode&) = delete;                           // Delete copy constructor.
            InputMode& operator=(const InputMode&) = delete; // Delete copy assignment.

            std::vector<GenericCallbackEngine*> keypress_callback_engines;
            std::vector<GenericCallbackEngine*> keyrelease_callback_engines;
            std::vector<GenericCallbackEngine*> continuous_keypress_callback_engines;
    };
}

#endif
