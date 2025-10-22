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

#ifndef YLIKUUTIO_SNIPPETS_CONSOLE_MODE_KEYBOARD_CALLBACK_CREATION_SNIPPETS_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_CONSOLE_MODE_KEYBOARD_CALLBACK_CREATION_SNIPPETS_HPP_INCLUDED

namespace yli::ontology
{
    class InputMode;
    class GenericEntityFactory;
}

namespace yli::snippets
{
    using yli::ontology::InputMode;
    using yli::ontology::GenericEntityFactory;

    void create_console_mode_keypress_callbacks(GenericEntityFactory& entity_factory);
    void create_console_mode_keyrelease_callbacks(GenericEntityFactory& entity_factory);
    void set_console_mode_keypress_callback_engines_or_throw(InputMode& console_mode_input_mode);
    void set_console_mode_keyrelease_callback_engines_or_throw(InputMode& console_mode_input_mode);
}

#endif

