#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

#include "any_value.hpp"

// GCC (at least g++ 4.7.2) and Visual Studio 2015 do support
// setting default values of a struct using C++11 syntax.
// Clang 3.7.0 and Visual Studio 2013 do not support
// setting default values of a struct using C++11 syntax.
// Visual Studio 2013 fails to compile, whereas Clang-compiled
// executable with code with setting default values of a struct
// causes Segmentation fault upon execution of the program.
// Compilers that don't support setting default values of a struct
// are handled by setting the default values in a macro.
// http://stackoverflow.com/questions/16782103/initializing-default-values-in-a-struct/16783513#16783513
#ifdef __clang__
#elif defined(__GNUC__)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#elif defined(_WIN32)
#if (_MSC_VER >= 1900)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#endif
#endif

// GLEW must be included here, because `globals.hpp` may be compiled
// first, and if `GL/glew.h` is not included before `glfw3.h` (?),
// then g++ prints the following error:
// `error: #error gl.h included before glew.h`
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
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <unordered_map> // std::unordered_map
#include <vector>   // std::vector

namespace config
{
    class SettingMaster;
    class Setting;
}

namespace callback_system
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace graph
{
    class Graph;
}

namespace ontology
{
    class Entity;
    class Font2D;
}

typedef std::shared_ptr<datatypes::AnyValue> (*PreRenderCallback) (ontology::Entity* entity, config::SettingMaster* setting_master);
typedef std::shared_ptr<datatypes::AnyValue> (*PostRenderCallback) (ontology::Entity* entity, config::SettingMaster* setting_master);

typedef struct PrintingStruct
{
    PrintingStruct()
        : screen_width(-1), screen_height(-1), x(-1), y(-1), text_size(-1), font_size(-1), text_char(nullptr), char_font_texture_file_format(nullptr), horizontal_alignment(nullptr), vertical_alignment(nullptr)
    {
        // constructor.
    }
    int32_t screen_width;
    int32_t screen_height;
    int32_t x;
    int32_t y;
    int32_t text_size;
    int32_t font_size;
    std::string text;
    const char* text_char;
    const char* char_font_texture_file_format;
    const char* horizontal_alignment;
    const char* vertical_alignment;
} PrintingStruct;

typedef struct
{
    uint32_t image_width;
    uint32_t image_height;
    bool should_ylikuutio_use_real_texture_coordinates;
} BilinearInterpolationStruct;

typedef std::shared_ptr<datatypes::AnyValue> (*InputParametersToAnyValueCallback) (
        callback_system::CallbackEngine*,
        callback_system::CallbackObject*,
        std::vector<callback_system::CallbackParameter*>&);

namespace console
{
    class Console;
}
typedef std::shared_ptr<datatypes::AnyValue> (*InputParametersToAnyValueCallbackWithConsole) (
        callback_system::CallbackEngine*,
        callback_system::CallbackObject*,
        std::vector<callback_system::CallbackParameter*>&,
        console::Console*);

typedef std::shared_ptr<datatypes::AnyValue> (*GetContentCallback) (
        callback_system::CallbackEngine*,
        callback_system::CallbackObject*,
        std::vector<callback_system::CallbackParameter*>&,
        uint32_t x_start,
        uint32_t y_start,
        uint32_t z_start,
        uint32_t x_size,
        uint32_t y_size,
        uint32_t z_size);

#endif
