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

#include "input_mode.hpp"
#include "parent_of_input_modes_module.hpp"
#include "universe.hpp"
#include "input_mode_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class MasterOfInputModesModule;
    class CallbackEngine;
    class Scene;

    InputMode::InputMode(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::InputModeStruct& input_mode_struct,
            yli::ontology::ParentOfInputModesModule* const parent_module,
            yli::ontology::MasterOfInputModesModule* const console_master_module)
        : Entity(application, universe, input_mode_struct),
        child_of_universe(parent_module, this),
        apprentice_of_console(console_master_module, this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::InputMode*";
    }

    void InputMode::activate()
    {
        yli::ontology::Universe* const universe = static_cast<yli::ontology::Universe*>(this->child_of_universe.get_parent());

        [[unlikely]]
        if (universe == nullptr)
        {
            throw std::runtime_error("ERROR: `InputMode::activate`: `universe` is `nullptr`!");
        }

        universe->parent_of_input_modes.set_active_input_mode(this);
    }

    void InputMode::deactivate()
    {
        yli::ontology::Universe* const universe = static_cast<yli::ontology::Universe*>(this->child_of_universe.get_parent());

        if (universe == nullptr)
        {
            throw std::runtime_error("ERROR: `InputMode::deactivate`: `universe` is `nullptr`!");
        }

        // Only the active input mode may deactivate itself.

        if (universe->parent_of_input_modes.get_active_input_mode() == this)
        {
            universe->parent_of_input_modes.pop_input_mode();
        }
    }

    yli::ontology::CallbackEngine* InputMode::get_keypress_callback_engine(uint32_t keycode) const
    {
        if (keycode < this->keypress_callback_engines.size())
        {
            return this->keypress_callback_engines[keycode];
        }

        return nullptr;
    }

    yli::ontology::CallbackEngine* InputMode::get_keyrelease_callback_engine(uint32_t keycode) const
    {
        if (keycode < this->keyrelease_callback_engines.size())
        {
            return this->keyrelease_callback_engines[keycode];
        }

        return nullptr;
    }

    yli::ontology::CallbackEngine* InputMode::get_continuous_keypress_callback_engine(uint32_t keycode) const
    {
        if (keycode < this->continuous_keypress_callback_engines.size())
        {
            return this->continuous_keypress_callback_engines[keycode];
        }

        return nullptr;
    }

    void InputMode::set_keypress_callback_engine(uint32_t keycode, yli::ontology::CallbackEngine* callback_engine)
    {
        if (keycode >= this->keypress_callback_engines.size())
        {
            this->keypress_callback_engines.resize(keycode + 1, nullptr);
        }

        this->keypress_callback_engines[keycode] = callback_engine;
    }

    void InputMode::set_keyrelease_callback_engine(uint32_t keycode, yli::ontology::CallbackEngine* callback_engine)
    {
        if (keycode >= this->keyrelease_callback_engines.size())
        {
            this->keyrelease_callback_engines.resize(keycode + 1, nullptr);
        }

        this->keyrelease_callback_engines[keycode] = callback_engine;
    }

    void InputMode::set_continuous_keypress_callback_engine(uint32_t keycode, yli::ontology::CallbackEngine* callback_engine)
    {
        if (keycode >= this->continuous_keypress_callback_engines.size())
        {
            this->continuous_keypress_callback_engines.resize(keycode + 1, nullptr);
        }

        this->continuous_keypress_callback_engines[keycode] = callback_engine;
    }

    const std::vector<yli::ontology::CallbackEngine*>* InputMode::get_keypress_callback_engines() const
    {
        return &this->keypress_callback_engines;
    }

    const std::vector<yli::ontology::CallbackEngine*>* InputMode::get_keyrelease_callback_engines() const
    {
        return &this->keyrelease_callback_engines;
    }

    const std::vector<yli::ontology::CallbackEngine*>* InputMode::get_continuous_keypress_callback_engines() const
    {
        return &this->continuous_keypress_callback_engines;
    }

    yli::ontology::Entity* InputMode::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    yli::ontology::Scene* InputMode::get_scene() const
    {
        return nullptr;
    }

    std::size_t InputMode::get_number_of_children() const
    {
        return 0; // `InputMode` has no children.
    }

    std::size_t InputMode::get_number_of_descendants() const
    {
        return 0; // `InputMode` has no children.
    }
}