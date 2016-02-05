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
add_executable(ylikuutio
    # callback, in alphabetical order
    cpp/callback/callback_engine.cpp
    cpp/callback/callback_engine.hpp
    cpp/callback/callback_object.cpp
    cpp/callback/callback_object.hpp
    cpp/callback/callback_parameter.cpp
    cpp/callback/callback_parameter.hpp

    # common, in alphabetical order
    cpp/common/any_value.hpp
    cpp/common/bilinear_interpolation.cpp
    cpp/common/bilinear_interpolation.hpp
    cpp/common/indexing.cpp
    cpp/common/indexing.hpp
    cpp/common/globals.cpp
    cpp/common/globals.hpp
    cpp/common/transformation.cpp
    cpp/common/transformation.hpp
    cpp/common/triangulation.cpp
    cpp/common/triangulation.hpp
    cpp/common/triangulation_macros.cpp

    # graph, in alphabetical order.
    cpp/graph/graph.cpp
    cpp/graph/graph.hpp
    cpp/graph/node.cpp
    cpp/graph/node.hpp

    # hierarchy, in alphabetical order.
    cpp/hierarchy/hierarchy.cpp
    cpp/hierarchy/hierarchy.hpp
    cpp/hierarchy/hierarchy_templates.hpp

    # model, in alphabetical order
    cpp/model/font.cpp
    cpp/model/font.hpp
    cpp/model/font_loader.cpp
    cpp/model/font_loader.hpp
    cpp/model/glyph.cpp
    cpp/model/glyph.hpp
    cpp/model/ground_level.cpp
    cpp/model/ground_level.hpp
    cpp/model/heightmap_loader.cpp
    cpp/model/heightmap_loader.hpp
    cpp/model/material.cpp
    cpp/model/material.hpp
    cpp/model/object.cpp
    cpp/model/object.hpp
    cpp/model/objloader.cpp
    cpp/model/objloader.hpp
    cpp/model/render_templates.hpp
    cpp/model/shader.cpp
    cpp/model/shader.hpp
    cpp/model/shader_loader.cpp
    cpp/model/shader_loader.hpp
    cpp/model/species.cpp
    cpp/model/species.hpp
    cpp/model/species_or_glyph.hpp
    cpp/model/text2D.cpp
    cpp/model/text2D.hpp
    cpp/model/text3D.hpp
    cpp/model/text3D.cpp
    cpp/model/texture_loader.cpp
    cpp/model/texture_loader.hpp
    cpp/model/vboindexer.cpp
    cpp/model/vboindexer.hpp
    cpp/model/world.cpp
    cpp/model/world.hpp

    # shaders, in alphabetical order
    cpp/common/StandardShading.fragmentshader
    cpp/common/StandardShading.vertexshader
    cpp/common/TransformVertexShader.vertexshader
    cpp/common/TextureFragmentShader.fragmentshader
    cpp/common/TextVertexShader.fragmentshader
    cpp/common/TextVertexShader.vertexshader

    # ylikuutio, in alphabetical order
    cpp/ylikuutio/ylikuutio.cpp
    )

configure_file(cpp/common/TransformVertexShader.vertexshader TransformVertexShader.vertexshader COPYONLY)
configure_file(cpp/common/TextureFragmentShader.fragmentshader TextureFragmentShader.fragmentshader COPYONLY)
configure_file(cpp/common/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(cpp/common/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(cpp/common/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(cpp/common/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)
configure_file(res/suzanne.obj suzanne.obj COPYONLY)
configure_file(res/uvmap.DDS uvmap.DDS COPYONLY)
configure_file(res/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(res/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(res/Holstein.bmp Holstein.bmp COPYONLY)
configure_file(res/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(res/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/noise128x128.bmp noise128x128.bmp COPYONLY)
configure_file(res/S17W069.hgt S17W069.hgt COPYONLY)
configure_file(res/kongtext.svg kongtext.svg COPYONLY)

target_link_libraries(ylikuutio
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(ylikuutio PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")
create_target_launcher(ylikuutio WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")

# Tests
add_executable(do_tests
    cpp/tests/tests.cpp
    )
configure_file(res/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/test3x3.bmp test3x3.bmp COPYONLY)

target_link_libraries(do_tests
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(do_tests PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/")
create_target_launcher(do_tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/cpp/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
