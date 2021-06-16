// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __YLIKUUTIO_ONTOLOGY_UNIVERSE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_UNIVERSE_HPP_INCLUDED

#include "entity.hpp"
#include "parent_module.hpp"
#include "framebuffer_module.hpp"
#include "entity_factory.hpp"
#include "universe_struct.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/input/input_master.hpp"
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_master_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/time/time.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <string>        // std::string
#include <vector>        // std::vector

// The ontological hierachy of Ylikuutio is based on composition.
//
// Each ontological class inherits `yli::ontology::Entity` either directly or indirectly.
// See `doc/class_diagram.tex` for a partial class diagram.
// Inheriting `yli::ontology::Entity` enables the use of virtual functions common for all ontological entities.
//
// The recommended way to create entities in a game or simulation is to first create `yli::ontology::Universe`
// and then get a `yli::ontology::EntityFactory*` pointer using `Universe::get_entity_factory` and then
// create all the rest entities using the member functions of that `EntityFactory`.
//
// There is no support for multiple simultaneous `Universe` entities. Do not create more than 1 `Universe`.
//
// `Universe`, `Scene`, `Shader`, `Material`, `Species`, `Object`.
// `Universe`, `Scene`, `Shader`, `Material`, `VectorFont`, `Glyph`, `Object`.
// `Universe` must be created before any `Scene`. `parent` must be given to each `Scene`.
// `Scene` must be created before any `Shader`. `parent` must be given to each `Shader`.
// `Shader` must be created before any `Material`. `parent` must be given to each `Material`.
// `Material` must be created before any `Species`. `parent` must be given to each `Species`.
// `Species` must be create before any `Object` of that `Species`. `parent` must be given to each `Object` of the `Species`.
//
//
// Hierarchy of regular `Object`s (including terrain `Species`):
//
//    Universe
//       ^
//     Scene
//       ^
//     Shader
//       ^
//    Material
//       ^
//    Species : Model
//       ^
//     Object : Movable
//
// Please note that for regular `Object`s the hierarchy above is both the ontological hierarchy and the rendering hierarchy.
//
// Ontological hierarchy of `Glyph` (character) entities:
//
//    Universe
//       ^
//     Scene
//       ^
//     Shader
//       ^
//    Material
//       ^
//   VectorFont < Glyph : Model
//       ^
//     Text3D
//       ^
//     Object : Movable
//
// Ontological hierarchy affects how objects can be created and how they can be destroyed,
// though the precise ways how objects can be created depends on the functions available.
//
// Rendering hierarchy of `Glyph` (character) entities:
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
//     Glyph : Model
//       ^
//     Object : Movable
//
// Please note that rendering hierarchy does not include `Text3D` at all, as each `Glyph` points directly to `VectorFont`.
// So, `render_species_or_glyph` is called only once for each glyph, and that call renders all the children of that `Glyph`,
// even if the children (which are of type `Object`) may belong to many different `Text3D` objects.
// `Text3D` is anyway needed in the ontological hierarchy, so that complete 3D texts can be destroyed and manipulated at once.
//
// Ontological hierarchy of `Symbiosis` entities:
//
//    Universe
//       ^
//     Scene
//       ^
//     Shader
//       ^
//   Symbiosis : Entity  < SymbiontMaterial : Material
//       ^                        ^
//   Holobiont : Movable   SymbiontSpecies : Species
//       ^
//     Biont : Movable
//
// Each `Holobiont` is a composite organism which consists of 0 more `Bionts`.
// The `Biont`s of the `Holobiont` each belong to their corresponding
// `SymbiontSpecies`.
//
// For more information about holobionts, check Wikipedia:
// https://en.wikipedia.org/wiki/Holobiont
//
// Ontological hierarchy affects how objects can be created and how they can be destroyed,
// though the precise ways how objects can be created depends on the functions available.
//
// Rendering hierarchy of `Symbiosis` entities:
//
//    Universe
//       ^
//     Scene
//       ^
//     Shader
//       ^
//   Symbiosis : Entity  > SymbiontMaterial : Material
//       ^                        v
//   Holobiont : Movable   SymbiontSpecies : Species
//       ^
//     Biont : Movable
//
// Optimized rendering hierarchy of `Symbiosis` entities:
//
//      Universe
//         ^
//       Scene
//         ^
//       Shader
//         ^
//     Symbiosis
//         ^
//  SymbiontMaterial : Material
//         ^
//  SymbiontSpecies : Species
//         ^
//       Biont : Movable
//
// TODO: implement optimized rendering hierarchy for `Symbiosis` entities!
//
// Ontological hierarchy of `ShaderSymbiosis` entities:
//
//      Universe
//         ^
//       Scene
//         ^
//  ShaderSymbiosis : Symbiosis < SymbiontShader : Shader
//         ^                            ^
//     Holobiont : Movable       SymbiontMaterial : Material
//         ^                            ^
//       Biont : Movable         SymbiontSpecies : Species
//
// Rendering hierarchy of `ShaderSymbiosis` entities:
//
//      Universe
//         ^
//       Scene
//         ^
//  ShaderSymbiosis : Symbiosis  > SymbiontShader : Shader
//         ^                             v
//     Holobiont : Movable        SymbiontMaterial : Material
//         ^                             v
//       Biont : Movable          SymbiontSpecies : Species
//
// TODO: implement `ShaderSymbiosis` entities!
//
// Optimized rendering hierarchy of `ShaderSymbiosis` entities:
//
//      Universe
//         ^
//       Scene
//         ^
//  ShaderSymbiosis
//         ^
//   SymbiontShader : Shader
//         ^
//  SymbiontMaterial : Material
//         ^
//  SymbiontSpecies : Species
//         ^
//       Biont : Movable
//
// TODO: implement optimized rendering hierarchy for `ShaderSymbiosis` entities!
//
// Deleting a `Universe` also deletes all worlds, scenes, all shaders, materials, species, fonts, glyphs and objects that are bound to the same `Universe`.
// Deleting a `World` also deletes all shaders, materials, species, fonts and glyphs that are bound to the same `World`.
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

namespace yli::data
{
    class AnyValue;
}

namespace yli::input
{
    enum class InputMethod;
}

namespace yli::render
{
    struct RenderStruct;
}

namespace yli::ontology
{
    class Scene;
    class Camera;
    class Font2D;
    class Console;

    class Universe: public yli::ontology::Entity
    {
        public:
            void bind_entity(yli::ontology::Entity* const entity);
            void unbind_entity(const std::size_t entityID);

            Universe(const yli::ontology::UniverseStruct& universe_struct)
                : Entity(this, universe_struct), // `Universe` has no parent.
                parent_of_worlds(this, &this->registry, "worlds"),
                parent_of_scenes(this, &this->registry, "scenes"),
                parent_of_font_2ds(this, &this->registry, "font_2ds"),
                parent_of_consoles(this, &this->registry, "consoles"),
                parent_of_any_value_entities(this, &this->registry, "any_value_entities"),
                parent_of_callback_engine_entities(this, &this->registry, "callback_engine_entities"),
                framebuffer_module(universe_struct.framebuffer_module_struct),
                is_headless { yli::sdl::init_sdl(universe_struct.is_headless) },
                is_silent { this->is_headless || universe_struct.is_silent },
                is_physical { universe_struct.is_physical }
            {
                // constructor.

                // call `bind_entity` here since it couldn't be performed from `Entity` constructor.
                this->bind_entity(this);

                // call `set_global_name` here because it can't be done in `Entity` constructor.
                this->set_global_name(universe_struct.global_name);

                this->current_camera_spherical_coordinates.rho   = NAN; // dummy coordinates.
                this->current_camera_spherical_coordinates.theta = NAN; // dummy coordinates.
                this->current_camera_spherical_coordinates.phi   = NAN; // dummy coordinates.

                // Variables related to the window.
                this->window_width       = universe_struct.window_width;
                this->window_height      = universe_struct.window_height;
                this->application_name   = universe_struct.application_name;
                this->window_title       = universe_struct.window_title;

                if (this->window_title.empty())
                {
                    std::stringstream window_title_stringstream;
                    window_title_stringstream << "Ylikuutio " << yli::ontology::Universe::version;
                    this->window_title = window_title_stringstream.str();
                }

                this->is_fullscreen = universe_struct.is_fullscreen;

                // mouse coordinates.
                this->mouse_x = this->window_width / 2;
                this->mouse_y = this->window_height / 2;

                // Variables related to the camera.
                this->aspect_ratio = static_cast<float>(this->window_width) / static_cast<float>(this->window_height);

                this->text_size = universe_struct.text_size;
                this->font_size = universe_struct.font_size;

                this->max_fps                 = universe_struct.max_fps;

                this->speed                   = universe_struct.speed;
                this->turbo_factor            = universe_struct.turbo_factor;
                this->twin_turbo_factor       = universe_struct.twin_turbo_factor;
                this->mouse_speed             = universe_struct.mouse_speed;

                this->znear                   = universe_struct.znear;
                this->zfar                    = universe_struct.zfar;

                // Set the value of `should_be_rendered` here because it can't be done in `Entity` constructor.
                this->should_be_rendered = !this->get_is_headless();

                this->create_should_be_rendered_variable();

                if (!this->is_silent)
                {
                    this->audio_master = std::make_unique<yli::audio::AudioMaster>(this);
                }

                if (this->is_headless)
                {
                    this->is_exit_requested = true;
                }
                else
                {
                    yli::render::RenderMasterStruct render_master_struct;
                    this->render_master = std::make_unique<yli::render::RenderMaster>(this, render_master_struct);
                    this->input_master = std::make_unique<yli::input::InputMaster>(this);
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Universe*";
            }

            Universe(const Universe&) = delete;            // Delete copy constructor.
            Universe& operator=(const Universe&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Universe();

            // This method contains the main loop.
            void start_simulation();

            // This method requests exit.
            void request_exit();

            // This method processes the physics.
            void do_physics();

            // Intentional actors (AIs and keyboard controlled ones).
            void act();

            // This method renders according to the data given in `render_struct`.
            void render(const yli::render::RenderStruct& render_struct);

            // This method renders the active `Scene` of this `Universe`.
            void render();

            // This method renders the active `Scene` of this `Universe`.
            void render_without_changing_depth_test();

            // This method sets the active `Scene`.
            void set_active_scene(yli::ontology::Scene* const scene);

            // This method sets the active `Camera`.
            // Setting the active `Camera` does not change the active `Scene`!
            void set_active_camera(yli::ontology::Camera* const camera) const;

            yli::ontology::Console* get_active_console() const;
            void set_active_console(yli::ontology::Console* const console);

            yli::input::InputMethod get_input_method() const;

            bool get_is_headless() const;

            std::string eval_string(const std::string& my_string) const;

            yli::render::RenderMaster* get_render_master() const;
            yli::audio::AudioMaster* get_audio_master() const;
            yli::input::InputMaster* get_input_master() const;

            btDefaultCollisionConfiguration* get_collision_configuration() const;
            btCollisionDispatcher* get_dispatcher() const;
            btBroadphaseInterface* get_overlapping_pair_cache() const;
            btSequentialImpulseConstraintSolver* get_solver() const;

            std::size_t get_number_of_worlds() const;
            std::size_t get_number_of_scenes() const;

            yli::ontology::Scene* get_active_scene() const;

            yli::ontology::Entity* get_parent() const override;

            void create_window();
            void setup_context();
            void create_window_and_setup_context();
            void set_swap_interval(const int32_t interval);
            void restore_onscreen_rendering() const;
            void set_opengl_background_color() const;
            void adjust_opengl_viewport() const;

            bool get_is_exit_requested() const;

            // This method returns current `window`.
            SDL_Window* get_window() const;

            // This method returns current `window_width`.
            uint32_t get_window_width() const;

            // This method sets `window_width`.
            void set_window_width(const uint32_t window_width);

            // This method returns current `window_height`.
            uint32_t get_window_height() const;

            // This method sets `window_height`.
            void set_window_height(const uint32_t window_height);

            // This method returns current `text_size`.
            std::size_t get_text_size() const;

            // This method returns current `font_size`.
            std::size_t get_font_size() const;

            // This method computes the new delta time and returns it.
            float compute_delta_time();

            // This method returns the last computed delta time.
            float get_delta_time() const;

            // This method stores `current_time_before_reading_keyboard` into `last_time_before_reading_keyboard`.
            void finalize_delta_time_loop();

            // This method returns current `max_fps`.
            std::size_t get_max_fps() const;
            float get_last_time_to_display_fps() const;
            float get_last_time_for_display_sync() const;
            int32_t get_number_of_frames() const;

            void increment_last_time_to_display_fps();
            void update_last_time_for_display_sync();
            void increment_number_of_frames();
            void reset_number_of_frames();

            yli::ontology::EntityFactory* get_entity_factory() const override;

            const glm::mat4& get_projection_matrix() const;
            void set_projection_matrix(const glm::mat4& projection_matrix);

            const glm::mat4& get_view_matrix() const;
            void set_view_matrix(const glm::mat4& view_matrix);

            float get_aspect_ratio() const;
            float get_initial_fov() const;

            // Public callbacks.

            // Public `Entity` bind callbacks.

            static std::shared_ptr<yli::data::AnyValue> bind(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Entity* const child_or_apprentice_entity,
                    yli::ontology::Entity* const parent_or_master_entity);

            // Public `Entity` create callbacks.

            // Public `Entity` delete callbacks.

            static std::shared_ptr<yli::data::AnyValue> delete_entity(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Entity* const entity);

            // Public `Entity` naming callbacks.

            static std::shared_ptr<yli::data::AnyValue> set_global_name_for_entity(
                    yli::ontology::Entity* const entity,
                    std::shared_ptr<std::string> new_value);

            static std::shared_ptr<yli::data::AnyValue> set_local_name_for_entity(
                    yli::ontology::Entity* const entity,
                    std::shared_ptr<std::string> new_value);

            // Public `Entity` activate callbacks.

            static std::shared_ptr<yli::data::AnyValue> activate_entity(yli::ontology::Entity* const entity);

            // Public YliLisp-related callbacks.

            static std::shared_ptr<yli::data::AnyValue> eval(
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const universe_entity,
                    const std::vector<std::string>& command_parameters);

            // Public data printing callbacks.

            static std::shared_ptr<yli::data::AnyValue> info0(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console);

            static std::shared_ptr<yli::data::AnyValue> info1(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> print_entities(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console);

            static std::shared_ptr<yli::data::AnyValue> print_parent(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const entity);

            // Other public callbacks.

            static std::shared_ptr<yli::data::AnyValue> screenshot(
                    yli::ontology::Universe* const universe,
                    std::shared_ptr<std::string> filename);

            // Public callbacks end here.

            // Ylikuutio version.
            static const std::string version;

            std::string application_name;

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3 current_camera_cartesian_coordinates { glm::vec3(NAN, NAN, NAN) }; // Dummy coordinates.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            yli::data::SphericalCoordinatesStruct current_camera_spherical_coordinates;

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 current_camera_direction;

            glm::vec3 current_camera_right; // note: `right` can not be set directly using console.
            glm::vec3 current_camera_up;    // note: `up` can not be set directly using console.

            float current_camera_yaw   { NAN };
            float current_camera_pitch { NAN };

            int32_t mouse_x;
            int32_t mouse_y;

            float speed;
            float turbo_factor;
            float twin_turbo_factor;
            float mouse_speed;
            bool has_mouse_ever_moved { false };

            // 'can toggle'-type of boolean keypress control variables
            // should all be stored in the `Universe` to avoid locking.
            bool can_toggle_invert_mouse { false };
            bool can_toggle_flight_mode  { false };
            bool can_toggle_help_mode    { false };

            bool is_invert_mouse_in_use  { false };
            bool is_first_turbo_pressed  { false };
            bool is_second_turbo_pressed { false };
            bool is_exit_requested       { false };

            // Variables related to graphics.
            float znear;
            float zfar;

            // Variables related to the current `Scene`.
            bool testing_spherical_terrain_in_use { false };

            // Variables related to `Console`s.
            bool in_console { false };

            // Variables related to help mode.
            bool in_help_mode            { true };
            bool can_display_help_screen { true };

            float background_red   { NAN };
            float background_green { NAN };
            float background_blue  { NAN };
            float background_alpha { NAN };

            yli::ontology::ParentModule parent_of_worlds;
            yli::ontology::ParentModule parent_of_scenes;
            yli::ontology::ParentModule parent_of_font_2ds;
            yli::ontology::ParentModule parent_of_consoles;
            yli::ontology::ParentModule parent_of_any_value_entities;
            yli::ontology::ParentModule parent_of_callback_engine_entities;

            yli::ontology::FramebufferModule framebuffer_module;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void create_should_be_rendered_variable();

            bool compute_and_update_matrices_from_inputs();

            std::unique_ptr<yli::ontology::EntityFactory> entity_factory { std::make_unique<yli::ontology::EntityFactory>(this) };

            std::vector<yli::ontology::Entity*> entity_pointer_vector;
            std::queue<std::size_t> free_entityID_queue;
            std::size_t number_of_entities { 0 };

            yli::ontology::Scene* active_scene     { nullptr };
            yli::ontology::Console* active_console { nullptr };

            std::unique_ptr<yli::render::RenderMaster> render_master { nullptr }; // pointer to `RenderMaster`.
            std::unique_ptr<yli::audio::AudioMaster> audio_master    { nullptr }; // pointer to `AudioMaster`.
            std::unique_ptr<yli::input::InputMaster> input_master    { nullptr }; // pointer to `InputMaster`.

            // Bullet variables.
            std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration { std::make_unique<btDefaultCollisionConfiguration>() };
            std::unique_ptr<btCollisionDispatcher> dispatcher { std::make_unique<btCollisionDispatcher>(this->collision_configuration.get()) };
            std::unique_ptr<btBroadphaseInterface> overlapping_pair_cache { std::make_unique<btDbvtBroadphase>() };
            std::unique_ptr<btSequentialImpulseConstraintSolver> solver { std::make_unique<btSequentialImpulseConstraintSolver>() };

            // variables related to the window.
            SDL_Window* window { nullptr };
            uint32_t window_width;
            uint32_t window_height;
            std::string window_title { "Ylikuutio " + yli::ontology::Universe::version };

            const bool is_headless;
            const bool is_silent;
            const bool is_physical;
            bool is_fullscreen;

            // variables related to `Camera` (projection).
            glm::mat4 current_camera_projection_matrix { glm::mat4(1.0f) }; // Identity matrix (dummy value).
            glm::mat4 current_camera_view_matrix { glm::mat4(1.0f) };       // Identity matrix (dummy value).
            float aspect_ratio;          // At the moment all `Camera`s use the same aspect ratio.
            float initial_fov { 60.0f }; // At the moment all `Camera`s use the same FoV.

            // variables related to the fonts and texts used.
            std::size_t text_size;
            std::size_t font_size;

            // variables related to timing of events.
            std::size_t max_fps;
            float last_time_to_display_fps   { yli::time::get_time() };
            float last_time_for_display_sync { yli::time::get_time() };
            float delta_time                 { NAN };
            int32_t number_of_frames         { 0 };

            // `std::numeric_limits<std::size_t>::max()` means that `last_time_before_reading_keyboard` is not defined.
            uint32_t last_time_before_reading_keyboard    { std::numeric_limits<uint32_t>::max() };

            // `std::numeric_limits<std::size_t>::max()` means that `current_time_before_reading_keyboard` is not defined.
            uint32_t current_time_before_reading_keyboard { std::numeric_limits<uint32_t>::max() };
    };
}

#endif
