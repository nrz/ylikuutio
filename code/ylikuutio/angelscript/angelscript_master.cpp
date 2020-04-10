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

#include "angelscript_master.hpp"
#include "angelscript_callbacks.hpp"

#include "angelscript.h"
#include "scriptstdstring/scriptstdstring.h"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli
{
    namespace angelscript
    {
        AngelscriptMaster::AngelscriptMaster()
        {
            // constructor.
            this->angelscript_engine = asCreateScriptEngine();

            if (angelscript_engine == nullptr)
            {
                std::cerr << "ERROR: `angelscript_engine` is `nullptr`!\n";
                return;
            }

            int result = angelscript_engine->SetMessageCallback(asFUNCTION(yli::angelscript::message_callback), 0, asCALL_CDECL);

            if (result < 0)
            {
                std::cerr << "Setting message callback failed!\n";
            }

            result = angelscript_engine->SetEngineProperty(asEP_ALLOW_MULTILINE_STRINGS, 1); // enable multiline strings.

            if (result < 0)
            {
                std::cerr << "Setting engine property `asEP_ALLOW_MULTILINE_STRINGS` failed!\n";
            }

            RegisterStdString(this->angelscript_engine);

            // result = angelscript_engine->RegisterObjectMethod("object", "float square(float x)", asMETHODPR(yli::angelscript::AngelscriptMaster, square, (float), float), asCALL_THISCALL);
            result = angelscript_engine->RegisterGlobalFunction("float square(float)", asMETHODPR(yli::angelscript::AngelscriptMaster, square, (float), float), asCALL_THISCALL_ASGLOBAL, this);

            if (result < 0)
            {
                std::cerr << "Registering global function float `square(float x)` failed!\n";
            }

            // result = angelscript_engine->RegisterObjectMethod("object", "float cube(float x)", asMETHODPR(yli::angelscript::AngelscriptMaster, cube, (float), float), asCALL_THISCALL);
            result = angelscript_engine->RegisterGlobalFunction("float cube(float x)", asMETHODPR(yli::angelscript::AngelscriptMaster, cube, (float), float), asCALL_THISCALL_ASGLOBAL, this);

            if (result < 0)
            {
                std::cerr << "Registering global function float `cube(float x)` failed!\n";
            }

            // result = angelscript_engine->RegisterObjectMethod("object", "void print(string &in)", asMETHODPR(yli::angelscript::AngelscriptMaster, print, (const std::string&), void), asCALL_THISCALL);
            result = angelscript_engine->RegisterGlobalFunction("void print(string &in)", asMETHODPR(yli::angelscript::AngelscriptMaster, print, (const std::string&), void), asCALL_THISCALL_ASGLOBAL, this);

            if (result < 0)
            {
                std::cerr << "Registering global function float `void print(const string &in)` failed!\n";
            }

            // result = angelscript_engine->RegisterObjectMethod("object", "void print(float x)", asMETHODPR(yli::angelscript::AngelscriptMaster, print, (float), void), asCALL_THISCALL);
            result = angelscript_engine->RegisterGlobalFunction("void print(float x)", asMETHODPR(yli::angelscript::AngelscriptMaster, print, (float), void), asCALL_THISCALL_ASGLOBAL, this);

            if (result < 0)
            {
                std::cerr << "Registering global function float `void print(float x)` failed!\n";
            }
        }

        AngelscriptMaster::~AngelscriptMaster()
        {
            // destructor.
            this->angelscript_engine->ShutDownAndRelease();
        }

        std::string AngelscriptMaster::eval_string(const std::string& my_string)
        {
            this->eval_output = ""; // reset eval output.

            if (this->angelscript_engine == nullptr)
            {
                return "";
            }

            CScriptBuilder builder;

            int result = builder.StartNewModule(this->angelscript_engine, "MyModule");

            if (result < 0)
            {
                std::cerr << "Error when executing `builder.StartNewModule`!\n";
                return "";
            }

            result = builder.AddSectionFromMemory("MySection", my_string.c_str(), my_string.size(), 0);

            if (result < 0)
            {
                std::cerr << "Error when executing `builder.AddSectionFromMemory`!\n";
                return "";
            }

            result = builder.BuildModule();

            if (result < 0)
            {
                std::cerr << "Error when executing `builder.BuildModule`!\n";
                return "";
            }

            asIScriptModule* module = this->angelscript_engine->GetModule("MyModule");

            if (module == nullptr)
            {
                std::cerr << "ERROR: `module` is `nullptr`!\n";
                return "";
            }

            asIScriptFunction* function = module->GetFunctionByDecl("void main()");

            if (function == nullptr)
            {
                std::cerr << "ERROR: function` is `nullptr`!\n";
                return "";
            }

            asIScriptContext* context = this->angelscript_engine->CreateContext();

            if (context == nullptr)
            {
                std::cerr << "ERROR: context` is `nullptr`!\n";
                return "";
            }

            context->Prepare(function);

            result = context->Execute();

            if (result != asEXECUTION_FINISHED)
            {
                std::cerr << "ERROR: execution did not finish normally!\n";

                if (result == asEXECUTION_EXCEPTION)
                {
                    std::cerr << "ERROR: `asEXECUTION_EXCEPTION`!\n";
                }

                context->Release();
                return "";
            }

            context->Release();
            return this->eval_output;
        }

        float AngelscriptMaster::square(const float x)
        {
            return x * x;
        }

        float AngelscriptMaster::cube(const float x)
        {
            return x * x * x;
        }

        void AngelscriptMaster::print(const std::string& my_message)
        {
            this->eval_output += my_message;
        }

        void AngelscriptMaster::print(const float value)
        {
            this->eval_output += std::to_string(value);
        }
    }
}
