#include "any_value.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <stdio.h>  // printf, snprintf, sprintf
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    class Universe;
    class Scene;
    class Shader;
    class Material;
    class Species;
    class Object;
    class VectorFont;
    class Glyph;
    class Text3D;
}

namespace font2D
{
    class Font2D;
}

namespace console
{
    class Console;
}

namespace datatypes
{
    std::string AnyValue::get_datatype()
    {
        std::string datatype_string;

        switch (this->type)
        {
            case (UNKNOWN):
                return "unknown";
            case (BOOL):
                return "bool";
            case (CHAR):
                return "char";
            case (FLOAT):
                return "float";
            case (DOUBLE):
                return "double";
            case (INT32_T):
                return "int32_t";
            case (UINT32_T):
                return "uint32_t";
            case (BOOL_POINTER):
                return "bool*";
            case (FLOAT_POINTER):
                return "float*";
            case (DOUBLE_POINTER):
                return "double*";
            case (INT32_T_POINTER):
                return "int32_t*";
            case (UINT32_T_POINTER):
                return "uint32_t*";
            case (UNIVERSE_POINTER):
                return "ontology::Universe*";
            case (SCENE_POINTER):
                return "ontology::Scene*";
            case (SHADER_POINTER):
                return "ontology::Shader*";
            case (MATERIAL_POINTER):
                return "ontology::Material*";
            case (SPECIES_POINTER):
                return "ontology::Species*";
            case (OBJECT_POINTER):
                return "ontology::Object*";
            case (VECTORFONT_POINTER):
                return "ontology::VectorFont*";
            case (GLYPH_POINTER):
                return "ontology::Glyph*";
            case (TEXT3D_POINTER):
                return "ontology::Text3D*";
            case (TEXT2D_POINTER):
                return "ontology::Text2D*";
            case (CONSOLE_POINTER):
                return "console::Console*";
            default:
                return "TODO: define string for this datatype!";
        }
    }

    std::string AnyValue::get_string()
    {
        uint32_t buffer_size = 128;
        char buffer[buffer_size];

        switch (this->type)
        {
            case (UNKNOWN):
                return "unknown";
            case (BOOL):
                return (this->bool_value ? "true" : "false");
            case (CHAR):
                snprintf(buffer, buffer_size, "%c", this->char_value);
                return std::string(buffer);
            case (FLOAT):
                snprintf(buffer, buffer_size, "%f", this->float_value);
                return std::string(buffer);
            case (DOUBLE):
                snprintf(buffer, buffer_size, "%f", this->double_value);
                return std::string(buffer);
            case (INT32_T):
                snprintf(buffer, buffer_size, "%f", this->int32_t_value);
                return std::string(buffer);
            case (UINT32_T):
                snprintf(buffer, buffer_size, "%lu", this->uint32_t_value);
                return std::string(buffer);
            case (BOOL_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->bool_pointer));
                return std::string(buffer);
            case (FLOAT_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->float_pointer));
                return std::string(buffer);
            case (DOUBLE_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->double_pointer));
                return std::string(buffer);
            case (INT32_T_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->int32_t_pointer));
                return std::string(buffer);
            case (UINT32_T_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->uint32_t_pointer));
                return std::string(buffer);
            case (UNIVERSE_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->universe_pointer));
                return std::string(buffer);
            case (SCENE_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->scene_pointer));
                return std::string(buffer);
            case (SHADER_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->shader_pointer));
                return std::string(buffer);
            case (MATERIAL_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->material_pointer));
                return std::string(buffer);
            case (SPECIES_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->species_pointer));
                return std::string(buffer);
            case (OBJECT_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->object_pointer));
                return std::string(buffer);
            case (VECTORFONT_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->vector_font_pointer));
                return std::string(buffer);
            case (GLYPH_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->glyph_pointer));
                return std::string(buffer);
            case (TEXT3D_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->text3D_pointer));
                return std::string(buffer);
            case (TEXT2D_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->text2D_pointer));
                return std::string(buffer);
            case (CONSOLE_POINTER):
                snprintf(buffer, buffer_size, "%llu", static_cast<void*>(this->console_pointer));
                return std::string(buffer);
            default:
                return "TODO: define string for this datatype!";
        }
    }

    void AnyValue::set_default_values()
    {
        this->type = datatypes::UNKNOWN;
        this->bool_value = false;
        this->char_value = 0;
        this->float_value = NAN;
        this->double_value = NAN;
        this->int32_t_value = 0;
        this->uint32_t_value = 0;
        this->bool_pointer = nullptr;
        this->float_pointer = nullptr;
        this->double_pointer = nullptr;
        this->int32_t_pointer = nullptr;
        this->uint32_t_pointer = nullptr;
        this->universe_pointer = nullptr;
        this->scene_pointer = nullptr;
        this->shader_pointer = nullptr;
        this->material_pointer = nullptr;
        this->species_pointer = nullptr;
        this->object_pointer = nullptr;
        this->vector_font_pointer = nullptr;
        this->glyph_pointer = nullptr;
        this->text3D_pointer = nullptr;
        this->text2D_pointer = nullptr;
        this->console_pointer = nullptr;
    }

    AnyValue::AnyValue()
    {
        // constructor.
        this->set_default_values();
    }

    AnyValue::AnyValue(bool bool_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::BOOL;
        this->bool_value = bool_value;
    }

    AnyValue::AnyValue(std::string type, bool bool_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "bool"))
        {
            this->type = datatypes::BOOL;
            this->bool_value = bool_value;
        }
    }

    AnyValue::AnyValue(char char_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::CHAR;
        this->char_value = char_value;
    }

    AnyValue::AnyValue(std::string type, char char_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "char"))
        {
            this->type = datatypes::CHAR;
            this->char_value = char_value;
        }
    }

    AnyValue::AnyValue(float float_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::FLOAT;
        this->float_value = float_value;
    }

    AnyValue::AnyValue(std::string type, float float_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "float"))
        {
            this->type = datatypes::FLOAT;
            this->float_value = float_value;
        }
    }

    AnyValue::AnyValue(double double_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::DOUBLE;
        this->double_value = double_value;
    }

    AnyValue::AnyValue(std::string type, double double_value)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "double"))
        {
            this->type = datatypes::DOUBLE;
            this->double_value = double_value;
        }
    }

    AnyValue::AnyValue(int32_t int32_t_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::INT32_T;
        this->int32_t_value = int32_t_value;
    }

    AnyValue::AnyValue(std::string type, int32_t int32_t_value)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "int32_t"))
        {
            this->type = datatypes::INT32_T;
            this->int32_t_value = int32_t_value;
        }
    }

    AnyValue::AnyValue(uint32_t uint32_t_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UINT32_T;
        this->uint32_t_value = uint32_t_value;
    }

    AnyValue::AnyValue(std::string type, uint32_t uint32_t_value)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "uint32_t"))
        {
            this->type = datatypes::UINT32_T;
            this->uint32_t_value = uint32_t_value;
        }
    }

    AnyValue::AnyValue(bool* bool_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::BOOL_POINTER;
        this->bool_pointer = bool_pointer;
    }

    AnyValue::AnyValue(std::string type, bool* bool_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "bool*"))
        {
            this->type = datatypes::BOOL_POINTER;
            this->bool_pointer = bool_pointer;
        }
    }

    AnyValue::AnyValue(float* float_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::FLOAT_POINTER;
        this->float_pointer = float_pointer;
    }

    AnyValue::AnyValue(std::string type, float* float_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "float*"))
        {
            this->type = datatypes::FLOAT_POINTER;
            this->float_pointer = float_pointer;
        }
    }

    AnyValue::AnyValue(double* double_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::DOUBLE_POINTER;
        this->double_pointer = double_pointer;
    }

    AnyValue::AnyValue(std::string type, double* double_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "double*"))
        {
            this->type = datatypes::DOUBLE_POINTER;
            this->double_pointer = double_pointer;
        }
    }

    AnyValue::AnyValue(int32_t* int32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::INT32_T_POINTER;
        this->int32_t_pointer = int32_t_pointer;
    }

    AnyValue::AnyValue(std::string type, int32_t* int32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "int32_t*"))
        {
            this->type = datatypes::INT32_T_POINTER;
            this->int32_t_pointer = int32_t_pointer;
        }
    }

    AnyValue::AnyValue(uint32_t* uint32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UINT32_T_POINTER;
        this->uint32_t_pointer = uint32_t_pointer;
    }

    AnyValue::AnyValue(std::string type, uint32_t* uint32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "uint32_t*"))
        {
            this->type = datatypes::UINT32_T_POINTER;
            this->uint32_t_pointer = uint32_t_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Universe* universe_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UNIVERSE_POINTER;
        this->universe_pointer = universe_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Universe* universe_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Universe*"))
        {
            this->type = datatypes::UNIVERSE_POINTER;
            this->universe_pointer = universe_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Scene* scene_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SCENE_POINTER;
        this->scene_pointer = scene_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Scene* scene_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Scene*"))
        {
            this->type = datatypes::SCENE_POINTER;
            this->scene_pointer = scene_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Shader* shader_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SHADER_POINTER;
        this->shader_pointer = shader_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Shader* shader_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Shader*"))
        {
            this->type = datatypes::SHADER_POINTER;
            this->shader_pointer = shader_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Material* material_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::MATERIAL_POINTER;
        this->material_pointer = material_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Material* material_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Material*"))
        {
            this->type = datatypes::MATERIAL_POINTER;
            this->material_pointer = material_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Species* species_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SPECIES_POINTER;
        this->species_pointer = species_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Species* species_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Species*"))
        {
            this->type = datatypes::SPECIES_POINTER;
            this->species_pointer = species_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Object* object_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::OBJECT_POINTER;
        this->object_pointer = object_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Object* object_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Object*"))
        {
            this->type = datatypes::OBJECT_POINTER;
            this->object_pointer = object_pointer;
        }
    }

    AnyValue::AnyValue(ontology::VectorFont* vector_font_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::VECTORFONT_POINTER;
        this->vector_font_pointer = vector_font_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::VectorFont* vector_font_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Vectorfont*"))
        {
            this->type = datatypes::VECTORFONT_POINTER;
            this->vector_font_pointer = vector_font_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Glyph* glyph_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::GLYPH_POINTER;
        this->glyph_pointer = glyph_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Glyph* glyph_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Glyph*"))
        {
            this->type = datatypes::GLYPH_POINTER;
            this->glyph_pointer = glyph_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Text3D* text3D_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::TEXT3D_POINTER;
        this->text3D_pointer = text3D_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Text3D* text3D_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Text3D*"))
        {
            this->type = datatypes::TEXT3D_POINTER;
            this->text3D_pointer = text3D_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Font2D* text2D_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::TEXT2D_POINTER;
        this->text2D_pointer = text2D_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Font2D* text2D_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Font2D*"))
        {
            this->type = datatypes::TEXT2D_POINTER;
            this->text2D_pointer = text2D_pointer;
        }
    }

    AnyValue::AnyValue(console::Console* console_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::CONSOLE_POINTER;
        this->console_pointer = console_pointer;
    }

    AnyValue::AnyValue(std::string type, console::Console* console_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "console::Console*"))
        {
            this->type = datatypes::CONSOLE_POINTER;
            this->console_pointer = console_pointer;
        }
    }
}
