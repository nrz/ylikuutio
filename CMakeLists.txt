# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ylikuutio)

find_package(OpenGL REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

# include_directories(
#     external/AntTweakBar-1.16/include/
#     external/glfw-3.0.3/include/GLFW/
#     external/glm-0.9.4.0/
#     external/glew-1.9.0/include/
#     external/assimp-3.0.1270/include/
#     external/bullet-2.81-rev2613/src/
#     .
#     )

include_directories(
    external/glfw-3.0.3/include/GLFW/
    external/glm-0.9.4.0/
    external/glew-1.9.0/include/
    external/Catch/single_include/
    .
    )

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    GLFW_303
    GLEW_190
    )

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    )

# Ylikuutio
add_executable(robotum
    # callback, in alphabetical order
    cpp/ylikuutio/callback/callback_engine.cpp
    cpp/ylikuutio/callback/callback_engine.hpp
    cpp/ylikuutio/callback/callback_object.cpp
    cpp/ylikuutio/callback/callback_object.hpp
    cpp/ylikuutio/callback/callback_parameter.cpp
    cpp/ylikuutio/callback/callback_parameter.hpp

    # common, in alphabetical order
    cpp/ylikuutio/common/any_value.hpp
    cpp/ylikuutio/common/bilinear_interpolation.cpp
    cpp/ylikuutio/common/bilinear_interpolation.hpp
    cpp/ylikuutio/common/indexing.cpp
    cpp/ylikuutio/common/indexing.hpp
    cpp/ylikuutio/common/globals.cpp
    cpp/ylikuutio/common/globals.hpp
    cpp/ylikuutio/common/transformation.cpp
    cpp/ylikuutio/common/transformation.hpp
    cpp/ylikuutio/common/triangulation.cpp
    cpp/ylikuutio/common/triangulation.hpp
    cpp/ylikuutio/common/triangulation_macros.cpp

    # graph, in alphabetical order.
    cpp/ylikuutio/graph/graph.cpp
    cpp/ylikuutio/graph/graph.hpp
    cpp/ylikuutio/graph/node.cpp
    cpp/ylikuutio/graph/node.hpp

    # hierarchy, in alphabetical order.
    cpp/ylikuutio/hierarchy/hierarchy.cpp
    cpp/ylikuutio/hierarchy/hierarchy.hpp
    cpp/ylikuutio/hierarchy/hierarchy_templates.hpp

    # model, in alphabetical order
    cpp/ylikuutio/model/font.cpp
    cpp/ylikuutio/model/font.hpp
    cpp/ylikuutio/model/font_loader.cpp
    cpp/ylikuutio/model/font_loader.hpp
    cpp/ylikuutio/model/glyph.cpp
    cpp/ylikuutio/model/glyph.hpp
    cpp/ylikuutio/model/ground_level.cpp
    cpp/ylikuutio/model/ground_level.hpp
    cpp/ylikuutio/model/heightmap_loader.cpp
    cpp/ylikuutio/model/heightmap_loader.hpp
    cpp/ylikuutio/model/material.cpp
    cpp/ylikuutio/model/material.hpp
    cpp/ylikuutio/model/object.cpp
    cpp/ylikuutio/model/object.hpp
    cpp/ylikuutio/model/objloader.cpp
    cpp/ylikuutio/model/objloader.hpp
    cpp/ylikuutio/model/render_templates.hpp
    cpp/ylikuutio/model/shader.cpp
    cpp/ylikuutio/model/shader.hpp
    cpp/ylikuutio/model/shader_loader.cpp
    cpp/ylikuutio/model/shader_loader.hpp
    cpp/ylikuutio/model/species.cpp
    cpp/ylikuutio/model/species.hpp
    cpp/ylikuutio/model/species_or_glyph.hpp
    cpp/ylikuutio/model/text2D.cpp
    cpp/ylikuutio/model/text2D.hpp
    cpp/ylikuutio/model/text3D.hpp
    cpp/ylikuutio/model/text3D.cpp
    cpp/ylikuutio/model/texture_loader.cpp
    cpp/ylikuutio/model/texture_loader.hpp
    cpp/ylikuutio/model/vboindexer.cpp
    cpp/ylikuutio/model/vboindexer.hpp
    cpp/ylikuutio/model/world.cpp
    cpp/ylikuutio/model/world.hpp

    # shaders, in alphabetical order
    cpp/ylikuutio/common/StandardShading.fragmentshader
    cpp/ylikuutio/common/StandardShading.vertexshader
    cpp/ylikuutio/common/TransformVertexShader.vertexshader
    cpp/ylikuutio/common/TextureFragmentShader.fragmentshader
    cpp/ylikuutio/common/TextVertexShader.fragmentshader
    cpp/ylikuutio/common/TextVertexShader.vertexshader

    # robotum, in alphabetical order
    cpp/robotum/robotum.cpp
    )

configure_file(cpp/ylikuutio/common/TransformVertexShader.vertexshader TransformVertexShader.vertexshader COPYONLY)
configure_file(cpp/ylikuutio/common/TextureFragmentShader.fragmentshader TextureFragmentShader.fragmentshader COPYONLY)
configure_file(cpp/ylikuutio/common/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(cpp/ylikuutio/common/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(cpp/ylikuutio/common/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(cpp/ylikuutio/common/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)
configure_file(res/objects/suzanne.obj suzanne.obj COPYONLY)
configure_file(res/textures/uvmap.DDS uvmap.DDS COPYONLY)
configure_file(res/textures/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(res/fonts/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(res/fonts/Holstein.bmp Holstein.bmp COPYONLY)
configure_file(res/height_maps/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/height_maps/noise128x128.bmp noise128x128.bmp COPYONLY)
configure_file(res/height_maps/S17W069.hgt S17W069.hgt COPYONLY)
configure_file(res/fonts/kongtext.svg kongtext.svg COPYONLY)

target_link_libraries(robotum
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(robotum PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")
create_target_launcher(robotum WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")

# Tests
add_executable(do_tests
    cpp/ylikuutio/tests/tests.cpp
    )
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/textures/test3x3.bmp test3x3.bmp COPYONLY)

target_link_libraries(do_tests
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(do_tests PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/")
create_target_launcher(do_tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/cpp/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
