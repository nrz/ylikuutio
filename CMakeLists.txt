# CMake entry point
cmake_minimum_required(VERSION 2.6.2)
project(ylikuutio)

# uncomment the following line to cross-compile for Windows under Linux using mingw64.
# set(CROSS_COMPILE_FOR_WINDOWS true)

# comment the following line to disable scripting with Chibi Scheme.
set(ENABLE_SCRIPTING_WITH_CHIBI_SCHEME true)

# uncomment the following line to do unit tests also with Catch.
# set(DO_UNIT_TESTS_WITH_CATCH true)

# comment the following line to disable unit tests with Google Test.
set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)

# uncomment the following line to download the latest versions of external projects
# instead of using the versions carried in Ylikuutio repository (in `external/`).
# set(ENABLE_DOWNLOAD_LATEST_VERSIONS_OF_EXTERNAL_PROJECTS)

# uncomment the following line to disable updating of external projects.
# set(DISABLE_UPDATE_STEP true)

if(CROSS_COMPILE_FOR_WINDOWS)
    # https://cmake.org/Wiki/CMake_Cross_Compiling
    # the name of the target operating system
    set(CMAKE_SYSTEM_NAME Windows)

    # which compilers to use for C and C++
    set(CMAKE_C_COMPILER /usr/bin/i686-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/i686-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER /usr/bin/686-w64-mingw32-windres)

    # here is the target environment located
    set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32/)

    # adjust the default behaviour of the FIND_XXX() commands:
    # search headers and libraries in the target environment, search
    # programs in the host environment
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(eigen)

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

include(ExternalProject) # for ExternalProject_Add

# for Google Test.
enable_testing()

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/external)

if(INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

# Do not compile GLFW tests, examples and documentation.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(
    external/glfw-3.2/include/GLFW/
    external/glfw-3.2/include/
    external/glm-0.9.4.0/
    external/glew-2.0.0/include/
    .
    )

if(ENABLE_SCRIPTING_WITH_CHIBI_SCHEME)
    include_directories(
        external/chibi-scheme/include/
        )
endif()

if(ENABLE_DOWNLOAD_LATEST_VERSIONS_OF_EXTERNAL_PROJECTS)
    if(DISABLE_UPDATE_STEP)
        # Download and install Eigen
        ExternalProject_Add(
            eigen
            GIT_REPOSITORY https://github.com/RLovelett/eigen
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/eigen
            # Disable install step
            INSTALL_COMMAND ""
            # Disable update step
            UPDATE_COMMAND ""
            LOG_DOWNLOAD ON
            LOG_DOWNLOAD ON
            LOG_BUILD ON
            )
    else()
        # Download and install Eigen
        ExternalProject_Add(
            eigen
            GIT_REPOSITORY https://github.com/RLovelett/eigen
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/eigen
            # Disable install step
            INSTALL_COMMAND ""
            LOG_DOWNLOAD ON
            LOG_DOWNLOAD ON
            LOG_BUILD ON
            )
    endif()
else()
    # Use Eigen 3.2.9 provided in the Ylikuutio repository.
    ExternalProject_Add(
        eigen
        URL "file://${CMAKE_SOURCE_DIR}/external/eigen-3.2.9"
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/eigen
        # Disable install step
        INSTALL_COMMAND ""
        LOG_BUILD ON
        )
endif()

# http://stackoverflow.com/questions/17446981/cmake-externalproject-add-and-findpackage/17473508#17473508
if(NOT ${eigen_FOUND})
    # Rerun CMake in initial build.
    # Will update cmakecache/project files on first build.
    # So you may have to reload project after first build.
    add_custom_target(rescan ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS eigen)
else()
    # rescan becomes a dummy target after first build.
    # This prevents CMake from rebuilding cache/projects on subsequent builds.
    add_custom_target(rescan)
endif()

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/eigen/src/eigen/
    )

if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    include_directories(
        external/googletest/googletest/include/
        external/googletest/googlemock/include/
        ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/googletest/googletest/include/
        ${CMAKE_CURRENT_BINARY_DIR}/gmock/src/googletest/googletest/include/
        )

    if(DISABLE_UPDATE_STEP)
        # Download and install GoogleTest
        ExternalProject_Add(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
            # Disable install step
            INSTALL_COMMAND ""
            # Disable update step
            UPDATE_COMMAND ""
            LOG_DOWNLOAD ON
            LOG_DOWNLOAD ON
            LOG_BUILD ON
            )
    else()
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
    endif()

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

    if(DISABLE_UPDATE_STEP)
        # Download and install GoogleMock
        ExternalProject_Add(
            googlemock
            GIT_REPOSITORY https://github.com/google/googletest
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
            # Disable install step
            INSTALL_COMMAND ""
            # Disable update step
            UPDATE_COMMAND ""
            LOG_DOWNLOAD ON
            LOG_DOWNLOAD ON
            LOG_BUILD ON
            )
    else()
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
    endif()

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
endif()

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
    GLEW_200
    )

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    )

# for general use.
configure_file(cpp/ylikuutio/shaders/TransformVertexShader.vertexshader TransformVertexShader.vertexshader COPYONLY)
configure_file(cpp/ylikuutio/shaders/TextureFragmentShader.fragmentshader TextureFragmentShader.fragmentshader COPYONLY)
configure_file(cpp/ylikuutio/shaders/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(cpp/ylikuutio/shaders/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(cpp/ylikuutio/shaders/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(cpp/ylikuutio/shaders/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)
configure_file(res/objects/suzanne.obj suzanne.obj COPYONLY)
configure_file(res/textures/uvmap.DDS uvmap.DDS COPYONLY)
configure_file(res/textures/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(res/fonts/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(res/fonts/Holstein.bmp Holstein.bmp COPYONLY)
configure_file(res/height_maps/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/height_maps/noise128x128.bmp noise128x128.bmp COPYONLY)
configure_file(res/height_maps/S17W069.hgt S17W069.hgt COPYONLY)
configure_file(res/fonts/kongtext/kongtext.svg kongtext.svg COPYONLY)

# for tests.
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/textures/test3x3.bmp test3x3.bmp COPYONLY)

# Ajokki
add_executable(ajokki
    # callback_system, in alphabetical order
    cpp/ylikuutio/callback_system/callback_engine.cpp
    cpp/ylikuutio/callback_system/callback_engine.hpp
    cpp/ylikuutio/callback_system/callback_magic_numbers.hpp
    cpp/ylikuutio/callback_system/callback_object.cpp
    cpp/ylikuutio/callback_system/callback_object.hpp
    cpp/ylikuutio/callback_system/callback_parameter.cpp
    cpp/ylikuutio/callback_system/callback_parameter.hpp
    cpp/ylikuutio/callback_system/key_and_callback_struct.hpp

    # common, in alphabetical order
    cpp/ylikuutio/common/any_value.cpp
    cpp/ylikuutio/common/any_value.hpp
    cpp/ylikuutio/common/global_variables.cpp
    cpp/ylikuutio/common/global_variables.hpp
    cpp/ylikuutio/common/globals.hpp

    # console, in alphabetical order.
    cpp/ylikuutio/console/console.cpp
    cpp/ylikuutio/console/console.hpp
    cpp/ylikuutio/console/console_callback_object.cpp
    cpp/ylikuutio/console/console_callback_object.hpp

    # file, in alphabetical order.
    cpp/ylikuutio/file/file_loader.cpp
    cpp/ylikuutio/file/file_loader.hpp

    # geometry, in alphabetical order.
    cpp/ylikuutio/geometry/bilinear_interpolation.cpp
    cpp/ylikuutio/geometry/bilinear_interpolation.hpp
    cpp/ylikuutio/geometry/chunk.cpp
    cpp/ylikuutio/geometry/chunk.hpp
    cpp/ylikuutio/geometry/indexing.cpp
    cpp/ylikuutio/geometry/indexing.hpp
    cpp/ylikuutio/geometry/line.cpp
    cpp/ylikuutio/geometry/line.hpp
    cpp/ylikuutio/geometry/line2D.cpp
    cpp/ylikuutio/geometry/line2D.hpp
    cpp/ylikuutio/geometry/line3D.cpp
    cpp/ylikuutio/geometry/line3D.hpp
    cpp/ylikuutio/geometry/line_line_intersection.cpp
    cpp/ylikuutio/geometry/line_line_intersection.hpp
    cpp/ylikuutio/geometry/line_segment.cpp
    cpp/ylikuutio/geometry/line_segment.hpp
    cpp/ylikuutio/geometry/line_segment2D.cpp
    cpp/ylikuutio/geometry/line_segment2D.hpp
    cpp/ylikuutio/geometry/line_segment3D.cpp
    cpp/ylikuutio/geometry/line_segment3D.hpp
    cpp/ylikuutio/geometry/line_segment_line_segment_intersection.cpp
    cpp/ylikuutio/geometry/line_segment_line_segment_intersection.hpp
    cpp/ylikuutio/geometry/polygon_triangulation.cpp
    cpp/ylikuutio/geometry/polygon_triangulation.hpp
    cpp/ylikuutio/geometry/quad_triangulation.cpp
    cpp/ylikuutio/geometry/quad_triangulation.hpp
    cpp/ylikuutio/geometry/transformation.cpp
    cpp/ylikuutio/geometry/transformation.hpp
    cpp/ylikuutio/geometry/triangulation_macros.cpp

    # graph, in alphabetical order.
    cpp/ylikuutio/graph/graph.cpp
    cpp/ylikuutio/graph/graph.hpp
    cpp/ylikuutio/graph/node.cpp
    cpp/ylikuutio/graph/node.hpp

    # hierarchy, in alphabetical order.
    cpp/ylikuutio/hierarchy/hierarchy_templates.hpp

    # ontology, in alphabetical order
    cpp/ylikuutio/ontology/font_loader.cpp
    cpp/ylikuutio/ontology/font_loader.hpp
    cpp/ylikuutio/ontology/glyph.cpp
    cpp/ylikuutio/ontology/glyph.hpp
    cpp/ylikuutio/ontology/ground_level.cpp
    cpp/ylikuutio/ontology/ground_level.hpp
    cpp/ylikuutio/ontology/heightmap_loader.cpp
    cpp/ylikuutio/ontology/heightmap_loader.hpp
    cpp/ylikuutio/ontology/material.cpp
    cpp/ylikuutio/ontology/material.hpp
    cpp/ylikuutio/ontology/model.cpp
    cpp/ylikuutio/ontology/model.hpp
    cpp/ylikuutio/ontology/object.cpp
    cpp/ylikuutio/ontology/object.hpp
    cpp/ylikuutio/ontology/objloader.cpp
    cpp/ylikuutio/ontology/objloader.hpp
    cpp/ylikuutio/ontology/render_templates.hpp
    cpp/ylikuutio/ontology/scene.cpp
    cpp/ylikuutio/ontology/scene.hpp
    cpp/ylikuutio/ontology/shader.cpp
    cpp/ylikuutio/ontology/shader.hpp
    cpp/ylikuutio/ontology/shader_loader.cpp
    cpp/ylikuutio/ontology/shader_loader.hpp
    cpp/ylikuutio/ontology/species.cpp
    cpp/ylikuutio/ontology/species.hpp
    cpp/ylikuutio/ontology/species_or_glyph.hpp
    cpp/ylikuutio/ontology/text2D.cpp
    cpp/ylikuutio/ontology/text2D.hpp
    cpp/ylikuutio/ontology/text3D.hpp
    cpp/ylikuutio/ontology/text3D.cpp
    cpp/ylikuutio/ontology/texture_loader.cpp
    cpp/ylikuutio/ontology/texture_loader.hpp
    cpp/ylikuutio/ontology/universe.cpp
    cpp/ylikuutio/ontology/universe.hpp
    cpp/ylikuutio/ontology/vector_font.cpp
    cpp/ylikuutio/ontology/vector_font.hpp
    cpp/ylikuutio/ontology/vboindexer.cpp
    cpp/ylikuutio/ontology/vboindexer.hpp

    # shaders, in alphabetical order
    cpp/ylikuutio/shaders/StandardShading.fragmentshader
    cpp/ylikuutio/shaders/StandardShading.vertexshader
    cpp/ylikuutio/shaders/TransformVertexShader.vertexshader
    cpp/ylikuutio/shaders/TextureFragmentShader.fragmentshader
    cpp/ylikuutio/shaders/TextVertexShader.fragmentshader
    cpp/ylikuutio/shaders/TextVertexShader.vertexshader

    # string, in alphabetical order
    cpp/ylikuutio/string/ylikuutio_string.cpp
    cpp/ylikuutio/string/ylikuutio_string.hpp

    # ajokki, in alphabetical order
    cpp/ajokki/ajokki.cpp
    cpp/ajokki/ajokki_callbacks.cpp
    cpp/ajokki/ajokki_callbacks.hpp
    )
add_dependencies(ajokki rescan)
target_link_libraries(ajokki ${ALL_LIBS} glfw)
if(${eigen_FOUND})
    # target_link_libraries(ajokki ${eigen_LIBRARY})
    target_link_libraries(ajokki ${ALL_LIBS})
endif()

# Xcode and Visual working directories
set_target_properties(ajokki PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ajokki/")
create_target_launcher(ajokki WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ajokki/")

# Tests
if(DO_UNIT_TESTS_WITH_CATCH)
    include_directories(
        external/Catch/single_include/
        )

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
        cpp/ylikuutio/callback_system/callback_engine.cpp
        cpp/ylikuutio/callback_system/callback_engine.hpp
        cpp/ylikuutio/callback_system/callback_object.cpp
        cpp/ylikuutio/callback_system/callback_object.hpp
        cpp/ylikuutio/callback_system/callback_parameter.cpp
        cpp/ylikuutio/callback_system/callback_parameter.hpp
        cpp/ylikuutio/common/any_value.cpp
        cpp/ylikuutio/common/any_value.hpp
        cpp/ylikuutio/common/globals.hpp
        cpp/ylikuutio/file/file_loader.cpp
        cpp/ylikuutio/file/file_loader.hpp
        cpp/ylikuutio/geometry/bilinear_interpolation.cpp
        cpp/ylikuutio/geometry/bilinear_interpolation.hpp
        cpp/ylikuutio/geometry/indexing.cpp
        cpp/ylikuutio/geometry/indexing.hpp
        cpp/ylikuutio/geometry/line.cpp
        cpp/ylikuutio/geometry/line.hpp
        cpp/ylikuutio/geometry/line2D.cpp
        cpp/ylikuutio/geometry/line2D.hpp
        cpp/ylikuutio/geometry/line_line_intersection.cpp
        cpp/ylikuutio/geometry/line_line_intersection.hpp
        cpp/ylikuutio/geometry/line_segment2D.cpp
        cpp/ylikuutio/geometry/line_segment2D.hpp
        cpp/ylikuutio/geometry/line_segment_line_segment_intersection.cpp
        cpp/ylikuutio/geometry/line_segment_line_segment_intersection.hpp
        cpp/ylikuutio/geometry/quad_triangulation.cpp
        cpp/ylikuutio/geometry/quad_triangulation.hpp
        cpp/ylikuutio/geometry/transformation.cpp
        cpp/ylikuutio/geometry/transformation.hpp
        cpp/ylikuutio/hierarchy/hierarchy_templates.hpp
        cpp/ylikuutio/ontology/font_loader.cpp
        cpp/ylikuutio/ontology/font_loader.hpp
        cpp/ylikuutio/string/ylikuutio_string.cpp
        cpp/ylikuutio/string/ylikuutio_string.hpp
        )
    set(UNIT_TESTS
        cpp/ylikuutio/tests/googletest/test_any_value.cpp
        cpp/ylikuutio/tests/googletest/test_callback_system.cpp
        cpp/ylikuutio/tests/googletest/test_eigen.cpp
        cpp/ylikuutio/tests/googletest/test_file_loader.cpp
        cpp/ylikuutio/tests/googletest/test_font_loader.cpp
        cpp/ylikuutio/tests/googletest/test_globals.cpp
        cpp/ylikuutio/tests/googletest/test_heightmap_loader.cpp
        cpp/ylikuutio/tests/googletest/test_line2D.cpp
        cpp/ylikuutio/tests/googletest/test_line_line_intersection.cpp
        cpp/ylikuutio/tests/googletest/test_line_segment_line_segment_intersection.cpp
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
