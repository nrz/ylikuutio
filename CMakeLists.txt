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
    cpp/ylikuutio/ylikuutio.cpp
    cpp/common/shader_loader.cpp
    cpp/common/shader_loader.hpp
    cpp/common/globals.cpp
    cpp/common/globals.hpp
    cpp/common/callback.cpp
    cpp/common/callback.hpp
    cpp/common/texture_loader.cpp
    cpp/common/texture_loader.hpp
    cpp/common/triangulation_macros.cpp
    cpp/common/transformation.cpp
    cpp/common/transformation.hpp
    cpp/common/indexing.cpp
    cpp/common/indexing.hpp
    cpp/common/bilinear_interpolation.cpp
    cpp/common/bilinear_interpolation.hpp
    cpp/common/triangulation.cpp
    cpp/common/triangulation.hpp
    cpp/common/heightmap_loader.cpp
    cpp/common/heightmap_loader.hpp
    cpp/common/objloader.cpp
    cpp/common/objloader.hpp
    cpp/common/font_loader.cpp
    cpp/common/font_loader.hpp
    cpp/common/model_common_functions.cpp
    cpp/common/model_common_functions.hpp
    cpp/common/model_templates.hpp
    cpp/common/world.cpp
    cpp/common/world.hpp
    cpp/common/shader.cpp
    cpp/common/shader.hpp
    cpp/common/material.cpp
    cpp/common/material.hpp
    cpp/common/graph.cpp
    cpp/common/graph.hpp
    cpp/common/node.cpp
    cpp/common/node.hpp
    cpp/common/species_or_glyph.hpp
    cpp/common/species.cpp
    cpp/common/species.hpp
    cpp/common/font.cpp
    cpp/common/font.hpp
    cpp/common/glyph.cpp
    cpp/common/glyph.hpp
    cpp/common/object.cpp
    cpp/common/object.hpp
    cpp/common/vboindexer.cpp
    cpp/common/vboindexer.hpp
    cpp/common/text2D.cpp
    cpp/common/text2D.hpp
    cpp/common/text3D.hpp
    cpp/common/text3D.cpp

    cpp/common/TransformVertexShader.vertexshader
    cpp/common/TextureFragmentShader.fragmentshader
    cpp/common/StandardShading.vertexshader
    cpp/common/StandardShading.fragmentshader
    cpp/common/TextVertexShader.vertexshader
    cpp/common/TextVertexShader.fragmentshader
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
