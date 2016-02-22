# CMake entry point
cmake_minimum_required(VERSION 2.6.2)
project(ylikuutio)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

# Compile external dependencies
add_subdirectory (external)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if(CMAKE_SOURCE_DIR MATCHES " ")
    message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if(CMAKE_BINARY_DIR MATCHES " ")
    message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# uncomment the following line to do unit tests also with Catch.
# set(DO_UNIT_TESTS_WITH_CATCH true)

# comment the following line to disable unit tests with Google Test.
set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)

include(ExternalProject) # for ExternalProject_Add

# for Google Test.
enable_testing()

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/external)

if(INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
    external/glfw-3.0.3/include/GLFW/
    external/glm-0.9.4.0/
    external/glew-1.9.0/include/
    external/Catch/single_include/
    external/googletest/googletest/include/
    external/googletest/googlemock/include/
    .
    )

# Download and install GoogleTest
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_DOWNLOAD ON
    LOG_BUILD ON
    )

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest googletest)

# Set gtest properties
ExternalProject_Get_Property(googletest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
    )
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
# include_directories("${source_dir}/external/googletest/googletest/include")

# specify include directory.
set(GTEST_INCLUDE_DIR ${source_dir}/include)

# library.
# set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY_PATH ${binary_dir}/googlemock/gtest/libgtest.a)
set(GTEST_LIBRARY gtest)
set(GTEST_MAIN_LIBRARY gtest_main)
find_package(GTest REQUIRED)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION
    ${GTEST_LIBRARY_PATH} )
add_dependencies(${GTEST_LIBRARY} googletest)

# Download and install GoogleMock
ExternalProject_Add(
    googlemock
    GIT_REPOSITORY https://github.com/google/googletest
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
    # Disable install step
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_DOWNLOAD ON
    LOG_BUILD ON
    )

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock googlemock)

# Set gmock properties
ExternalProject_Get_Property(googlemock source_dir binary_dir)
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gmock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
    )
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
# include_directories("${source_dir}/external/googletest/googlemock/include")

include_directories(${GTEST_INCLUDE_DIRS})

# include_directories(
#     external/AntTweakBar-1.16/include/
#     external/glfw-3.0.3/include/GLFW/
#     external/glm-0.9.4.0/
#     external/glew-1.9.0/include/
#     external/assimp-3.0.1270/include/
#     external/bullet-2.81-rev2613/src/
#     .
#     )

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

# for general use.
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

# for tests.
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/textures/test3x3.bmp test3x3.bmp COPYONLY)

# Ajokki
add_executable(ajokki
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

    # string, in alphabetical order
    cpp/ylikuutio/string/ylikuutio_string.cpp
    cpp/ylikuutio/string/ylikuutio_string.hpp

    # ajokki, in alphabetical order
    cpp/ajokki/ajokki.cpp
    )

target_link_libraries(ajokki
    ${ALL_LIBS}
    )
# Xcode and Visual working directories
set_target_properties(ajokki PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")
create_target_launcher(ajokki WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ylikuutio/")

# Tests
if(DO_UNIT_TESTS_WITH_CATCH)
    add_executable(unit_tests_with_Catch
        cpp/ylikuutio/tests/catch/tests.cpp
        )

    target_link_libraries(unit_tests_with_Catch
        ${ALL_LIBS}
        )
    # Xcode and Visual working directories
    set_target_properties(unit_tests_with_Catch PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/catch/")
    create_target_launcher(unit_tests_with_Catch WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/catch/")
endif()

if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    set(FILES_TO_TEST
        cpp/ylikuutio/common/globals.cpp
        cpp/ylikuutio/common/globals.hpp
        cpp/ylikuutio/common/transformation.cpp
        cpp/ylikuutio/common/transformation.hpp
        cpp/ylikuutio/common/indexing.cpp
        cpp/ylikuutio/common/indexing.hpp
        cpp/ylikuutio/common/bilinear_interpolation.cpp
        cpp/ylikuutio/common/bilinear_interpolation.hpp
        cpp/ylikuutio/common/triangulation.cpp
        cpp/ylikuutio/common/triangulation.hpp
        cpp/ylikuutio/string/ylikuutio_string.cpp
        cpp/ylikuutio/string/ylikuutio_string.hpp
        )
    set(UNIT_TESTS
        cpp/ylikuutio/tests/googletest/test_globals.cpp
        cpp/ylikuutio/tests/googletest/test_heightmap_loader.cpp
        cpp/ylikuutio/tests/googletest/test_triangulation.cpp
        cpp/ylikuutio/tests/googletest/test_ylikuutio_string.cpp)
    set(MAIN_FILE cpp/ylikuutio/tests/googletest/main.cpp)

    add_library(codeToTest ${FILES_TO_TEST})

    add_executable(do_tests_googletest ${MAIN_FILE})
    target_link_libraries(do_tests_googletest codeToTest)

    add_executable(unit_tests_with_Google_Test cpp/ylikuutio/tests/googletest/test_main.cpp ${UNIT_TESTS})
    target_link_libraries(unit_tests_with_Google_Test gtest libgtest rt pthread codeToTest)

    # Xcode and Visual working directories
    set_target_properties(unit_tests_with_Google_Test PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/googletest/")
    create_target_launcher(unit_tests_with_Google_Test WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/tests/googletest/")
endif()

source_group(common REGULAR_EXPRESSION ".*/cpp/common/.*" )
source_group(shaders REGULAR_EXPRESSION ".*/.*shader$" )
