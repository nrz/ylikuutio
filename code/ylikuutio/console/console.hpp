#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

#include "console_struct.hpp"
#include "command_and_callback_struct.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
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

// Include standard headers
#include <list>          // std::list
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `Console` works through keypress callbacks and keyrelease callbacks, and
// `glfwSetCharModsCallback`. If the action of a key should not happen many
// times in a very fast succession, some means to control the frequency is
// needed. The easiest option is to use a `bool` variable like
// `bool enable_action`.
//
// In the keypress callback, the value of `enable_action` is tested, and
// nothing is done if it's `false`.
//
// If `enable_action` is `true`, the corresponding action takes place,
// after which `enable_action` is set to `false`.
//
// In the keyrelease callback `enable_action` is set to `true`.
//
// `glfwSetCharModsCallback` sets a separate callback for some special keys.
// This is used for entering text into console (writing commands).
// All other console-related functions are implemented through keypress
// callbacks and keyrelease callbacks.

namespace map
{
    template <class T1>
        void print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, console::Console* const console);
}

namespace console
{
    class Console
    {
        public:
            // constructor.
            Console(const ConsoleStruct& console_struct);

            // destructor.
            ~Console();

            void set_my_keypress_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer);
            void set_my_keyrelease_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer);
            void print_text(const std::string& text);
            void print_help();
            void draw_console() const;

            // Public callbacks.

            // Action mode keyrelease callbacks begin here.

            static std::shared_ptr<datatypes::AnyValue> enable_enter_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Action mode keypress callbacks begin here.

            static std::shared_ptr<datatypes::AnyValue> enter_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Console mode keyrelease callbacks begin here.

            static std::shared_ptr<datatypes::AnyValue> enable_exit_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> release_left_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> release_right_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> release_left_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> release_right_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> release_left_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> release_right_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_move_to_previous_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_move_to_next_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_backspace(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_enter_key(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_ctrl_c(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_ctrl_w(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_page_up(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_page_down(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_home(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enable_end(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Console mode keypress callbacks begin here.

            static std::shared_ptr<datatypes::AnyValue> exit_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> press_left_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> press_right_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> press_left_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> press_right_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> press_left_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> press_right_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> move_to_previous_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> move_to_next_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> backspace(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> enter_key(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> ctrl_c(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> ctrl_w(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> page_up(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> page_down(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> home(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static std::shared_ptr<datatypes::AnyValue> end(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Public callbacks end here.

            template <class T1>
                friend void map::print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, console::Console* const console);

        private:
            static void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods);

            // Callbacks end here.

            ontology::Universe* get_universe() const;

            void copy_historical_input_into_current_input();
            bool exit_console();
            void delete_character();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();

            std::list<char> current_input; // This is used for actual inputs.
            std::list<char>::iterator cursor_it;
            int32_t cursor_index;
            bool in_console;
            bool can_enter_console;
            bool can_exit_console;
            bool can_move_to_previous_input;
            bool can_move_to_next_input;
            bool can_backspace;
            bool can_enter_key;
            bool can_ctrl_c;
            bool can_ctrl_w;
            bool can_page_up;
            bool can_page_down;
            bool can_home;
            bool can_end;
            bool is_left_control_pressed;
            bool is_right_control_pressed;
            bool is_left_alt_pressed;
            bool is_right_alt_pressed;
            bool is_left_shift_pressed;
            bool is_right_shift_pressed;

            std::vector<std::list<char>> command_history;
            std::vector<std::list<char>> console_history;

            bool in_history;
            bool in_historical_input;
            int32_t history_line_i;
            int32_t historical_input_i;
            std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.

            // These are related to keypress callbacks.
            std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_keypress_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer;

            // These are related to keyrelease callbacks.
            std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_keyrelease_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer;

            // This is a pointer to `std::unordered_map<std::string, bool>` that contains console command callbacks.
            std::unordered_map<std::string, ConsoleCommandCallback>* command_callback_map_pointer;

            // This is a pointer to `ontology::Universe`.
            ontology::Universe* universe;

            // This is a pointer to `font2D::Font2D` instance that is used for printing.
            ontology::Font2D* font2D_pointer;

            int32_t console_top_y;
            int32_t console_bottom_y;
            int32_t console_left_x;
            int32_t console_right_x;

            int32_t n_rows;
            int32_t n_columns;

            const std::string prompt = "$ ";
    };
}

#endif
