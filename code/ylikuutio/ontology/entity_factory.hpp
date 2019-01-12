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

// Include standard headers
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace yli
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
                // constructor.
                EntityFactory(yli::ontology::Universe* const universe);

                // destructor.
                ~EntityFactory();

                yli::ontology::Universe* get_universe() const;

                yli::ontology::Entity* create_World() const;
                yli::ontology::Entity* create_Scene(yli::ontology::World* const world, const float water_level);
                yli::ontology::Entity* create_Shader(const ShaderStruct& shader_struct);
                yli::ontology::Entity* create_Material(const MaterialStruct& material_struct);
                yli::ontology::Entity* create_Species(const SpeciesStruct& species_struct);
                yli::ontology::Entity* create_Object(ObjectStruct& object_struct);
                yli::ontology::Entity* create_Symbiosis(const SymbiosisStruct& symbiosis_struct);
                yli::ontology::Entity* create_Holobiont(HolobiontStruct& object_struct);
                yli::ontology::Entity* create_VectorFont(const VectorFontStruct& vector_font_struct);
                yli::ontology::Entity* create_Text3D(Text3DStruct& text3D_struct);
                yli::ontology::Entity* create_Font2D(
                        std::size_t screen_width,
                        std::size_t screen_height,
                        const std::string& texture_filename,
                        const std::string& font_texture_file_format);
                yli::ontology::Entity* create_Camera(CameraStruct& camera_struct);

                friend class Universe;

            private:
                yli::ontology::Universe* universe;
        };
    }
}

#endif
