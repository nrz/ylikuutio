#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#include "any_value.hpp"
#include "spherical_coordinates_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cerrno>   // errno
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <inttypes.h> // PRId32, PRId64, PRIu32, PRIu64, PRIx32, PRIx64
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.
#include <stdlib.h> // std::strtol, std::strtoll, std::strtoul

namespace yli
{
    namespace console
    {
        class Console;
    }

    namespace ontology
    {
        class Entity;
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

    namespace datatypes
    {
        std::string AnyValue::get_datatype() const
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
                    return "yli::ontology::Universe*";
                case (SCENE_POINTER):
                    return "yli::ontology::Scene*";
                case (SHADER_POINTER):
                    return "yli::ontology::Shader*";
                case (MATERIAL_POINTER):
                    return "yli::ontology::Material*";
                case (SPECIES_POINTER):
                    return "yli::ontology::Species*";
                case (OBJECT_POINTER):
                    return "yli::ontology::Object*";
                case (VECTORFONT_POINTER):
                    return "yli::ontology::VectorFont*";
                case (GLYPH_POINTER):
                    return "yli::ontology::Glyph*";
                case (TEXT3D_POINTER):
                    return "yli::ontology::Text3D*";
                case (TEXT2D_POINTER):
                    return "yli::ontology::Text2D*";
                case (CONSOLE_POINTER):
                    return "yli::console::Console*";
                case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                    return "SphericalCoordinatesStruct*";
                case (STD_STRING_POINTER):
                    return "std::string*";
                case (GLM_VEC3_POINTER):
                    return "glm::vec3*";
                case (GLM_VEC4_POINTER):
                    return "glm::vec4*";
                default:
                    return "TODO: define string for this datatype!";
            }
        }

        std::string AnyValue::get_string() const
        {
            const std::size_t buffer_size = 128;
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
                    std::snprintf(buffer, sizeof(buffer), "%" PRIx64, (uint64_t) this->universe);
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
                case (GLM_VEC4_POINTER):
                    if (this->glm_vec4_pointer == nullptr)
                    {
                        std::snprintf(buffer, sizeof(buffer), "nullptr");
                    }
                    else
                    {
                        std::snprintf(buffer, sizeof(buffer), "{ %f, %f, %f, %f }",
                                this->glm_vec4_pointer->x,
                                this->glm_vec4_pointer->y,
                                this->glm_vec4_pointer->z,
                                this->glm_vec4_pointer->w);
                    }
                    return std::string(buffer);
                default:
                    return "TODO: define string for this datatype!";
            }
        }

        yli::ontology::Entity* AnyValue::get_entity_pointer() const
        {
            switch (this->type)
            {
                case (UNIVERSE_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->universe));
                case (SCENE_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->scene_pointer));
                case (SHADER_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->shader_pointer));
                case (MATERIAL_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->material_pointer));
                case (SPECIES_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->species_pointer));
                case (OBJECT_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->object_pointer));
                case (VECTORFONT_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->vector_font_pointer));
                case (GLYPH_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->glyph_pointer));
                case (TEXT3D_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->text3D_pointer));
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
                        if (!yli::string::check_if_float_string(value_string))
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
                        if (!yli::string::check_if_double_string(value_string))
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
                        if (!yli::string::check_if_signed_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Universe* universe = (yli::ontology::Universe*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->universe = universe;
                        return true;
                    }
                case (SCENE_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Scene* scene_pointer = (yli::ontology::Scene*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->scene_pointer = scene_pointer;
                        return true;
                    }
                case (SHADER_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Shader* shader_pointer = (yli::ontology::Shader*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->shader_pointer = shader_pointer;
                        return true;
                    }
                case (MATERIAL_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Material* material_pointer = (yli::ontology::Material*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->material_pointer = material_pointer;
                        return true;
                    }
                case (SPECIES_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Species* species_pointer = (yli::ontology::Species*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->species_pointer = species_pointer;
                        return true;
                    }
                case (OBJECT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Object* object_pointer = (yli::ontology::Object*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->object_pointer = object_pointer;
                        return true;
                    }
                case (VECTORFONT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::VectorFont* vector_font_pointer = (yli::ontology::VectorFont*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->vector_font_pointer = vector_font_pointer;
                        return true;
                    }
                case (GLYPH_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Glyph* glyph_pointer = (yli::ontology::Glyph*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->glyph_pointer = glyph_pointer;
                        return true;
                    }
                case (TEXT3D_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Text3D* text3D_pointer = (yli::ontology::Text3D*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->text3D_pointer = text3D_pointer;
                        return true;
                    }
                case (TEXT2D_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::ontology::Font2D* font2D_pointer = (yli::ontology::Font2D*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->font2D_pointer = font2D_pointer;
                        return true;
                    }
                case (CONSOLE_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        // 0 means that the base is determined by the format given in string.
                        // The size of the pointer is assumed to be 64 bits.
                        yli::console::Console* console_pointer = (yli::console::Console*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->console_pointer = console_pointer;
                        return true;
                    }
                case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
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
                case (GLM_VEC4_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        glm::vec4* glm_vec4_pointer = (glm::vec4*) (std::strtoll(value_string.c_str(), &end, 0));
                        if (errno == ERANGE)
                        {
                            return false;
                        }
                        this->glm_vec4_pointer = glm_vec4_pointer;
                        return true;
                    }
                default:
                    return false;
            }
        }

        void AnyValue::set_default_values()
        {
            this->type = yli::datatypes::UNKNOWN;
        }

        AnyValue::AnyValue(const yli::datatypes::AnyValue& original)
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
            this->universe = original.universe;
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
            this->std_string_pointer = original.std_string_pointer;
            this->glm_vec3_pointer = original.glm_vec3_pointer;
            this->glm_vec4_pointer = original.glm_vec4_pointer;
        }

        AnyValue::AnyValue(const std::string& type, const std::string& value_string)
        {
            this->set_default_values();

            if (std::strcmp(type.c_str(), "bool") == 0)
            {
                this->type = yli::datatypes::BOOL;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "char") == 0)
            {
                this->type = yli::datatypes::CHAR;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "float") == 0)
            {
                this->type = yli::datatypes::FLOAT;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "double") == 0)
            {
                this->type = yli::datatypes::DOUBLE;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "int32_t") == 0)
            {
                this->type = yli::datatypes::INT32_T;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "uint32_t") == 0)
            {
                this->type = yli::datatypes::UINT32_T;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "bool*") == 0)
            {
                this->type = yli::datatypes::BOOL_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "float*") == 0)
            {
                this->type = yli::datatypes::FLOAT_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "double*") == 0)
            {
                this->type = yli::datatypes::FLOAT_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "int32_t*") == 0)
            {
                this->type = yli::datatypes::INT32_T_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "uint32_t*") == 0)
            {
                this->type = yli::datatypes::UINT32_T_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Universe*") == 0)
            {
                this->type = yli::datatypes::UNIVERSE_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Scene*") == 0)
            {
                this->type = yli::datatypes::SCENE_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Shader*") == 0)
            {
                this->type = yli::datatypes::SHADER_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Material*") == 0)
            {
                this->type = yli::datatypes::MATERIAL_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Species*") == 0)
            {
                this->type = yli::datatypes::SPECIES_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Object*") == 0)
            {
                this->type = yli::datatypes::OBJECT_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::VectorFont*") == 0)
            {
                this->type = yli::datatypes::VECTORFONT_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Glyph*") == 0)
            {
                this->type = yli::datatypes::GLYPH_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Text3D*") == 0)
            {
                this->type = yli::datatypes::TEXT3D_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Symbiosis*") == 0)
            {
                this->type = yli::datatypes::SYMBIOSIS_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::ontology::Text2D*") == 0)
            {
                this->type = yli::datatypes::TEXT2D_POINTER;
                this->set_value(value_string);
            }
            else if (std::strcmp(type.c_str(), "yli::console::Console*") == 0)
            {
                this->type = yli::datatypes::CONSOLE_POINTER;
                this->set_value(value_string);
            }
            else
            {
                this->type = yli::datatypes::UNKNOWN;
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
            this->type = yli::datatypes::BOOL;
            this->bool_value = bool_value;
        }

        AnyValue::AnyValue(const std::string& type, const bool bool_value)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "bool") == 0)
            {
                this->type = yli::datatypes::BOOL;
                this->bool_value = bool_value;
            }
        }

        AnyValue::AnyValue(const char char_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::CHAR;
            this->char_value = char_value;
        }

        AnyValue::AnyValue(const std::string& type, const char char_value)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "char") == 0)
            {
                this->type = yli::datatypes::CHAR;
                this->char_value = char_value;
            }
        }

        AnyValue::AnyValue(const float float_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::FLOAT;
            this->float_value = float_value;
        }

        AnyValue::AnyValue(const std::string& type, const float float_value)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "float") == 0)
            {
                this->type = yli::datatypes::FLOAT;
                this->float_value = float_value;
            }
        }

        AnyValue::AnyValue(const double double_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::DOUBLE;
            this->double_value = double_value;
        }

        AnyValue::AnyValue(const std::string& type, const double double_value)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "double") == 0)
            {
                this->type = yli::datatypes::DOUBLE;
                this->double_value = double_value;
            }
        }

        AnyValue::AnyValue(const int32_t int32_t_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::INT32_T;
            this->int32_t_value = int32_t_value;
        }

        AnyValue::AnyValue(const std::string& type, const int32_t int32_t_value)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "int32_t") == 0)
            {
                this->type = yli::datatypes::INT32_T;
                this->int32_t_value = int32_t_value;
            }
        }

        AnyValue::AnyValue(const uint32_t uint32_t_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::UINT32_T;
            this->uint32_t_value = uint32_t_value;
        }

        AnyValue::AnyValue(const std::string& type, const uint32_t uint32_t_value)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "uint32_t") == 0)
            {
                this->type = yli::datatypes::UINT32_T;
                this->uint32_t_value = uint32_t_value;
            }
        }

        AnyValue::AnyValue(bool* const bool_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::BOOL_POINTER;
            this->bool_pointer = bool_pointer;
        }

        AnyValue::AnyValue(const std::string& type, bool* const bool_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "bool*") == 0)
            {
                this->type = yli::datatypes::BOOL_POINTER;
                this->bool_pointer = bool_pointer;
            }
        }

        AnyValue::AnyValue(float* const float_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::FLOAT_POINTER;
            this->float_pointer = float_pointer;
        }

        AnyValue::AnyValue(const std::string& type, float* const float_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "float*") == 0)
            {
                this->type = yli::datatypes::FLOAT_POINTER;
                this->float_pointer = float_pointer;
            }
        }

        AnyValue::AnyValue(double* const double_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::DOUBLE_POINTER;
            this->double_pointer = double_pointer;
        }

        AnyValue::AnyValue(const std::string& type, double* const double_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "double*") == 0)
            {
                this->type = yli::datatypes::DOUBLE_POINTER;
                this->double_pointer = double_pointer;
            }
        }

        AnyValue::AnyValue(int32_t* const int32_t_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::INT32_T_POINTER;
            this->int32_t_pointer = int32_t_pointer;
        }

        AnyValue::AnyValue(const std::string& type, int32_t* const int32_t_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "int32_t*") == 0)
            {
                this->type = yli::datatypes::INT32_T_POINTER;
                this->int32_t_pointer = int32_t_pointer;
            }
        }

        AnyValue::AnyValue(uint32_t* const uint32_t_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::UINT32_T_POINTER;
            this->uint32_t_pointer = uint32_t_pointer;
        }

        AnyValue::AnyValue(const std::string& type, uint32_t* const uint32_t_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "uint32_t*") == 0)
            {
                this->type = yli::datatypes::UINT32_T_POINTER;
                this->uint32_t_pointer = uint32_t_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Universe* const universe)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::UNIVERSE_POINTER;
            this->universe = universe;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Universe* const universe)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Universe*") == 0)
            {
                this->type = yli::datatypes::UNIVERSE_POINTER;
                this->universe = universe;
            }
        }

        AnyValue::AnyValue(yli::ontology::Scene* const scene_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::SCENE_POINTER;
            this->scene_pointer = scene_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Scene* const scene_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Scene*") == 0)
            {
                this->type = yli::datatypes::SCENE_POINTER;
                this->scene_pointer = scene_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Shader* const shader_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::SHADER_POINTER;
            this->shader_pointer = shader_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Shader* const shader_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Shader*") == 0)
            {
                this->type = yli::datatypes::SHADER_POINTER;
                this->shader_pointer = shader_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Material* const material_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::MATERIAL_POINTER;
            this->material_pointer = material_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Material* const material_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Material*") == 0)
            {
                this->type = yli::datatypes::MATERIAL_POINTER;
                this->material_pointer = material_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Species* const species_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::SPECIES_POINTER;
            this->species_pointer = species_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Species* const species_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Species*") == 0)
            {
                this->type = yli::datatypes::SPECIES_POINTER;
                this->species_pointer = species_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Object* const object_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::OBJECT_POINTER;
            this->object_pointer = object_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Object* const object_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Object*") == 0)
            {
                this->type = yli::datatypes::OBJECT_POINTER;
                this->object_pointer = object_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::VectorFont* const vector_font_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::VECTORFONT_POINTER;
            this->vector_font_pointer = vector_font_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::VectorFont* const vector_font_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Vectorfont*") == 0)
            {
                this->type = yli::datatypes::VECTORFONT_POINTER;
                this->vector_font_pointer = vector_font_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Glyph* const glyph_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::GLYPH_POINTER;
            this->glyph_pointer = glyph_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Glyph* const glyph_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Glyph*") == 0)
            {
                this->type = yli::datatypes::GLYPH_POINTER;
                this->glyph_pointer = glyph_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Text3D* const text3D_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::TEXT3D_POINTER;
            this->text3D_pointer = text3D_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Text3D* const text3D_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Text3D*") == 0)
            {
                this->type = yli::datatypes::TEXT3D_POINTER;
                this->text3D_pointer = text3D_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Font2D* const font2D_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::TEXT2D_POINTER;
            this->font2D_pointer = font2D_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Font2D* const font2D_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::ontology::Font2D*") == 0)
            {
                this->type = yli::datatypes::TEXT2D_POINTER;
                this->font2D_pointer = font2D_pointer;
            }
        }

        AnyValue::AnyValue(yli::console::Console* const console_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::CONSOLE_POINTER;
            this->console_pointer = console_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::console::Console* const console_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "yli::console::Console*") == 0)
            {
                this->type = yli::datatypes::CONSOLE_POINTER;
                this->console_pointer = console_pointer;
            }
        }

        AnyValue::AnyValue(SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER;
            this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
        }

        AnyValue::AnyValue(const std::string& type, SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "SphericalCoordinatesStruct*") == 0)
            {
                this->type = yli::datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER;
                this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
            }
        }

        AnyValue::AnyValue(std::string* const std_string_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::STD_STRING_POINTER;
            this->std_string_pointer = std_string_pointer;
        }

        AnyValue::AnyValue(const std::string& type, std::string* const std_string_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "std::string*") == 0)
            {
                this->type = yli::datatypes::STD_STRING_POINTER;
                this->std_string_pointer = std_string_pointer;
            }
        }

        AnyValue::AnyValue(glm::vec3* const glm_vec3_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::GLM_VEC3_POINTER;
            this->glm_vec3_pointer = glm_vec3_pointer;
        }

        AnyValue::AnyValue(const std::string& type, glm::vec3* const glm_vec3_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "glm::vec3*") == 0)
            {
                this->type = yli::datatypes::GLM_VEC3_POINTER;
                this->glm_vec3_pointer = glm_vec3_pointer;
            }
        }

        AnyValue::AnyValue(glm::vec4* const glm_vec4_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::datatypes::GLM_VEC4_POINTER;
            this->glm_vec4_pointer = glm_vec4_pointer;
        }

        AnyValue::AnyValue(const std::string& type, glm::vec4* const glm_vec4_pointer)
        {
            // constructor.
            this->set_default_values();

            if (std::strcmp(type.c_str(), "glm::vec4*") == 0)
            {
                this->type = yli::datatypes::GLM_VEC4_POINTER;
                this->glm_vec4_pointer = glm_vec4_pointer;
            }
        }
    }
}
