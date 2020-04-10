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

#ifndef __ANGELSCRIPT_MASTER_HPP_INCLUDED
#define __ANGELSCRIPT_MASTER_HPP_INCLUDED

#include "angelscript.h"

#include "angelscript.h"
#include "scriptstdstring/scriptstdstring.h"
#include "scriptbuilder/scriptbuilder.h"

// Include standard headers
#include <string> // std::string

namespace yli
{
    namespace angelscript
    {
        class AngelscriptMaster
        {
            public:
                // constructor.
                AngelscriptMaster();

                AngelscriptMaster(const AngelscriptMaster&) = delete;            // Delete copy constructor.
                AngelscriptMaster &operator=(const AngelscriptMaster&) = delete; // Delete copy assignment.

                // destructor.
                ~AngelscriptMaster();

                std::string eval_string(const std::string& my_string);

            private:
                asIScriptEngine* angelscript_engine;

                std::string eval_output;

                float square(const float x);
                float cube(const float x);
                void print(const std::string& my_message);
                void print(const float value);
        };
    }
}

#endif
