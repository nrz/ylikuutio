#ifndef __UNIVERSE_HPP_INCLUDED
#define __UNIVERSE_HPP_INCLUDED

#include "entity.hpp"
#include "entity_factory.hpp"
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
#include <GLFW/glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <unordered_map> // std::unordered_map
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

// `Universe`, `Scene`, `Shader`, `Material`, `Species`, `Object`.
// `Universe`, `Scene`, `Shader`, `Material`, `VectorFont`, `Glyph`, `Object`.
// `Universe` must be created before any `Scene`. `parent` must be given to each `Scene`.
// `Scene` must be created before any `Shader`. `parent` must be given to each `Shader`.
// `Shader` must be created before any `Material`. `parent` must be given to each `Material`.
// `Material` must be created before any `Species`. `parent` must be given to each `Species`.
// `Species` must be create before any `Object` of that `Species`. `parent` must be given to each `Object` of the `Species`.
//
//
// Hierarchy of regular `Object`s (including terrain species):
//
//    Universe
//       ^
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
// Please note that for regular `Object`s the hierarchy above is both the ontological hierarchy and the rendering hierarchy.
//
// Ontological hierarchy of `Glyph` (character) objects:
//
//    Universe
//       ^
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
// Rendering hierarchy of `Glyph` (character) objects:
//
//    Universe
//       ^
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
// Ontological hierarchy of `Symbiosis` objects:
//
//    Universe
//       ^
//     World
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
// Please note that `Symbiosis` is ignored completely in rendering hierarchy.
//
// Deleting a `Universe` also deletes all worlds, scenes, all shaders, materials, species, fonts, glyphs and objects that are bound to the same `Universe`.
// Deleting a `World` also deletes all scenes, all shaders, materials, species, fonts, glyphs and objects that are bound to the same `World`.
// Deleting a `Scene` also deletes all shaders, materials, species, fonts, glyphs and objects that are bound to the same `Scene`.
// Deleting a `Shader` also deletes all materials, species, fonts, glyphs and objects that are bound to the same `Shader`.
// Deleting a `Material` also deletes all species, fonts, glyphs and objects that are bound to the same `Material`.
// Deleting a `Species` also deletes all objects that are bound to the same `Species`.
// Deleting an `Object` only deletes the object.

// Characteristics of object type graphs: TODO: implement object type graphs!
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
    class World;
    class Scene;
    class Species;

    class Universe: public ontology::Entity
    {
        public:
            // constructor.
            Universe()
                : Entity(nullptr) // `Universe` has no parent.
            {
                this->entity_factory = new ontology::EntityFactory(this);

                this->cartesian_coordinates = nullptr;
                this->spherical_coordinates = nullptr;

                this->planet_radius = NAN; // world radius is NAN as long it doesn't get `set` by `SettingMaster`.
                this->terrain_species = nullptr;
                this->active_world = nullptr;
                this->console_pointer = nullptr;

                this->background_red = NAN;
                this->background_green = NAN;
                this->background_blue = NAN;
                this->background_alpha = NAN;

                // Variables related to the window.
                this->window = nullptr;
                this->window_width = 1600; // default width.
                this->window_height = 900; // default height.

                this->ProjectionMatrix = glm::mat4(1.0f); // identity matrix (dummy value).
                this->ViewMatrix = glm::mat4(1.0f);       // identity matrix (dummy value).

                // Variables related to the camera.
                this->aspect_ratio = static_cast<GLfloat>(this->window_width / this->window_height);
                this->initialFoV = 60.0f;

                this->text_size = 40; // default text size.
                this->font_size = 16; // default font size.

                this->max_FPS = 60; // default value max 60 frames per second.
                this->delta_time = NAN;
                this->last_time_before_reading_keyboard = NAN;
                this->current_time_before_reading_keyboard = NAN;

                this->has_mouse_ever_moved = false;
                this->can_toggle_invert_mouse = false;
                this->is_invert_mouse_in_use = false;
                this->can_toggle_flight_mode = false;
                this->is_flight_mode_in_use = false;
                this->is_first_turbo_pressed = false;
                this->is_second_turbo_pressed = false;

                this->horizontal_angle = NAN;
                this->vertical_angle = NAN;
                this->turbo_factor = NAN;
                this->twin_turbo_factor = NAN;

                this->speed = 5.0f; // 5.0 units / second
                this->mouse_speed = 0.005f;

                this->gravity = 9.81f / 60.0f;
                this->fall_speed = this->gravity;

                this->testing_spherical_terrain_in_use = false;
                this->is_key_I_released = true;
                this->is_key_F_released = true;
                this->in_help_mode = true;
                this->can_toggle_help_mode = false;
                this->can_display_help_screen = true;

                this->number_of_worlds = 0;

                this->child_vector_pointers_vector.push_back(&this->world_pointer_vector);
                this->type = "ontology::Universe*";
            }

            // destructor.
            virtual ~Universe();

            void bind(ontology::World* world);

            // this method renders the active `Scene` of this `Universe`.
            void render();

            // this method stes the active `World`.
            void set_active_world(ontology::World* world);

            // this method stes the active `Scene`.
            void set_active_scene(ontology::Scene* world);

            config::SettingMaster* get_setting_master() const;

            console::Console* get_console() const;
            void set_console(console::Console* console);

            float get_planet_radius() const;
            void set_planet_radius(float planet_radius);

            // this method sets a `World` pointer.
            void set_world_pointer(int32_t childID, ontology::World* child_pointer);

            // this method sets a terrain `Species` pointer.
            void set_terrain_species(ontology::Species* terrain_species);

            glm::mat4& get_projection_matrix();
            glm::mat4& get_view_matrix();

            int32_t get_number_of_worlds() const;

            ontology::World* get_active_world() const;

            ontology::Universe* get_universe() final override;
            ontology::Entity* get_parent() const override;
            int32_t get_number_of_children() const override;
            int32_t get_number_of_descendants() const override;

            // this method sets a new `window`.
            void set_window(GLFWwindow* window);

            // this method returns current `window`.
            GLFWwindow* get_window() const;

            // this method returns current `window_width`.
            int32_t get_window_width() const;

            // this method returns current `window_height`.
            int32_t get_window_height() const;

            // this method returns current `text_size`.
            int32_t get_text_size() const;

            // this method returns current `font_size`.
            int32_t get_font_size() const;

            // this method computes the new delta time and returns it.
            float compute_delta_time();

            // this method returns the last computed delta time.
            float get_delta_time() const;

            // this method stores `current_time_before_reading_keyboard` into `last_time_before_reading_keyboard`.
            void finalize_delta_time_loop();

            // this method returns current `max_FPS`.
            uint32_t get_max_FPS() const;

            void set(std::string& setting_name, std::shared_ptr<datatypes::AnyValue> setting_any_value);

            // this method returns a pointer to `config::Setting` corresponding to the given `key`.
            config::Setting* get(std::string key) const;

            bool is_entity(const std::string& name) const;
            ontology::Entity* get_entity(const std::string& name) const;
            std::string get_entity_names() const;

            void add_entity(const std::string& name, ontology::Entity* const entity);
            void erase_entity(const std::string& name);

            ontology::EntityFactory* get_entity_factory() const;

            // Public callbacks.

            static std::shared_ptr<datatypes::AnyValue> delete_entity(
                    console::Console* const console,
                    ontology::Entity* const entity,
                    std::vector<std::string>& command_parameters);

            static std::shared_ptr<datatypes::AnyValue> activate(
                    console::Console* const console,
                    ontology::Entity* const universe_entity,
                    std::vector<std::string>& command_parameters);

            static std::shared_ptr<datatypes::AnyValue> info(
                    console::Console* const console,
                    ontology::Entity* const entity,
                    std::vector<std::string>& command_parameters);

            // Public callbacks end here.

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3* cartesian_coordinates;

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            SphericalCoordinatesStruct* spherical_coordinates;

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction;

            glm::vec3 right; // note: `right` can not be set directly using console.
            glm::vec3 up;    // note: `up` can not be set directly using console.

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

            // Variables related to physics.
            float gravity;
            float fall_speed;

            // Variables related to the current `Scene`.
            bool testing_spherical_terrain_in_use;

            // Variables related to debug & testing keys.
            bool is_key_I_released;
            bool is_key_F_released;

            // Variables related to help mode.
            bool in_help_mode;
            bool can_toggle_help_mode;
            bool can_display_help_screen;

        private:
            bool compute_matrices_from_inputs();

            void* terrain_species;               // pointer to terrain `Species` (used in collision detection).

            float planet_radius;

            ontology::EntityFactory* entity_factory;

            std::vector<ontology::World*> world_pointer_vector;
            std::queue<int32_t> free_worldID_queue;
            int32_t number_of_worlds;

            ontology::World* active_world;

            console::Console* console_pointer;     // pointer to `Console`.

            // Named entities are stored here so that they can be recalled, if needed.
            std::unordered_map<std::string, ontology::Entity*> entity_map;

            GLclampf background_red;
            GLclampf background_green;
            GLclampf background_blue;
            GLclampf background_alpha;

            // Variables related to the window.
            GLFWwindow* window;
            int32_t window_width;
            int32_t window_height;

            // Variables related to the camera.
            glm::mat4 ProjectionMatrix;
            glm::mat4 ViewMatrix;
            GLfloat aspect_ratio;
            GLfloat initialFoV;

            // Variables related to the fonts and texts used.
            int32_t text_size;
            int32_t font_size;

            // Variables related to timing of events.
            uint32_t max_FPS;
            float delta_time;

            double last_time_before_reading_keyboard;
            double current_time_before_reading_keyboard;
    };
}

#endif
