#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

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
#include <unordered_map> // std::unordered_map
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

// `Universe`, `Scene`, `Shader`, `Material`, `Species`, `Object`.
// `Universe`, `Scene`, `Shader`, `Material`, `VectorFont`, `Glyph`, `Object`.
// `Universe` must be created before any `Scene`. `parent_pointer` must be given to each `Scene`.
// `Scene` must be created before any `Shader`. `parent_pointer` must be given to each `Shader`.
// `Shader` must be created before any `Material`. `parent_pointer` must be given to each `Material`.
// `Material` must be created before any `Species`. `parent_pointer` must be given to each `Species`.
// `Species` must be create before any `Object` of that `Species`. `parent_pointer` must be given to each `Object` of the `Species`.
//
//
// Hierarchy of regular `Object`s (including terrain species):
//
//    Universe
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
// Please note that for regular `Object`s the hierarchy above is both the ontological hierarchy and the rendering hierarchy.
//
// Ontological hierarchy of `Glyph` (character) objects:
//
//    Universe
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
// Rendering hierarchy of `Glyph` (character) objects:
//
//    Universe
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
// Ontological hierarchy of `Symbiosis` objects:
//
//    Universe
//       ^
//     Scene
//       ^
//   Symbiosis
//       ^
//     Shader
//       ^
//    Material
//       ^
//    Species
//       ^
//     Object
//
// Ontological hierarchy affects how objects can be created and how they can be destroyed,
// though the precise ways how objects can be created depends on the functions available.
//
// Rendering hierarchy of `Symbiosis` objects:
//
//    Universe
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
// Please note that `Symbiosis` is ignored completely in rendering hierarchy.
//
// Deleting a `Universe` also deletes all scenes, all shaders, materials, species, fonts, glyphs and objects that are bound to the same `Universe`.
// Deleting a `Scene` also deletes all shaders, materials, species, fonts, glyphs and objects that are bound to the same `Universe`.
// Deleting a `Shader` also deletes all materials, species, fonts, glyphs and objects that are bound to the same `Shader`.
// Deleting a `Material` also deletes all species, fonts, glyphs and objects that are bound to the same `Material`.
// Deleting a `Species` also deletes all objects that are bound to the same `Species`.
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

namespace config
{
    class Setting;
    class SettingMaster;
}

namespace console
{
    class Console;
}

namespace ontology
{
    class Scene;
    class Shader;
    class Object;

    class Universe: public ontology::Entity
    {
        public:
            // constructor.
            Universe();

            // destructor.
            ~Universe();

            // this method renders the active `Scene` of this `Universe`.
            void render();

            // this method sets a new `window`.
            void set_window(GLFWwindow* window);

            // this method returns current `window`.
            GLFWwindow* get_window();

            // this method returns current `window_width`.
            uint32_t get_window_width();

            // this method returns current `window_height`.
            uint32_t get_window_height();

            // this method returns current `text_size`.
            uint32_t get_text_size();

            // this method returns current `font_size`.
            uint32_t get_font_size();

            // this method computes the new delta time and returns it.
            float compute_delta_time();

            // this method returns the last computed delta time.
            float get_delta_time();

            // this method stores `current_time_before_reading_keyboard` into `last_time_before_reading_keyboard`.
            void finalize_delta_time_loop();

            // this method returns current `max_FPS`.
            uint32_t get_max_FPS();

            // this method computes new location and orientation.
            void compute_new_location_and_orientation();

            bool set(std::string& setting_name, datatypes::AnyValue* setting_any_value);

            // this method returns a pointer to `config::Setting` corresponding to the given `key`.
            config::Setting* get(std::string key);

            // this method returns a pointer to `datatypes::AnyValue` corresponding to the given `key`.
            datatypes::AnyValue* get_value(std::string key);

            // Public callbacks.

            static datatypes::AnyValue* delete_entity(
                    console::Console* console,
                    ontology::Universe* universe,
                    std::vector<std::string>& command_parameters);

            static datatypes::AnyValue* info(
                    console::Console* console,
                    ontology::Universe* universe,
                    std::vector<std::string>& command_parameters);

            // Public callbacks end here.

            friend class Scene;
            friend class Shader;
            friend class Material;
            friend class Species;
            friend class Object;
            friend class VectorFont;
            friend class Glyph;
            friend class Text3D;
            friend class Font2D;
            friend class config::Setting;
            friend class config::SettingMaster;
            friend class console::Console;

            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);

        private:
            // this method sets a `Scene` pointer.
            void set_scene_pointer(uint32_t childID, ontology::Scene* child_pointer);

            // this method stes the active `Scene`.
            void set_active_scene(ontology::Scene* scene);

            // this method sets a terrain `Species` pointer.
            void set_terrain_species_pointer(ontology::Species* terrain_species_pointer);

            bool compute_matrices_from_inputs();

            void* terrain_species_pointer;              // pointer to terrain `Species` (used in collision detection).

            float world_radius;

            std::vector<ontology::Scene*> scene_pointer_vector;
            std::queue<uint32_t> free_sceneID_queue;
            ontology::Scene* active_scene;

            config::SettingMaster* setting_master_pointer; // pointer to `SettingMaster`.
            console::Console* console_pointer;             // pointer to `Console`.

            // Named entities are stored here so that they can be recalled, if needed.
            std::unordered_map<std::string, datatypes::AnyValue*> entity_anyvalue_map;

            GLclampf background_red;
            GLclampf background_green;
            GLclampf background_blue;
            GLclampf background_alpha;

            // Variables related to the window.
            GLFWwindow* window;
            uint32_t window_width;
            uint32_t window_height;

            // Variables related to the camera.
            glm::vec3 camera_position;
            glm::mat4 ProjectionMatrix;
            glm::mat4 ViewMatrix;
            GLfloat aspect_ratio;
            GLfloat initialFoV;

            // Variables related to the fonts and texts used.
            uint32_t text_size;
            uint32_t font_size;

            // Variables related to timing of events.
            uint32_t max_FPS;
            float delta_time;

            double last_time_before_reading_keyboard;
            double current_time_before_reading_keyboard;

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3 cartesian_coordinates;
            double x;
            double y;
            double z;

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction;
            float pitch;
            float roll;
            float yaw;

            glm::vec3 right; // note: `right` can not be set directly using console.
            glm::vec3 up;    // note: `up` can not be set directly using console.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            SphericalCoordinatesStruct* spherical_coordinates;
            double rho;
            double theta;
            double phi;

            double horizontal_angle;
            double vertical_angle;

            float speed;
            float turbo_factor;
            float twin_turbo_factor;
            float mouse_speed;
            bool has_mouse_ever_moved;
            bool can_toggle_invert_mouse;
            bool is_invert_mouse_in_use;
            bool can_toggle_flight_mode;
            bool is_flight_mode_in_use;
            bool is_first_turbo_pressed;
            bool is_second_turbo_pressed;

            // Variables related to the current `Scene`.
            bool testing_spherical_world_in_use;

            // Variables related to debug & testing keys.
            bool is_key_I_released;
            bool is_key_F_released;

            // Variables related to help mode.
            bool in_help_mode;
            bool can_toggle_help_mode;
            bool can_display_help_screen;
    };
}

#endif
