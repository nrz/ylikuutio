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
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace config
{
    class SettingMaster;
}

namespace ontology
{
    class EntityFactory
    {
        public:
            // constructor.
            EntityFactory();

            // destructor.
            ~EntityFactory();

            void set_universe(ontology::Universe* universe);
            ontology::Universe* get_universe();

            void set_setting_master(config::SettingMaster* setting_master);
            config::SettingMaster* get_setting_master();

            ontology::Entity* create_Universe();
            ontology::Entity* create_Scene(ontology::Universe* const universe, const float water_level);
            ontology::Entity* create_Shader(const ShaderStruct& shader_struct);
            ontology::Entity* create_Material(const MaterialStruct& material_struct);
            ontology::Entity* create_Species(const SpeciesStruct& species_struct);
            ontology::Entity* create_Object(const ObjectStruct& object_struct);
            ontology::Entity* create_VectorFont(const VectorFontStruct& vector_font_struct);
            ontology::Entity* create_Text3D(const Text3DStruct& text3D_struct);
            ontology::Entity* create_Font2D(
                    ontology::Universe* const universe,
                    GLuint screen_width,
                    GLuint screen_height,
                    const std::string& texture_filename,
                    const std::string& font_texture_file_format);

        private:
            ontology::Universe* universe;
            config::SettingMaster* setting_master;
    };
}

#endif
