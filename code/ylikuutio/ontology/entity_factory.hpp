#ifndef __ENTITY_FACTORY_HPP_INCLUDED
#define __ENTITY_FACTORY_HPP_INCLUDED

#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "holobiont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text3D_struct.hpp"
#include "camera_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace ylikuutio
{
    namespace ontology
    {
        class Entity;
        class Universe;
        class World;
        class Scene;
        class Shader;
        class Material;
        class Species;
        class Object;
        class VectorFont;
        class Text3D;
        class Font2D;

        class EntityFactory
        {
            public:
                // destructor.
                ~EntityFactory();

                ylikuutio::ontology::Universe* get_universe() const;

                ylikuutio::ontology::Entity* create_Universe();
                ylikuutio::ontology::Entity* create_World();
                ylikuutio::ontology::Entity* create_Scene(ylikuutio::ontology::World* const world, const float water_level);
                ylikuutio::ontology::Entity* create_Shader(const ShaderStruct& shader_struct);
                ylikuutio::ontology::Entity* create_Material(const MaterialStruct& material_struct);
                ylikuutio::ontology::Entity* create_Species(const SpeciesStruct& species_struct);
                ylikuutio::ontology::Entity* create_Object(ObjectStruct& object_struct);
                ylikuutio::ontology::Entity* create_Symbiosis(const SymbiosisStruct& symbiosis_struct);
                ylikuutio::ontology::Entity* create_Holobiont(HolobiontStruct& object_struct);
                ylikuutio::ontology::Entity* create_VectorFont(const VectorFontStruct& vector_font_struct);
                ylikuutio::ontology::Entity* create_Text3D(Text3DStruct& text3D_struct);
                ylikuutio::ontology::Entity* create_Font2D(
                        GLuint screen_width,
                        GLuint screen_height,
                        const std::string& texture_filename,
                        const std::string& font_texture_file_format);
                ylikuutio::ontology::Entity* create_Camera(CameraStruct& camera_struct);

                friend class Universe;

            private:
                // constructor.
                // only `Universe` can create an `EntityFactory`.
                EntityFactory(ylikuutio::ontology::Universe* const universe);

                ylikuutio::ontology::Universe* universe;
        };
    }
}

#endif
