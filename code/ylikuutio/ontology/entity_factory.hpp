#ifndef __ENTITY_FACTORY_HPP_INCLUDED
#define __ENTITY_FACTORY_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "vector_font.hpp"
#include "text3D.hpp"
#include "font2D.hpp"
#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "vector_font_struct.hpp"
#include "text3D_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <string>    // std::string

namespace ontology
{
    class EntityFactory
    {
        public:
            EntityFactory();
            ~EntityFactory();

            static ontology::Entity* create_Universe();
            static ontology::Entity* create_Scene(ontology::Universe* const universe, const float water_level);
            static ontology::Entity* create_Shader(const ShaderStruct shader_struct);
            static ontology::Entity* create_Material(const MaterialStruct material_struct);
            static ontology::Entity* create_Species(const SpeciesStruct species_struct);
            static ontology::Entity* create_Object(const ObjectStruct object_struct);
            static ontology::Entity* create_VectorFont(const VectorFontStruct vector_font_struct);
            static ontology::Entity* create_Text3D(const Text3DStruct text3D_struct);
            static ontology::Entity* create_Font2D(
                    ontology::Universe* universe,
                    GLuint screen_width,
                    GLuint screen_height,
                    std::string texture_filename,
                    std::string font_texture_file_format);
    };
}

#endif
