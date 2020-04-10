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

#include "code/ylikuutio/angelscript/angelscript_callbacks.hpp"

#include "angelscript.h"
#include "scriptstdstring/scriptstdstring.h"
#include "scriptbuilder/scriptbuilder.h"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string

float square(const float x)
{
    return x * x;
}

float cube(const float x)
{
    return x * x * x;
}

asIScriptEngine* init_angelscript()
{
    asIScriptEngine* angelscript_engine = asCreateScriptEngine();

    if (angelscript_engine == nullptr)
    {
        std::cerr << "ERROR: `angelscript_engine` is `nullptr`!\n";
        return nullptr;
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

    RegisterStdString(angelscript_engine);

    result = angelscript_engine->RegisterGlobalFunction("float square(float x)", asFUNCTIONPR(square, (const float), float), asCALL_CDECL);

    if (result < 0)
    {
        std::cerr << "Registering global function float `square(float x)` failed!\n";
    }

    result = angelscript_engine->RegisterGlobalFunction("float cube(float x)", asFUNCTIONPR(cube, (const float), float), asCALL_CDECL);

    if (result < 0)
    {
        std::cerr << "Registering global function float `cube(float x)` failed!\n";
    }

    result = angelscript_engine->RegisterGlobalFunction("void print(string &in)", asFUNCTIONPR(yli::angelscript::print, (const std::string&), void), asCALL_CDECL);

    if (result < 0)
    {
        std::cerr << "Registering global function float `void print(const string &in)` failed!\n";
    }

    result = angelscript_engine->RegisterGlobalFunction("void print(float x)", asFUNCTIONPR(yli::angelscript::print, (const float), void), asCALL_CDECL);

    if (result < 0)
    {
        std::cerr << "Registering global function float `void print(float x)` failed!\n";
    }

    return angelscript_engine;
}

bool do_stuff(asIScriptEngine* angelscript_engine)
{
    if (angelscript_engine == nullptr)
    {
        std::cerr << "error: asIScriptEngine* angelscript_engine is nullptr\n";
        return false;
    }

    CScriptBuilder builder;

    // Execute script from file `hello_world.angel`.

    int result = builder.StartNewModule(angelscript_engine, "HelloWorldModule");

    if (result < 0)
    {
        std::cerr << "Error when executing `builder.StartNewModule`!\n";
        return false;
    }

    result = builder.AddSectionFromFile("hello_world.angel");

    if (result < 0)
    {
        std::cerr << "Error when executing `builder.AddSectionFromFile`!\n";
        return false;
    }

    result = builder.BuildModule();

    if (result < 0)
    {
        std::cerr << "Error when executing `builder.BuildModule`!\n";
        return false;
    }

    asIScriptModule* module = angelscript_engine->GetModule("HelloWorldModule");

    if (module == nullptr)
    {
        std::cerr << "ERROR: `module` is `nullptr`!\n";
        return false;
    }

    asIScriptFunction* function = module->GetFunctionByDecl("void main()");

    if (function == nullptr)
    {
        std::cerr << "ERROR: function` is `nullptr`!\n";
        return false;
    }

    asIScriptContext* context = angelscript_engine->CreateContext();

    if (context == nullptr)
    {
        std::cerr << "ERROR: context` is `nullptr`!\n";
        return false;
    }

    context->Prepare(function);

    result = context->Execute();

    if (result != asEXECUTION_FINISHED)
    {
        std::cerr << "ERROR: execution did not finish normally!\n";

        if (result == asEXECUTION_EXCEPTION)
        {
            std::cerr << "ERROR: `asEXECUTION_EXCEPTION`!\n";
            return false;
        }
    }

    context->Release();

    // Execute script from memory.

    result = builder.StartNewModule(angelscript_engine, "CubeModule");

    if (result < 0)
    {
        std::cerr << "Error when executing `builder.StartNewModule`!\n";
        return false;
    }

    const std::string square_cube_script =
        "void main()\n"
        "{\n"
        "print(\"5.0 squared is \");\n"
        "print(square(5.0));\n"
        "print(\"\n\");\n"
        "print(\"5.0 cubed is \");\n"
        "print(cube(5.0));\n"
        "print(\"\n\");\n"
        "}\n";

    result = builder.AddSectionFromMemory("CubeSection", square_cube_script.c_str(), square_cube_script.size(), 0);

    if (result < 0)
    {
        std::cerr << "Error when executing `builder.AddSectionFromMemory`!\n";
        return false;
    }

    result = builder.BuildModule();

    if (result < 0)
    {
        std::cerr << "Error when executing `builder.BuildModule`!\n";
        return false;
    }

    module = angelscript_engine->GetModule("CubeModule");

    if (module == nullptr)
    {
        std::cerr << "ERROR: `module` is `nullptr`!\n";
        return false;
    }

    function = module->GetFunctionByDecl("void main()");

    if (function == nullptr)
    {
        std::cerr << "ERROR: function` is `nullptr`!\n";
        return false;
    }

    context = angelscript_engine->CreateContext();

    if (context == nullptr)
    {
        std::cerr << "ERROR: context` is `nullptr`!\n";
        return false;
    }

    context->Prepare(function);

    result = context->Execute();

    if (result != asEXECUTION_FINISHED)
    {
        std::cerr << "ERROR: execution did not finish normally!\n";

        if (result == asEXECUTION_EXCEPTION)
        {
            std::cerr << "ERROR: `asEXECUTION_EXCEPTION`!\n";
            return false;
        }
    }

    context->Release();

    return true;
}

int main()
{
    asIScriptEngine* angelscript_engine = init_angelscript();

    if (angelscript_engine == nullptr)
    {
        std::cerr << "Error occurred in init_angelscript function.\n";
        return 1;
    }

    if (!do_stuff(angelscript_engine))
    {
        std::cerr << "Error occurred in do_stuff function.\n";
        angelscript_engine->ShutDownAndRelease();
        return 1;
    }

    angelscript_engine->ShutDownAndRelease();
    return 0;
}
