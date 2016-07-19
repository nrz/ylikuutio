#ifndef __ANY_VALUE_HPP_INCLUDED
#define __ANY_VALUE_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
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

namespace datatypes
{
    enum datatype
    {
        UNKNOWN,
        BOOL,
        FLOAT,
        DOUBLE,
        INT32_T,
        UINT32_T,
        BOOL_POINTER,
        FLOAT_POINTER,
        DOUBLE_POINTER,
        INT32_T_POINTER,
        UINT32_T_POINTER,
        UNIVERSE_POINTER,
        SCENE_POINTER,
        SHADER_POINTER,
        MATERIAL_POINTER,
        SPECIES_POINTER,
        OBJECT_POINTER,
        VECTORFONT_POINTER,
        GLYPH_POINTER,
        TEXT3D_POINTER
    };

    typedef class AnyValue
    {
        public:
            AnyValue();
            AnyValue(bool bool_value);
            AnyValue(float float_value);
            AnyValue(double double_value);
            AnyValue(int32_t int32_t_value);
            AnyValue(uint32_t uint32_t_value);
            AnyValue(bool* bool_pointer);
            AnyValue(float* float_pointer);
            AnyValue(double* double_pointer);
            AnyValue(int32_t* int32_t_pointer);
            AnyValue(uint32_t* uint32_t_pointer);
            AnyValue(ontology::Universe* universe_pointer);
            AnyValue(ontology::Scene* scene_pointer);
            AnyValue(ontology::Shader* shader_pointer);
            AnyValue(ontology::Material* material_pointer);
            AnyValue(ontology::Species* species_pointer);
            AnyValue(ontology::Object* object_pointer);
            AnyValue(ontology::VectorFont* vector_font_pointer);
            AnyValue(ontology::Glyph* glyph_pointer);
            AnyValue(ontology::Text3D* text3D_pointer);

            AnyValue(std::string type, bool bool_value);
            AnyValue(std::string type, float float_value);
            AnyValue(std::string type, double double_value);
            AnyValue(std::string type, int32_t int32_t_value);
            AnyValue(std::string type, uint32_t uint32_t_value);
            AnyValue(std::string type, bool* bool_pointer);
            AnyValue(std::string type, float* float_pointer);
            AnyValue(std::string type, double* double_pointer);
            AnyValue(std::string type, int32_t* int32_t_pointer);
            AnyValue(std::string type, uint32_t* uint32_t_pointer);
            AnyValue(std::string type, ontology::Universe* universe_pointer);
            AnyValue(std::string type, ontology::Scene* scene_pointer);
            AnyValue(std::string type, ontology::Shader* shader_pointer);
            AnyValue(std::string type, ontology::Material* material_pointer);
            AnyValue(std::string type, ontology::Species* species_pointer);
            AnyValue(std::string type, ontology::Object* object_pointer);
            AnyValue(std::string type, ontology::VectorFont* vector_font_pointer);
            AnyValue(std::string type, ontology::Glyph* glyph_pointer);
            AnyValue(std::string type, ontology::Text3D* text3D_pointer);

            int type;
            bool bool_value;
            float float_value;
            double double_value;
            int32_t int32_t_value;
            uint32_t uint32_t_value;
            bool* bool_pointer;
            float* float_pointer;
            double* double_pointer;
            int32_t* int32_t_pointer;
            uint32_t* uint32_t_pointer;
            ontology::Universe* universe_pointer;
            ontology::Scene* scene_pointer;
            ontology::Shader* shader_pointer;
            ontology::Material* material_pointer;
            ontology::Species* species_pointer;
            ontology::Object* object_pointer;
            ontology::VectorFont* vector_font_pointer;
            ontology::Glyph* glyph_pointer;
            ontology::Text3D* text3D_pointer;

        private:
            void set_default_values();
    } AnyValue;
}

#endif
