#include "any_value.hpp"
#include "spherical_coordinates_struct.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/text3D.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cerrno>   // errno
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <inttypes.h> // PRId32, PRId64, PRIu32, PRIu64, PRIx32, PRIx64
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.
#include <stdlib.h> // std::strtol, std::strtoll, std::strtoul

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
    class Symbiosis;
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
            case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                return "SphericalCoordinatesStruct*";
            case (STD_STRING_POINTER):
                return "std::string*";
            case (GLM_VEC3_POINTER):
                return "glm::vec3*";
            default:
                return "TODO: define string for this datatype!";
        }
    }

    std::string AnyValue::get_string() const
    {
        const uint32_t buffer_size = 128;
        char buffer[buffer_size];

        switch (this->type)
        {
            case (UNKNOWN):
                return "unknown";
            case (BOOL):
                return (this->bool_value ? "true" : "false");
            case (CHAR):
                std::snprintf(buffer, sizeof(buffer), "%c", this->char_value);
                return std::string(buffer);
            case (FLOAT):
                std::snprintf(buffer, sizeof(buffer), "%f", this->float_value);
                return std::string(buffer);
            case (DOUBLE):
                std::snprintf(buffer, sizeof(buffer), "%f", this->double_value);
                return std::string(buffer);
            case (INT32_T):
                // in Linux `int` is 32 bits, `long` is 64 bits, `long long` is also 64 bits.
                // in Windows `int` is 32 bits, `long` is also 32 bits, `long long` is 64 bits.
                std::snprintf(buffer, sizeof(buffer), "%" PRId32, this->int32_t_value);
                return std::string(buffer);
            case (UINT32_T):

                // in Linux `int` is 32 bits, `long` is 64 bits, `long long` is also 64 bits.
                // in Windows `int` is 32 bits, `long` is also 32 bits, `long long` is 64 bits.
                std::snprintf(buffer, sizeof(buffer), "%" PRIu32, this->uint32_t_value);
                return std::string(buffer);
            case (BOOL_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->bool_pointer);
                return std::string(buffer);
            case (FLOAT_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->float_pointer);
                return std::string(buffer);
            case (DOUBLE_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->double_pointer);
                return std::string(buffer);
            case (INT32_T_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->int32_t_pointer);
                return std::string(buffer);
            case (UINT32_T_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->uint32_t_pointer);
                return std::string(buffer);
            case (UNIVERSE_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->universe_pointer);
                return std::string(buffer);
            case (SCENE_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->scene_pointer);
                return std::string(buffer);
            case (SHADER_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->shader_pointer);
                return std::string(buffer);
            case (MATERIAL_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->material_pointer);
                return std::string(buffer);
            case (SPECIES_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->species_pointer);
                return std::string(buffer);
            case (OBJECT_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->object_pointer);
                return std::string(buffer);
            case (VECTORFONT_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->vector_font_pointer);
                return std::string(buffer);
            case (GLYPH_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->glyph_pointer);
                return std::string(buffer);
            case (TEXT3D_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->text3D_pointer);
                return std::string(buffer);
            case (TEXT2D_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->font2D_pointer);
                return std::string(buffer);
            case (CONSOLE_POINTER):
                std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->console_pointer);
                return std::string(buffer);
            case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                if (this->spherical_coordinates_struct_pointer == nullptr)
                {
                    std::snprintf(buffer, sizeof(buffer), "nullptr");
                }
                else
                {
                    std::snprintf(buffer, sizeof(buffer), "{ %f, %f, %f }",
                            this->spherical_coordinates_struct_pointer->rho,
                            this->spherical_coordinates_struct_pointer->theta,
                            this->spherical_coordinates_struct_pointer->phi);
                }
                return std::string(buffer);
            case (STD_STRING_POINTER):
                if (this->std_string_pointer == nullptr)
                {
                    std::snprintf(buffer, sizeof(buffer), "nullptr");
                    return std::string(buffer);
                }
                return std::string(*this->std_string_pointer);
            case (GLM_VEC3_POINTER):
                if (this->glm_vec3_pointer == nullptr)
                {
                    std::snprintf(buffer, sizeof(buffer), "nullptr");
                }
                else
                {
                    std::snprintf(buffer, sizeof(buffer), "{ %f, %f, %f }",
                            this->glm_vec3_pointer->x,
                            this->glm_vec3_pointer->y,
                            this->glm_vec3_pointer->z);
                }
                return std::string(buffer);
            default:
                return "TODO: define string for this datatype!";
        }
    }

    ontology::Entity* AnyValue::get_entity_pointer() const
    {
        switch (this->type)
        {
            case (UNIVERSE_POINTER):
                return this->universe_pointer;
            case (SCENE_POINTER):
                return this->scene_pointer;
            case (SHADER_POINTER):
                return this->shader_pointer;
            case (MATERIAL_POINTER):
                return this->material_pointer;
            case (SPECIES_POINTER):
                return this->species_pointer;
            case (OBJECT_POINTER):
                return this->object_pointer;
            case (VECTORFONT_POINTER):
                return this->vector_font_pointer;
            case (GLYPH_POINTER):
                return this->glyph_pointer;
            case (TEXT3D_POINTER):
                return this->text3D_pointer;
            default:
                return nullptr;
        }
    }

    bool AnyValue::set_value(const std::string& value_string)
    {
        char* end;

        switch (this->type)
        {
            case (UNKNOWN):
                return false;
            case (BOOL):
                {
                    if (strcmp(value_string.c_str(), "true") == 0) // Ylikuutio is case sensitive!
                    {
                        this->bool_value = true;
                        return true;
                    }
                    else if (strcmp(value_string.c_str(), "false") == 0) // Ylikuutio is case sensitive!
                    {
                        this->bool_value = false;
                        return true;
                    }
                    return false;
                }
            case (CHAR):
                {
                    if (value_string.size() == 1)
                    {
                        this->char_value = value_string[0];
                        return true;
                    }
                    return false;
                }
            case (FLOAT):
                {
                    if (!string::check_if_float_string(value_string))
                    {
                        return false;
                    }

                    float float_value = std::strtof(value_string.c_str(), &end);
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->float_value = float_value;
                    return true;
                }
            case (DOUBLE):
                {
                    if (!string::check_if_float_string(value_string))
                    {
                        return false;
                    }

                    double double_value = std::strtod(value_string.c_str(), &end);
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->double_value = double_value;
                    return true;
                }
            case (INT32_T):
                {
                    if (!string::check_if_signed_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    int32_t int32_t_value = std::strtol(value_string.c_str(), &end, 0);
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->int32_t_value = int32_t_value;
                    return true;
                }
            case (UINT32_T):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    uint32_t uint32_t_value = std::strtoul(value_string.c_str(), &end, 0);
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->uint32_t_value = uint32_t_value;
                    return true;
                }
            case (BOOL_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    bool* bool_pointer = (bool*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->bool_pointer = bool_pointer;
                    return true;
                }
            case (FLOAT_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    float* float_pointer = (float*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->float_pointer = float_pointer;
                    return true;
                }
            case (DOUBLE_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    double* double_pointer = (double*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->double_pointer = double_pointer;
                    return true;
                }
            case (INT32_T_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    int32_t* int32_t_pointer = (int32_t*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->int32_t_pointer = int32_t_pointer;
                    return true;
                }
            case (UINT32_T_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    uint32_t* uint32_t_pointer = (uint32_t*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->uint32_t_pointer = uint32_t_pointer;
                    return true;
                }
            case (UNIVERSE_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Universe* universe_pointer = (ontology::Universe*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->universe_pointer = universe_pointer;
                    return true;
                }
            case (SCENE_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Scene* scene_pointer = (ontology::Scene*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->scene_pointer = scene_pointer;
                    return true;
                }
            case (SHADER_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Shader* shader_pointer = (ontology::Shader*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->shader_pointer = shader_pointer;
                    return true;
                }
            case (MATERIAL_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Material* material_pointer = (ontology::Material*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->material_pointer = material_pointer;
                    return true;
                }
            case (SPECIES_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Species* species_pointer = (ontology::Species*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->species_pointer = species_pointer;
                    return true;
                }
            case (OBJECT_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Object* object_pointer = (ontology::Object*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->object_pointer = object_pointer;
                    return true;
                }
            case (VECTORFONT_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::VectorFont* vector_font_pointer = (ontology::VectorFont*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->vector_font_pointer = vector_font_pointer;
                    return true;
                }
            case (GLYPH_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Glyph* glyph_pointer = (ontology::Glyph*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->glyph_pointer = glyph_pointer;
                    return true;
                }
            case (TEXT3D_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Text3D* text3D_pointer = (ontology::Text3D*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->text3D_pointer = text3D_pointer;
                    return true;
                }
            case (TEXT2D_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    ontology::Font2D* font2D_pointer = (ontology::Font2D*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->font2D_pointer = font2D_pointer;
                    return true;
                }
            case (CONSOLE_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    // 0 means that the base is determined by the format given in string.
                    // The size of the pointer is assumed to be 64 bits.
                    console::Console* console_pointer = (console::Console*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->console_pointer = console_pointer;
                    return true;
                }
            case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    SphericalCoordinatesStruct* spherical_coordinates_struct_pointer = (SphericalCoordinatesStruct*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
                    return true;
                }
            case (GLM_VEC3_POINTER):
                {
                    if (!string::check_if_unsigned_integer_string(value_string))
                    {
                        return false;
                    }

                    glm::vec3* glm_vec3_pointer = (glm::vec3*) (std::strtoll(value_string.c_str(), &end, 0));
                    if (errno == ERANGE)
                    {
                        return false;
                    }
                    this->glm_vec3_pointer = glm_vec3_pointer;
                    return true;
                }
            default:
                return false;
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
        this->symbiosis_pointer = nullptr;
        this->font2D_pointer = nullptr;
        this->console_pointer = nullptr;
        this->spherical_coordinates_struct_pointer = nullptr;
        this->std_string_pointer = nullptr;
        this->glm_vec3_pointer = nullptr;
    }

    AnyValue::AnyValue(const datatypes::AnyValue& original)
    {
        // copy constructor.
        this->type = original.type;
        this->bool_value = original.bool_value;
        this->char_value = original.char_value;
        this->float_value = original.float_value;
        this->double_value = original.double_value;
        this->int32_t_value = original.int32_t_value;
        this->uint32_t_value = original.uint32_t_value;
        this->bool_pointer = original.bool_pointer;
        this->float_pointer = original.float_pointer;
        this->double_pointer = original.double_pointer;
        this->int32_t_pointer = original.int32_t_pointer;
        this->uint32_t_pointer = original.uint32_t_pointer;
        this->universe_pointer = original.universe_pointer;
        this->scene_pointer = original.scene_pointer;
        this->shader_pointer = original.shader_pointer;
        this->material_pointer = original.material_pointer;
        this->species_pointer = original.species_pointer;
        this->object_pointer = original.object_pointer;
        this->vector_font_pointer = original.vector_font_pointer;
        this->glyph_pointer = original.glyph_pointer;
        this->text3D_pointer = original.text3D_pointer;
        this->symbiosis_pointer = original.symbiosis_pointer;
        this->font2D_pointer = original.font2D_pointer;
        this->console_pointer = original.console_pointer;
        this->spherical_coordinates_struct_pointer = original.spherical_coordinates_struct_pointer;
        this->glm_vec3_pointer = original.glm_vec3_pointer;
    }

    AnyValue::AnyValue(const std::string& type, const std::string& value_string)
    {
        this->set_default_values();

        if (std::strcmp(type.c_str(), "bool") == 0)
        {
            this->type = datatypes::BOOL;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "char") == 0)
        {
            this->type = datatypes::CHAR;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "float") == 0)
        {
            this->type = datatypes::FLOAT;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "double") == 0)
        {
            this->type = datatypes::DOUBLE;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "int32_t") == 0)
        {
            this->type = datatypes::INT32_T;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "uint32_t") == 0)
        {
            this->type = datatypes::UINT32_T;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "bool*") == 0)
        {
            this->type = datatypes::BOOL_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "float*") == 0)
        {
            this->type = datatypes::FLOAT_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "double*") == 0)
        {
            this->type = datatypes::FLOAT_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "int32_t*") == 0)
        {
            this->type = datatypes::INT32_T_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "uint32_t*") == 0)
        {
            this->type = datatypes::UINT32_T_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Universe*") == 0)
        {
            this->type = datatypes::UNIVERSE_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Scene*") == 0)
        {
            this->type = datatypes::SCENE_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Shader*") == 0)
        {
            this->type = datatypes::SHADER_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Material*") == 0)
        {
            this->type = datatypes::MATERIAL_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Species*") == 0)
        {
            this->type = datatypes::SPECIES_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Object*") == 0)
        {
            this->type = datatypes::OBJECT_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::VectorFont*") == 0)
        {
            this->type = datatypes::VECTORFONT_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Glyph*") == 0)
        {
            this->type = datatypes::GLYPH_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Text3D*") == 0)
        {
            this->type = datatypes::TEXT3D_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Symbiosis*") == 0)
        {
            this->type = datatypes::SYMBIOSIS_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "ontology::Text2D*") == 0)
        {
            this->type = datatypes::TEXT2D_POINTER;
            this->set_value(value_string);
        }
        else if (std::strcmp(type.c_str(), "console::Console*") == 0)
        {
            this->type = datatypes::CONSOLE_POINTER;
            this->set_value(value_string);
        }
        else
        {
            this->type = datatypes::UNKNOWN;
        }
    }

    AnyValue::AnyValue()
    {
        // constructor.
        this->set_default_values();
    }

    AnyValue::AnyValue(const bool bool_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::BOOL;
        this->bool_value = bool_value;
    }

    AnyValue::AnyValue(const std::string& type, const bool bool_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "bool") == 0)
        {
            this->type = datatypes::BOOL;
            this->bool_value = bool_value;
        }
    }

    AnyValue::AnyValue(const char char_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::CHAR;
        this->char_value = char_value;
    }

    AnyValue::AnyValue(const std::string& type, const char char_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "char") == 0)
        {
            this->type = datatypes::CHAR;
            this->char_value = char_value;
        }
    }

    AnyValue::AnyValue(const float float_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::FLOAT;
        this->float_value = float_value;
    }

    AnyValue::AnyValue(const std::string& type, const float float_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "float") == 0)
        {
            this->type = datatypes::FLOAT;
            this->float_value = float_value;
        }
    }

    AnyValue::AnyValue(const double double_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::DOUBLE;
        this->double_value = double_value;
    }

    AnyValue::AnyValue(const std::string& type, const double double_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "double") == 0)
        {
            this->type = datatypes::DOUBLE;
            this->double_value = double_value;
        }
    }

    AnyValue::AnyValue(const int32_t int32_t_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::INT32_T;
        this->int32_t_value = int32_t_value;
    }

    AnyValue::AnyValue(const std::string& type, const int32_t int32_t_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "int32_t") == 0)
        {
            this->type = datatypes::INT32_T;
            this->int32_t_value = int32_t_value;
        }
    }

    AnyValue::AnyValue(const uint32_t uint32_t_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UINT32_T;
        this->uint32_t_value = uint32_t_value;
    }

    AnyValue::AnyValue(const std::string& type, const uint32_t uint32_t_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "uint32_t") == 0)
        {
            this->type = datatypes::UINT32_T;
            this->uint32_t_value = uint32_t_value;
        }
    }

    AnyValue::AnyValue(bool* const bool_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::BOOL_POINTER;
        this->bool_pointer = bool_pointer;
    }

    AnyValue::AnyValue(const std::string& type, bool* const bool_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "bool*") == 0)
        {
            this->type = datatypes::BOOL_POINTER;
            this->bool_pointer = bool_pointer;
        }
    }

    AnyValue::AnyValue(float* const float_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::FLOAT_POINTER;
        this->float_pointer = float_pointer;
    }

    AnyValue::AnyValue(const std::string& type, float* const float_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "float*") == 0)
        {
            this->type = datatypes::FLOAT_POINTER;
            this->float_pointer = float_pointer;
        }
    }

    AnyValue::AnyValue(double* const double_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::DOUBLE_POINTER;
        this->double_pointer = double_pointer;
    }

    AnyValue::AnyValue(const std::string& type, double* const double_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "double*") == 0)
        {
            this->type = datatypes::DOUBLE_POINTER;
            this->double_pointer = double_pointer;
        }
    }

    AnyValue::AnyValue(int32_t* const int32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::INT32_T_POINTER;
        this->int32_t_pointer = int32_t_pointer;
    }

    AnyValue::AnyValue(const std::string& type, int32_t* const int32_t_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "int32_t*") == 0)
        {
            this->type = datatypes::INT32_T_POINTER;
            this->int32_t_pointer = int32_t_pointer;
        }
    }

    AnyValue::AnyValue(uint32_t* const uint32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UINT32_T_POINTER;
        this->uint32_t_pointer = uint32_t_pointer;
    }

    AnyValue::AnyValue(const std::string& type, uint32_t* const uint32_t_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "uint32_t*") == 0)
        {
            this->type = datatypes::UINT32_T_POINTER;
            this->uint32_t_pointer = uint32_t_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Universe* const universe_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UNIVERSE_POINTER;
        this->universe_pointer = universe_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Universe* const universe_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Universe*") == 0)
        {
            this->type = datatypes::UNIVERSE_POINTER;
            this->universe_pointer = universe_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Scene* const scene_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SCENE_POINTER;
        this->scene_pointer = scene_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Scene* const scene_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Scene*") == 0)
        {
            this->type = datatypes::SCENE_POINTER;
            this->scene_pointer = scene_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Shader* const shader_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SHADER_POINTER;
        this->shader_pointer = shader_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Shader* const shader_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Shader*") == 0)
        {
            this->type = datatypes::SHADER_POINTER;
            this->shader_pointer = shader_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Material* const material_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::MATERIAL_POINTER;
        this->material_pointer = material_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Material* const material_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Material*") == 0)
        {
            this->type = datatypes::MATERIAL_POINTER;
            this->material_pointer = material_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Species* const species_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SPECIES_POINTER;
        this->species_pointer = species_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Species* const species_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Species*") == 0)
        {
            this->type = datatypes::SPECIES_POINTER;
            this->species_pointer = species_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Object* const object_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::OBJECT_POINTER;
        this->object_pointer = object_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Object* const object_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Object*") == 0)
        {
            this->type = datatypes::OBJECT_POINTER;
            this->object_pointer = object_pointer;
        }
    }

    AnyValue::AnyValue(ontology::VectorFont* const vector_font_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::VECTORFONT_POINTER;
        this->vector_font_pointer = vector_font_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::VectorFont* const vector_font_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Vectorfont*") == 0)
        {
            this->type = datatypes::VECTORFONT_POINTER;
            this->vector_font_pointer = vector_font_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Glyph* const glyph_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::GLYPH_POINTER;
        this->glyph_pointer = glyph_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Glyph* const glyph_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Glyph*") == 0)
        {
            this->type = datatypes::GLYPH_POINTER;
            this->glyph_pointer = glyph_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Text3D* const text3D_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::TEXT3D_POINTER;
        this->text3D_pointer = text3D_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Text3D* const text3D_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Text3D*") == 0)
        {
            this->type = datatypes::TEXT3D_POINTER;
            this->text3D_pointer = text3D_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Font2D* const font2D_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::TEXT2D_POINTER;
        this->font2D_pointer = font2D_pointer;
    }

    AnyValue::AnyValue(const std::string& type, ontology::Font2D* const font2D_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "ontology::Font2D*") == 0)
        {
            this->type = datatypes::TEXT2D_POINTER;
            this->font2D_pointer = font2D_pointer;
        }
    }

    AnyValue::AnyValue(console::Console* const console_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::CONSOLE_POINTER;
        this->console_pointer = console_pointer;
    }

    AnyValue::AnyValue(const std::string& type, console::Console* const console_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "console::Console*") == 0)
        {
            this->type = datatypes::CONSOLE_POINTER;
            this->console_pointer = console_pointer;
        }
    }

    AnyValue::AnyValue(SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER;
        this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
    }

    AnyValue::AnyValue(const std::string& type, SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "SphericalCoordinatesStruct*") == 0)
        {
            this->type = datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER;
            this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
        }
    }

    AnyValue::AnyValue(std::string* const std_string_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::STD_STRING_POINTER;
        this->std_string_pointer = std_string_pointer;
    }

    AnyValue::AnyValue(const std::string& type, std::string* const std_string_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "std::string*") == 0)
        {
            this->type = datatypes::STD_STRING_POINTER;
            this->std_string_pointer = std_string_pointer;
        }
    }

    AnyValue::AnyValue(glm::vec3* const glm_vec3_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::GLM_VEC3_POINTER;
        this->glm_vec3_pointer = glm_vec3_pointer;
    }

    AnyValue::AnyValue(const std::string& type, glm::vec3* const glm_vec3_pointer)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "glm::vec3*") == 0)
        {
            this->type = datatypes::GLM_VEC3_POINTER;
            this->glm_vec3_pointer = glm_vec3_pointer;
        }
    }
}
