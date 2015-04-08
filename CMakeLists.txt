# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ylikuutio)

find_package(OpenGL REQUIRED)

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

include_directories(
    external/AntTweakBar-1.16/include/
    external/glfw-3.0.3/include/GLFW/
    external/glm-0.9.4.0/
    external/glew-1.9.0/include/
    external/assimp-3.0.1270/include/
    external/bullet-2.81-rev2613/src/
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
    cube_with_colors/cube_with_colors.cpp
    common/shader.cpp
    common/shader.hpp

    cube_with_colors/TransformVertexShader.vertexshader
    cube_with_colors/ColorFragmentShader.fragmentshader
    )
target_link_libraries(cube_with_colors
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(cube_with_colors PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cube_with_colors/")
create_target_launcher(cube_with_colors WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cube_with_colors/")

# Tutorial 9 - several objects
add_executable(several_objects
    several_objects/several_objects.cpp
    common/shader.cpp
    common/shader.hpp
    common/globals.cpp
    common/globals.hpp
    common/controls.cpp
    common/controls.hpp
    common/texture.cpp
    common/texture.hpp
    common/bmploader.cpp
    common/bmploader.hpp
    common/objloader.cpp
    common/objloader.hpp
    common/model.cpp
    common/model.hpp
    common/vboindexer.cpp
    common/vboindexer.hpp
    common/text2D.hpp
    common/text2D.cpp

    common/StandardShading.vertexshader
    common/StandardShading.fragmentshader
    )
configure_file(common/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(common/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(several_objects/suzanne.obj suzanne.obj COPYONLY)
configure_file(several_objects/uvmap.DDS uvmap.DDS COPYONLY)
configure_file(text2d/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(text2d/Holstein.bmp Holstein.bmp COPYONLY)

target_link_libraries(several_objects
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(several_objects PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/several_objects/")
create_target_launcher(several_objects WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/several_objects/")

# Tutorial 11
add_executable(text2d
    text2d/tutorial11.cpp
    common/shader.cpp
    common/shader.hpp
    common/globals.cpp
    common/globals.hpp
    common/controls.cpp
    common/controls.hpp
    common/texture.cpp
    common/texture.hpp
    common/bmploader.cpp
    common/bmploader.hpp
    common/objloader.cpp
    common/objloader.hpp
    common/model.cpp
    common/model.hpp
    common/vboindexer.cpp
    common/vboindexer.hpp
    common/text2D.hpp
    common/text2D.cpp

    common/StandardShading.vertexshader
    common/StandardShading.fragmentshader
    common/TextVertexShader.vertexshader
    common/TextVertexShader.fragmentshader
    )
configure_file(common/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(common/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(common/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(common/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)
configure_file(text2d/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(text2d/Holstein.bmp Holstein.bmp COPYONLY)

target_link_libraries(text2d
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(text2d PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/text2d/")
create_target_launcher(text2d WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/text2d/")

# Ylikuutio
add_executable(ylikuutio
    ylikuutio/ylikuutio.cpp
    common/shader.cpp
    common/shader.hpp
    common/globals.cpp
    common/globals.hpp
    common/controls.cpp
    common/controls.hpp
    common/texture.cpp
    common/texture.hpp
    common/bmploader.cpp
    common/bmploader.hpp
    common/objloader.cpp
    common/objloader.hpp
    common/model.cpp
    common/model.hpp
    common/vboindexer.cpp
    common/vboindexer.hpp
    common/text2D.cpp
    common/text2D.hpp

    common/TransformVertexShader.vertexshader
    common/TextureFragmentShader.fragmentshader
    common/StandardShading.vertexshader
    common/StandardShading.fragmentshader
    common/TextVertexShader.vertexshader
    common/TextVertexShader.fragmentshader
    )
configure_file(common/TransformVertexShader.vertexshader TransformVertexShader.vertexshader COPYONLY)
configure_file(common/TextureFragmentShader.fragmentshader TextureFragmentShader.fragmentshader COPYONLY)
configure_file(common/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(common/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(common/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(common/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)
configure_file(ylikuutio/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(ylikuutio/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(ylikuutio/Holstein.bmp Holstein.bmp COPYONLY)
configure_file(ylikuutio/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(ylikuutio/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(ylikuutio/noise128x128.bmp noise128x128.bmp COPYONLY)

target_link_libraries(ylikuutio
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(ylikuutio PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ylikuutio/")
create_target_launcher(ylikuutio WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ylikuutio/")


SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
    add_custom_command(
        TARGET cube_with_colors POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/cube_with_colors${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/cube_with_colors/"
        )

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

