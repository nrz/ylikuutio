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

# Tutorial 4
add_executable(cube_with_colors
    cpp/cube_with_colors/cube_with_colors.cpp
    cpp/common/shader.cpp
    cpp/common/shader.hpp

    cpp/cube_with_colors/TransformVertexShader.vertexshader
    cpp/cube_with_colors/ColorFragmentShader.fragmentshader
    )
target_link_libraries(cube_with_colors
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(cube_with_colors PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/cube_with_colors/")
create_target_launcher(cube_with_colors WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/cube_with_colors/")

# Tutorial 9 - several objects
add_executable(several_objects
    cpp/several_objects/several_objects.cpp
    cpp/common/shader.cpp
    cpp/common/shader.hpp
    cpp/common/globals.cpp
    cpp/common/globals.hpp
    cpp/common/texture.cpp
    cpp/common/texture.hpp
    cpp/common/heightmap_loader.cpp
    cpp/common/heightmap_loader.hpp
    cpp/common/objloader.cpp
    cpp/common/objloader.hpp
    cpp/common/model.cpp
    cpp/common/model.hpp
    cpp/common/vboindexer.cpp
    cpp/common/vboindexer.hpp
    cpp/common/text2D.hpp
    cpp/common/text2D.cpp

    cpp/common/StandardShading.vertexshader
    cpp/common/StandardShading.fragmentshader
    )
configure_file(cpp/common/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(cpp/common/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(cpp/several_objects/suzanne.obj suzanne.obj COPYONLY)
configure_file(cpp/several_objects/uvmap.DDS uvmap.DDS COPYONLY)
configure_file(cpp/ylikuutio/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(cpp/ylikuutio/Holstein.bmp Holstein.bmp COPYONLY)

target_link_libraries(several_objects
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(several_objects PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/several_objects/")
create_target_launcher(several_objects WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/several_objects/")

# Ylikuutio
add_executable(ylikuutio
    cpp/ylikuutio/ylikuutio.cpp
    cpp/common/shader.cpp
    cpp/common/shader.hpp
    cpp/common/globals.cpp
    cpp/common/globals.hpp
    cpp/common/texture.cpp
    cpp/common/texture.hpp
    cpp/common/heightmap_loader.cpp
    cpp/common/heightmap_loader.hpp
    cpp/common/objloader.cpp
    cpp/common/objloader.hpp
    cpp/common/model.cpp
    cpp/common/model.hpp
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
configure_file(cpp/ylikuutio/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(cpp/ylikuutio/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(cpp/ylikuutio/Holstein.bmp Holstein.bmp COPYONLY)
configure_file(cpp/ylikuutio/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(cpp/ylikuutio/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(cpp/ylikuutio/noise128x128.bmp noise128x128.bmp COPYONLY)
configure_file(cpp/ylikuutio/S17W069.hgt S17W069.hgt COPYONLY)

target_link_libraries(ylikuutio
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(ylikuutio PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")
create_target_launcher(ylikuutio WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/cpp/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
    add_custom_command(
        TARGET cube_with_colors POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/cube_with_colors${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/cpp/cube_with_colors/"
        )

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

