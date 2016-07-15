#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

#include "cpp/ylikuutio/common/globals.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

// `World`, `Scene`, `Shader`, `Material`, `Species`, `Object`.
// `World`, `Scene`, `Shader`, `Material`, `VectorFont`, `Glyph`, `Object`.
// `World` must be created before any `Scene`. `parent_pointer` must be given to each `Scene`.
// `Scene` must be created before any `Shader`. `parent_pointer` must be given to each `Shader`.
// `Shader` must be created before any `Material`. `parent_pointer` must be given to each `Material`.
// `Material` must be created before any `Species`. `parent_pointer` must be given to each `Species`.
// `Species` must be create before any `Object` of that `Species`. `parent_pointer` must be given to each `Object` of the `Species`.
//
//
// Hierarchy of regular objects (including terrain species):
//
//     World
//       ^
//     Scene
//       ^
//     Shader
//       ^
//    Material
//       ^
//    Species
//       ^
//     Object
//
// Please note that for regular objects the hierarchy above is both the ontological hierarchy and the rendering hierarchy.
//
// Ontological hierarchy of glyph (character) objects:
//
//     World
//       ^
//     Scene
//       ^
//     Shader
//       ^
//    Material
//       ^
//   VectorFont < Glyph
//       ^
//     Text3D
//       ^
//     Object
//
// Ontological hierarchy affects how objects can be created and how they can be destroyed,
// though the precise ways how objects can be created depends on the functions available.
//
// Rendering hierarchy of glyph (character) objects:
//
//     World
//       ^
//     Scene
//       ^
//     Shader
//       ^
//    Material
//       ^
//   VectorFont
//       ^
//     Glyph
//       ^
//     Object
//
// Please note that rendering hierarchy does not include `Text3D` at all, as each `Glyph` points directly to `VectorFont`.
// So, `render_species_or_glyph` is called only once for each glyph, and that call renders all the children of that `Glyph`,
// even if the children (which are of type `Object`) may belong to many different `Text3D` objects.
// `Text3D` is anyway needed in the ontological hierarchy, so that complete 3D texts can be destroyed and manipulated at once.
//
// Deleting a `World` also deletes all scenes, all shaders, materials, species, fonts, glyphs and objects that are binded to the same World.
// Deleting a `Scene` also deletes all shaders, materials, species, fonts, glyphs and objects that are binded to the same World.
// Deleting a `Shader` also deletes all materials, species, fonts, glyphs and objects that are binded to the same Shader.
// Deleting a `Material` also deletes all species, fonts, glyphs and objects that are binded to the same Material.
// Deleting a `Species` also deletes all objects that are binded to the same Species.
// Deleting an `Object` only deletes the object.

// Characteristics of object type graphs:
// 1. Each object must be an undirected graph.
// 2. Each edge must be a link in the graph.
// 3. The faces of each object must form a closed surface. The only exception is the terrain object, which may have borders.
//
// Modifying object type graphs:
// 1. Translation of a vertex does not require changes in any other nodes of the graph.
// 2. Adding a vertex always requires changes in some other nodes of the graph (unless the graph is empty before adding the vertex).
// 3. Deleting a vertex always requires deletion of edges from some other nodes of the graph (unless the vertex is the only vertex of the graph).
// 4. Deleting a vertex or vertices usually also requires appropriate vertex additions. These changes are called 'complex modifications'.
//
// Adding a vertex or several vertices:
// 1. The new edges must be connected to the existing graph with appropriate links.
// 2. Each new face must be a triangle.
//
// Deleting a vertex or several vertices:
// 1. When a vertex or several vertices are deleted, their links must be deleted too (`Node` destructor handles this).
// 2. If the vertex to be deleted is on the border of a [terrain] object, it can be deleted.
// 3. If the vertices that are neighbors to the vertex to be deleted form only triangeles, the vertex can be deleted without vertex additions.
// 4. Otherwise the vertex cannot be deleted without appropriate vertex and edge additions.
//
// Complex modifications:
// 1. In complex modifications one or more vertices and edges are deleted and one or more vertices and edges are added.
// 2. Complex modifications may also change the topology of the object (tunnels, arcs, etc.).
// 3. If a complex modification causes splitting the object in two or more pieces, each piece becomes a separate object.
// 4. If the splitted object is a terrain object, then the lowest vertex (any vertex with smallest y-coordinate) of each piece is searched and the
//    y-coordinates of these are compared. The piece with the smallest y-coordinate (lowest altitude) remains terrain, other pieces become
//    regular objects. The pieces that become regular objects will be subject to gravity the same way as any regular object.

namespace ontology
{
    class Scene;
    class Shader;

    class World
    {
        public:
            // constructor.
            World();

            // destructor.
            ~World();

            // this method renders the entire world, one scene at a time.
            void render();

            friend class Scene;
            friend class Shader;
            friend class Species;

        private:
            // this method sets a scene pointer.
            void set_scene_pointer(uint32_t childID, void* parent_pointer);

            // this method sets a world species pointer.
            void set_terrain_species_pointer(ontology::Species* terrain_species_pointer);

            void compute_matrices_from_inputs();

            void* terrain_species_pointer;              // pointer to world species (used in collision detection).

            std::vector<void*> scene_pointer_vector;
            std::queue<uint32_t> free_sceneID_queue;
    };
}

#endif
