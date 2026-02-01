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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "hirvi_edit.hpp"
#include "core/hirvi_core.hpp"
#include "data/datatype.hpp"
#include "lisp/hirvi_edit_console_callbacks.hpp"
#include "code/ylikuutio/audio/audio_system.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/input/input_system.hpp"

#ifndef GOOGLE_TEST
// Google Test provides its own `main` entrypoint.
#include "code/ylikuutio/core/entrypoint.hpp"
#endif

#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cerr
#include <memory>   // std::make_unique, std::unique_ptr
#include <stdexcept> // std::logic_error
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::event
{
    class EventSystem;
}

namespace yli::memory
{
    class GenericMemorySystem;
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class GenericEntityFactory;
}

namespace hirvi
{
    using namespace yli::console;
    using namespace yli::ontology;

    HirviEditApplication::HirviEditApplication(const int argc, const char* const argv[])
        : yli::core::Application(argc, argv),
        core(*this, this->get_universe_struct())
    {
        std::cout << "HirviEditApplication initialized!\n";
    }

    std::string HirviEditApplication::get_name() const
    {
        return "HirviEdit";
    }

    std::vector<std::string> HirviEditApplication::get_valid_keys() const
    {
        return {
            "help",
                "version",
                "silent",
                "fullscreen",
                "no-fullscreen",
                "headless",
                "window-width",
                "window-height",
                "framebuffer-width",
                "framebuffer-height",
                "speed",
                "turbo-factor",
                "twin-turbo-factor",
                "mouse-speed"
        };
    }

    yli::memory::GenericMemorySystem& HirviEditApplication::get_generic_memory_system() const
    {
        return this->core.memory_system.get();
    }

    yli::memory::MemorySystem<hirvi::Datatype>& HirviEditApplication::get_memory_system() const
    {
        return this->core.memory_system.get();
    }

    yli::memory::GenericMemoryAllocator& HirviEditApplication::get_generic_memory_allocator(const int type) const
    {
        return this->core.memory_system.get_generic_allocator(type);
    }

    GenericEntityFactory& HirviEditApplication::get_generic_entity_factory() const
    {
        return this->core.entity_factory.get();
    }

    yli::event::EventSystem* HirviEditApplication::get_event_system() const
    {
        return this->core.event_system;
    }

    yli::input::InputSystem* HirviEditApplication::get_input_system() const
    {
        return this->core.input_system;
    }

    yli::audio::AudioSystem* HirviEditApplication::get_audio_system() const
    {
        return this->core.audio_system;
    }

    bool HirviEditApplication::is_universe(Entity* entity) const
    {
        return static_cast<Entity*>(this->core.universe) == entity;
    }

    Universe& HirviEditApplication::get_universe() const
    {
        if (this->core.universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `HirviEditApplication::get_universe`: `this->core.universe` is `nullptr`!");
        }

        return *this->core.universe;
    }

    UniverseStruct HirviEditApplication::get_universe_struct() const
    {
        UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
        universe_struct.application_name = "HirviEdit";
        universe_struct.window_title = "Hirvi " + Universe::version + ", powered by Ylikuutio " + Universe::version;
        universe_struct.window_width = 3840;
        universe_struct.window_height = 2400;
        universe_struct.is_fullscreen = true;

        if (this->command_line_master.is_key("silent"))
        {
            universe_struct.is_silent = true;
        }

        if (this->command_line_master.is_key("fullscreen"))
        {
            universe_struct.is_fullscreen = true;
        }

        if (this->command_line_master.is_key("no-fullscreen"))
        {
            universe_struct.is_fullscreen = false;
        }

        if (this->command_line_master.is_key("headless"))
        {
            universe_struct.graphics_api_backend = yli::render::GraphicsApiBackend::HEADLESS;
        }

        if (this->command_line_master.is_key("window-width") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("window-width")))
        {
            universe_struct.window_width = this->command_line_master.get_value_or_throw<uint32_t>("window-width");
        }

        if (this->command_line_master.is_key("window-height") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("window-height")))
        {
            universe_struct.window_height = this->command_line_master.get_value_or_throw<uint32_t>("window-height");
        }

        if (this->command_line_master.is_key("framebuffer-width") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("framebuffer-width")))
        {
            universe_struct.framebuffer_module_struct.texture_width = this->command_line_master.get_value_or_throw<uint32_t>("framebuffer-width");
        }

        if (this->command_line_master.is_key("framebuffer-height") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("framebuffer-height")))
        {
            universe_struct.framebuffer_module_struct.texture_height = this->command_line_master.get_value_or_throw<uint32_t>("framebuffer-height");
        }

        if (this->command_line_master.is_key("speed") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("speed")))
        {
            universe_struct.speed = this->command_line_master.get_value_or_throw<float>("speed");
        }

        if (this->command_line_master.is_key("turbo-factor") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("turbo-factor")))
        {
            universe_struct.turbo_factor = this->command_line_master.get_value_or_throw<float>("turbo-factor");
        }

        if (this->command_line_master.is_key("twin-turbo_factor") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("twin-turbo-factor")))
        {
            universe_struct.twin_turbo_factor = this->command_line_master.get_value_or_throw<float>("twin-turbo-factor");
        }

        if (this->command_line_master.is_key("mouse-speed") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("mouse-speed")))
        {
            universe_struct.mouse_speed = this->command_line_master.get_value_or_throw<float>("mouse-speed");
        }

        return universe_struct;
    }

    bool HirviEditApplication::create_and_start_simulation()
    {
        return this->core.create_and_start_simulation(&HirviEditApplication::customize);
    }

    void HirviEditApplication::customize(HirviCore& hirvi_core)
    {
        hirvi_core.entity_factory.create_lisp_function_overload("version", Request<Console>("my_console"), &hirvi_edit::version);
    }
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[])
    {
        return std::make_unique<hirvi::HirviEditApplication>(argc, argv);
    }
}
