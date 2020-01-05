// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __CREATURE_HPP_INCLUDED
#define __CREATURE_HPP_INCLUDED

#include "object.hpp"

// Every intentional entity is a `Creature`.
// Every player-controlled character is a `Creature`.
// Every AI-controlled character is a `Creature`.
// If any intentional motion is wanted for an entity (eg. ship, spaceship, vehicle), then it should be a `Creature`.
// Available input methods may be different for player-controlled and AI-controlled characters.
// AI-controlled creatures may have limitations in their options, if so desired.
// For example, it may be useful to disable exit game and enter console functions from AI characters.
//
// The artificial intelligence itself will be in a `yli::ontology::AI` entity, of which `Creature` depends on.

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Creature: public yli::ontology::Object
        {
            public:
                // constructor.
                Creature(yli::ontology::Universe* const universe, yli::ontology::ObjectStruct& object_struct)
                    : Object(universe, object_struct)
                {
                    // constructor.

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Creature*";
                }

                Creature(const Creature&) = delete;            // Delete copy constructor.
                Creature &operator=(const Creature&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Creature();

                // Act according to this `Creature`'s programming.
                void act();

                // Public callbacks (to be called from AI scripts written in
                // s7 Scheme). These are the functions that are available
                // for AI scripts. Ylikuutio will support scripting of game
                // agents using s7 Scheme. Ylikuutio does not predefine what
                // kind of games can be done with it. However, the callbacks
                // Ylikuutio provides mean these is more support for features
                // needing such callbacks. In particular, Ylikuutio supports
                // simulations of real-life phenomena.
                // TODO: implement public AI callbacks!

                // Command callbacks.

                // Allied-object-centric path and map information callbacks.

                // This method returns `true` if destination is visible, `false` otherwise.
                // destination may be visible directly (line of sight) or eg. by radar (without line of sight).
                static bool is_visible(const float x, const float y, const float z);

                // This method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
                static bool is_line_of_sight_for_any(const float x, const float y, const float z);

                // This method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
                static bool is_line_of_sight(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if there is any known ground path between `Object` and (x, y, z),  `false` otherwise.
                static bool is_ground_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if there is any known rail path between `Object` and (x, y, z),  `false` otherwise.
                static bool is_rail_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if there is known air path between objects, `false` otherwise.
                static bool is_air_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if there is known ballistic path between `Object` and (x, y, z), `false` otherwise.
                static bool is_ballistic_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if there may be ballistic path between objects, `false` otherwise.
                static bool may_have_ballistic_path(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // These functions return the coordinates of the farthest point.
                static float get_closest_visible_ground_dest_x_towards(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static float get_closest_visible_ground_dest_y_towards(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static float get_closest_visible_ground_dest_z_towards(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if complete path is visible, `false` otherwise.
                static bool is_complete_ground_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static bool is_complete_rail_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static bool is_complete_air_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static bool is_complete_ballistic_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // These methods return the coordinates of the point closest to `object` from which there is known ballistic path to (x, y, z).
                static float get_nearest_known_ballistic_launch_site_x(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static float get_nearest_known_ballistic_launch_site_y(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static float get_nearest_known_ballistic_launch_site_z(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // These methods return the coordinates of the point closest to `object` from which there may be a ballistic path to (x, y, z).
                static float get_nearest_possible_ballistic_launch_site_x(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static float get_nearest_possible_ballistic_launch_site_y(const yli::ontology::Object* const object, const float x, const float y, const float z);
                static float get_nearest_possible_ballistic_launch_site_z(const yli::ontology::Object* const object, const float x, const float y, const float z);

                // This method returns `true` if there is known line of sight between (x1, y1, z1) and (x2, y2, z2).

                // Coordinate-centric path and map information callbacks.
                // The conditions for returning `true` match the conditions of the corresponding allied-object-centric callbacks.

                static bool is_line_of_sight_between_from(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static bool may_have_line_of_sight_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static bool is_ground_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static bool is_rail_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static bool is_air_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static bool is_ballistic_path_known(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static bool may_have_ballistic_path_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

                static float get_nearest_known_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static float get_nearest_known_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static float get_nearest_known_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

                static float get_nearest_possible_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static float get_nearest_possible_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static float get_nearest_possible_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

                static float get_closest_visible_dest_x_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static float get_closest_visible_dest_y_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
                static float get_closest_visible_dest_z_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

                // Callbacks for looping through objects.
                static void* get_first_allied_object(yli::ontology::Object* object);       // point `allied_iterator` to the first object, `nullptr` if N/A.
                static void* get_next_allied_object(yli::ontology::Object* object);        // advance `allied_iterator`, `nullptr` if N/A.
                static void* get_first_other_allied_object(yli::ontology::Object* object); // point `allied_other_iterator` to the first other object, `nullptr` if N/A.
                static void* get_next_other_allied_object(yli::ontology::Object* object);  // advance `allied_other_iterator`, `nullptr` if N/A.
                static void* get_first_opponent_object(yli::ontology::Object* object);     // point `opponent_iterator` to the first opponent, `nullptr` if N/A.
                static void* get_next_opponent_object(yli::ontology::Object* object);      // advance `opponent_iterator`, `nullptr` if N/A.

                // Public callbacks end here.
        };
    }
}

#endif
