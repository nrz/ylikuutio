#ifndef __SYMBIOSIS_HPP_INCLUDED
#define __SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `Material`s and 2 or more `Species` bound to these `Material`s.
// Symbiont `Species` use the same `Shader`. In the future, a new class `ShaderSymbiosis` may be crated should need for such class arise.
// `ShaderSymbiosis` is like `Symbiosis`, but it contains also `Shader`s in addition to `Material`s and `Species`.

#include "entity.hpp"
#include "symbiont_species.hpp"
#include "symbiosis_struct.hpp"
#include "symbiont_species_struct.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include <ofbx.h>

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Shader;
    class SymbiontMaterial;
    class SymbiontSpecies;

    class Symbiosis: public ontology::Entity
    {
        public:
            // constructor.
            Symbiosis(const SymbiosisStruct& symbiosis_struct)
                : Entity(symbiosis_struct.parent->universe)
            {
                // constructor.
                this->parent = symbiosis_struct.parent;

                this->number_of_symbiont_materials = 0;

                // get `childID` from `Shader` and set pointer to this `Symbiosis`.
                this->bind_to_parent();

                if (symbiosis_struct.model_file_format.compare("fbx") == 0 || symbiosis_struct.model_file_format.compare("FBX") == 0)
                {
                    // TODO: write the FBX symbiosis loading code!
                    std::vector<unsigned char> data_vector = file::binary_slurp(symbiosis_struct.model_filename);

                    // OpenFBX wants `u8` == `unsigned char`.
                    const u8* data = reinterpret_cast<const u8*>(data_vector.data());
                    int size = data_vector.size();
                    ofbx::IScene* ofbx_iscene = ofbx::load(data, size);

                    if (ofbx_iscene == nullptr)
                    {
                        std::cerr << "Error: ofbx_iscene is nullptr!\n";
                        return;
                    }

                    int32_t mesh_count = static_cast<int32_t>(ofbx_iscene->getMeshCount()); // `getMeshCount()` returns `int`.

                    for (int32_t mesh_i = 0; mesh_i < mesh_count; mesh_i++)
                    {
                        const ofbx::Mesh* mesh = ofbx_iscene->getMesh(mesh_i);

                        if (mesh == nullptr)
                        {
                            std::cerr << "Error: mesh is nullptr!\n";
                            continue;
                        }

                        const ofbx::Geometry* geometry = mesh->getGeometry();

                        if (geometry == nullptr)
                        {
                            std::cerr << "Error: geometry is nullptr!\n";
                            continue;
                        }

                        int material_count = mesh->getMaterialCount(); // TODO: use this in  `ontology::Symbiosis` entities!
                        std::cout << symbiosis_struct.model_filename << ": mesh " << mesh_i << ": getMaterialCount(): " << material_count << "\n";

                        int vertex_count = geometry->getVertexCount();
                        std::cout << symbiosis_struct.model_filename << ": mesh " << mesh_i << ": getVertexCount(): " << vertex_count << "\n";

                        if (vertex_count <= 0)
                        {
                            std::cerr << "Error: vertex count is <= 0 !\n";
                            continue;
                        }

                        const ofbx::Vec3* vertices = geometry->getVertices();

                        if (vertices == nullptr)
                        {
                            std::cerr << "Error: vertices is nullptr!\n";
                            continue;
                        }

                        const ofbx::Vec3* normals = geometry->getNormals();

                        if (normals == nullptr)
                        {
                            std::cerr << "Error: normals is nullptr!\n";
                            continue;
                        }

                        const ofbx::Vec2* uvs = geometry->getUVs();

                        if (uvs == nullptr)
                        {
                            std::cerr << "Error: uvs is nullptr!\n";
                            continue;
                        }
                    }
                }
                else
                {
                    std::cerr << "no model was loaded!\n";
                    std::cerr << "model file format: " << symbiosis_struct.model_file_format << "\n";
                }

                // TODO: Compute the graph of each type to enable object vertex modification!

                this->type = "ontology::Symbiosis*";
            }

            // destructor.
            virtual ~Symbiosis();

            // this method renders all `SymbiontMaterial`s belonging to this `Symbiosis`.
            void render();

            int32_t get_number_of_children() override;

            int32_t get_number_of_descendants() override;

            void set_symbiont_material_pointer(const int32_t childID, ontology::SymbiontMaterial* const child_pointer);

            // this method sets pointer to this `Symbiosis` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
            void bind_to_new_parent(ontology::Shader* new_shader_pointer);

            void set_name(std::string name);

            friend class SymbiontSpecies;
            friend class SymbiontMaterial;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            ontology::Shader* parent; // pointer to `Scene`.

            std::vector<ontology::SymbiontMaterial*> symbiont_material_pointer_vector;
            std::queue<int32_t> free_symbiont_materialID_queue;
            int32_t number_of_symbiont_materials;
    };
}

#endif
