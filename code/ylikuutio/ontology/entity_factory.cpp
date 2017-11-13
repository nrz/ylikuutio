#include "entity_factory.hpp"
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
    EntityFactory::EntityFactory()
    {
        // constructor.
        this->universe = nullptr;
        this->setting_master = nullptr;
    }

    EntityFactory::~EntityFactory()
    {
        // destructor.
    }

    void EntityFactory::set_universe(ontology::Universe* universe)
    {
        this->universe = universe;
    }

    ontology::Universe* EntityFactory::get_universe()
    {
        return this->universe;
    }

    void EntityFactory::set_setting_master(config::SettingMaster* setting_master)
    {
        this->setting_master = setting_master;
    }

    config::SettingMaster* EntityFactory::get_setting_master()
    {
        return this->setting_master;
    }

    ontology::Entity* EntityFactory::create_Universe()
    {
        return new ontology::Universe();
    }

    ontology::Entity* EntityFactory::create_Scene(const float water_level)
    {
        return new ontology::Scene(this->universe, water_level);
    }

    ontology::Entity* EntityFactory::create_Shader(const ShaderStruct& shader_struct)
    {
        return new ontology::Shader(this->universe, shader_struct);
    }

    ontology::Entity* EntityFactory::create_Material(const MaterialStruct& material_struct)
    {
        return new ontology::Material(this->universe, material_struct);
    }

    ontology::Entity* EntityFactory::create_Species(const SpeciesStruct& species_struct)
    {
        return new ontology::Species(this->universe, species_struct);
    }

    ontology::Entity* EntityFactory::create_Object(const ObjectStruct& object_struct)
    {
        return new ontology::Object(this->universe, object_struct);
    }

    ontology::Entity* EntityFactory::create_VectorFont(const VectorFontStruct& vector_font_struct)
    {
        return new ontology::VectorFont(this->universe, vector_font_struct);
    }

    ontology::Entity* EntityFactory::create_Text3D(const Text3DStruct& text3D_struct)
    {
        return new ontology::Text3D(this->universe, text3D_struct);
    }

    ontology::Entity* EntityFactory::create_Font2D(
            ontology::Universe* const universe,
            GLuint screen_width,
            GLuint screen_height,
            const std::string& texture_filename,
            const std::string& font_texture_file_format)
    {
        return new ontology::Font2D(
                universe,
                universe->get_window_width(),
                universe->get_window_height(),
                texture_filename.c_str(),
                font_texture_file_format.c_str());
    }
}
