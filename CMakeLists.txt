# CMake entry point
cmake_minimum_required(VERSION 2.6.2)
project(ylikuutio)

# http://stackoverflow.com/questions/11783932/how-to-add-linker-or-compile-flag-in-cmake-file/11797272#11797272
# SET(GCC_COVERAGE_LINK_FLAGS "-ldl")
# SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# comment the following line to disable scripting with TinyScheme.
set(ENABLE_SCRIPTING_WITH_TINYSCHEME true)

# comment the following line to disable unit tests with Google Test.
set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)

# uncomment the following line to download the latest versions of external projects
# instead of using the versions carried in Ylikuutio repository (in `external/`).
# this does not affect any library at the moment (did affect Eigen earlier, though).
# set(ENABLE_DOWNLOAD_LATEST_VERSIONS_OF_EXTERNAL_PROJECTS)

# uncomment the following line to disable updating of external projects.
set(DISABLE_UPDATE_STEP true)

if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Android")
    find_library(OpenGL REQUIRED)
else()
    find_package(OpenGL REQUIRED)
endif()

find_package(Threads REQUIRED)

# Compile external dependencies
add_subdirectory (external)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

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

# Do not compile GLFW tests, examples and documentation.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(
    external/assimp/include/
    external/FastNoiseSIMD/
    external/glew-2.0.0/include/
    external/glfw-3.2/include/
    external/glm/
    external/pugixml/src/
    .
    )

if(ENABLE_SCRIPTING_WITH_TINYSCHEME)
    include_directories(
        external/tinyscheme-1.41/
        )
endif()

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

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    assimp
    glfw
    GLEW_200
    pugixml
    )

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    )

# for general use.
configure_file(code/ylikuutio/shaders/TransformVertexShader.vertexshader TransformVertexShader.vertexshader COPYONLY)
configure_file(code/ylikuutio/shaders/TextureFragmentShader.fragmentshader TextureFragmentShader.fragmentshader COPYONLY)
configure_file(code/ylikuutio/shaders/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(code/ylikuutio/shaders/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(code/ylikuutio/shaders/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(code/ylikuutio/shaders/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)
configure_file(code/tinyscheme/hello_world.scm hello_world.scm COPYONLY)
configure_file(external/tinyscheme-1.41/init.scm init.scm COPYONLY)
configure_file(res/objects/custom/suzanne.obj suzanne.obj COPYONLY)
configure_file(res/objects/snow_cottage_triangulated.obj snow_cottage_triangulated.obj COPYONLY)
configure_file(res/textures/uvmap.DDS uvmap.DDS COPYONLY)
configure_file(res/textures/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(res/textures/pavers1b2.bmp pavers1b2.bmp COPYONLY)
configure_file(res/textures/numbers_123456_black_and_white.bmp numbers_123456_black_and_white.bmp COPYONLY)
configure_file(res/fonts/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(res/fonts/Holstein.bmp Holstein.bmp COPYONLY)
configure_file(res/height_maps/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/height_maps/noise128x128.bmp noise128x128.bmp COPYONLY)
configure_file(res/height_maps/S17W069.hgt S17W069.hgt COPYONLY)
configure_file(res/height_maps/L4133D.asc L4133D.asc COPYONLY)
configure_file(res/height_maps/N5424G.asc N5424G.asc COPYONLY)
configure_file(res/laser_scanning_data/L4133D1.laz L4133D1.laz COPYONLY)
configure_file(res/fonts/kongtext/kongtext.svg kongtext.svg COPYONLY)
configure_file(res/maps/Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm COPYONLY)
configure_file(res/maps/Exactum_Physicum_Helsinki_Finland.osm Exactum_Physicum_Helsinki_Finland.osm COPYONLY)

# for tests.
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/textures/test3x3.bmp test3x3.bmp COPYONLY)

# Ylikuutio
add_library(ylikuutio STATIC
    # callback_system, in alphabetical order
    code/ylikuutio/callback_system/callback_engine.cpp
    code/ylikuutio/callback_system/callback_engine.hpp
    code/ylikuutio/callback_system/callback_magic_numbers.hpp
    code/ylikuutio/callback_system/callback_object.cpp
    code/ylikuutio/callback_system/callback_object.hpp
    code/ylikuutio/callback_system/callback_parameter.cpp
    code/ylikuutio/callback_system/callback_parameter.hpp
    code/ylikuutio/callback_system/key_and_callback_struct.hpp

    # common, in alphabetical order
    code/ylikuutio/common/any_value.cpp
    code/ylikuutio/common/any_value.hpp
    code/ylikuutio/common/globals.hpp
    code/ylikuutio/common/pi.hpp
    code/ylikuutio/common/spherical_coordinates_struct.hpp

    # config, in alphabetical order.
    code/ylikuutio/config/setting.cpp
    code/ylikuutio/config/setting.hpp
    code/ylikuutio/config/setting_master.cpp
    code/ylikuutio/config/setting_master.hpp

    # console, in alphabetical order.
    code/ylikuutio/console/command_and_callback_struct.hpp
    code/ylikuutio/console/console.cpp
    code/ylikuutio/console/console.hpp
    code/ylikuutio/console/console_command_callback.hpp
    code/ylikuutio/console/console_struct.hpp
    code/ylikuutio/console/console_callback_object.cpp
    code/ylikuutio/console/console_callback_object.hpp

    # file, in alphabetical order.
    code/ylikuutio/file/file_loader.cpp
    code/ylikuutio/file/file_loader.hpp

    # geometry, in alphabetical order.
    code/ylikuutio/geometry/line.cpp
    code/ylikuutio/geometry/line.hpp
    code/ylikuutio/geometry/line2D.cpp
    code/ylikuutio/geometry/line2D.hpp
    code/ylikuutio/geometry/line3D.cpp
    code/ylikuutio/geometry/line3D.hpp
    code/ylikuutio/geometry/line_line_intersection.cpp
    code/ylikuutio/geometry/line_line_intersection.hpp
    code/ylikuutio/geometry/line_segment.cpp
    code/ylikuutio/geometry/line_segment.hpp
    code/ylikuutio/geometry/line_segment2D.cpp
    code/ylikuutio/geometry/line_segment2D.hpp
    code/ylikuutio/geometry/line_segment3D.cpp
    code/ylikuutio/geometry/line_segment3D.hpp
    code/ylikuutio/geometry/line_segment_line_segment_intersection.cpp
    code/ylikuutio/geometry/line_segment_line_segment_intersection.hpp
    code/ylikuutio/geometry/spherical_world_struct.hpp
    code/ylikuutio/geometry/transformation.cpp
    code/ylikuutio/geometry/transformation.hpp
    code/ylikuutio/geometry/transformation_struct.hpp

    # graph, in alphabetical order.
    code/ylikuutio/graph/graph.cpp
    code/ylikuutio/graph/graph.hpp
    code/ylikuutio/graph/node.cpp
    code/ylikuutio/graph/node.hpp
    code/ylikuutio/graph/node_struct.hpp

    # hierarchy, in alphabetical order.
    code/ylikuutio/hierarchy/hierarchy_templates.hpp

    # interpolation, in alphabetical order
    code/ylikuutio/interpolation/bilinear_interpolation2D.hpp

    # linear algebra, in alphabetical order.
    code/ylikuutio/linear_algebra/matrix.cpp
    code/ylikuutio/linear_algebra/matrix.hpp
    code/ylikuutio/linear_algebra/matrix_functions.cpp
    code/ylikuutio/linear_algebra/matrix_functions.hpp
    code/ylikuutio/linear_algebra/tensor3.cpp
    code/ylikuutio/linear_algebra/tensor3.hpp

    # loaders, in alphabetical order.
    code/ylikuutio/loaders/ascii_grid_loader.cpp
    code/ylikuutio/loaders/ascii_grid_loader.hpp
    code/ylikuutio/loaders/bmp_heightmap_loader.cpp
    code/ylikuutio/loaders/bmp_heightmap_loader.hpp
    code/ylikuutio/loaders/bmp_loader.cpp
    code/ylikuutio/loaders/bmp_loader.hpp
    code/ylikuutio/loaders/font_loader.cpp
    code/ylikuutio/loaders/font_loader.hpp
    code/ylikuutio/loaders/las_loader.cpp
    code/ylikuutio/loaders/las_loader.hpp
    code/ylikuutio/loaders/obj_loader.cpp
    code/ylikuutio/loaders/obj_loader.hpp
    code/ylikuutio/loaders/shader_loader.cpp
    code/ylikuutio/loaders/shader_loader.hpp
    code/ylikuutio/loaders/species_loader.cpp
    code/ylikuutio/loaders/species_loader.hpp
    code/ylikuutio/loaders/species_loader_struct.hpp
    code/ylikuutio/loaders/srtm_heightmap_loader.cpp
    code/ylikuutio/loaders/srtm_heightmap_loader.hpp
    code/ylikuutio/loaders/texture_loader.cpp
    code/ylikuutio/loaders/texture_loader.hpp

    # map, in alphabetical order
    code/ylikuutio/map/ylikuutio_map.hpp

    # ontology, in alphabetical order
    code/ylikuutio/ontology/entity.cpp
    code/ylikuutio/ontology/entity.hpp
    code/ylikuutio/ontology/entity_factory.cpp
    code/ylikuutio/ontology/entity_factory.hpp
    code/ylikuutio/ontology/entity_templates.hpp
    code/ylikuutio/ontology/font2D.cpp
    code/ylikuutio/ontology/font2D.hpp
    code/ylikuutio/ontology/glyph.cpp
    code/ylikuutio/ontology/glyph.hpp
    code/ylikuutio/ontology/glyph_struct.hpp
    code/ylikuutio/ontology/ground_level.cpp
    code/ylikuutio/ontology/ground_level.hpp
    code/ylikuutio/ontology/info_struct.hpp
    code/ylikuutio/ontology/material.cpp
    code/ylikuutio/ontology/material.hpp
    code/ylikuutio/ontology/material_struct.hpp
    code/ylikuutio/ontology/model.cpp
    code/ylikuutio/ontology/model.hpp
    code/ylikuutio/ontology/object.cpp
    code/ylikuutio/ontology/object.hpp
    code/ylikuutio/ontology/object_struct.hpp
    code/ylikuutio/ontology/render_templates.hpp
    code/ylikuutio/ontology/scene.cpp
    code/ylikuutio/ontology/scene.hpp
    code/ylikuutio/ontology/shader.cpp
    code/ylikuutio/ontology/shader.hpp
    code/ylikuutio/ontology/shader_struct.hpp
    code/ylikuutio/ontology/species.cpp
    code/ylikuutio/ontology/species.hpp
    code/ylikuutio/ontology/species_or_glyph.hpp
    code/ylikuutio/ontology/species_struct.hpp
    code/ylikuutio/ontology/symbiosis.cpp
    code/ylikuutio/ontology/symbiosis.hpp
    code/ylikuutio/ontology/symbiosis_struct.hpp
    code/ylikuutio/ontology/text3D.hpp
    code/ylikuutio/ontology/text3D.cpp
    code/ylikuutio/ontology/text3D_struct.hpp
    code/ylikuutio/ontology/universe.cpp
    code/ylikuutio/ontology/universe.hpp
    code/ylikuutio/ontology/vector_font.cpp
    code/ylikuutio/ontology/vector_font.hpp
    code/ylikuutio/ontology/vector_font_struct.hpp
    code/ylikuutio/ontology/vboindexer.cpp
    code/ylikuutio/ontology/vboindexer.hpp

    # shaders, in alphabetical order
    code/ylikuutio/shaders/StandardShading.fragmentshader
    code/ylikuutio/shaders/StandardShading.vertexshader
    code/ylikuutio/shaders/TransformVertexShader.vertexshader
    code/ylikuutio/shaders/TextureFragmentShader.fragmentshader
    code/ylikuutio/shaders/TextVertexShader.fragmentshader
    code/ylikuutio/shaders/TextVertexShader.vertexshader

    # space partition, in alphabetical order.
    code/ylikuutio/space_partition/chunk.cpp
    code/ylikuutio/space_partition/chunk.hpp
    code/ylikuutio/space_partition/chunk_master.cpp
    code/ylikuutio/space_partition/chunk_master.hpp
    code/ylikuutio/space_partition/terrain_generation_callbacks.cpp
    code/ylikuutio/space_partition/terrain_generation_callbacks.hpp
    code/ylikuutio/space_partition/vertex_graph.cpp
    code/ylikuutio/space_partition/vertex_graph.hpp
    code/ylikuutio/space_partition/vertex_node.cpp
    code/ylikuutio/space_partition/vertex_node.hpp

    # string, in alphabetical order
    code/ylikuutio/string/ylikuutio_string.cpp
    code/ylikuutio/string/ylikuutio_string.hpp

    # triangulation, in alphabetical order
    code/ylikuutio/triangulation/face_normals.cpp
    code/ylikuutio/triangulation/face_normals.hpp
    code/ylikuutio/triangulation/indexing.hpp
    code/ylikuutio/triangulation/polygon_triangulation.cpp
    code/ylikuutio/triangulation/polygon_triangulation.hpp
    code/ylikuutio/triangulation/quad_triangulation.hpp
    code/ylikuutio/triangulation/triangulate_polygons_struct.hpp
    code/ylikuutio/triangulation/triangulate_quads_struct.hpp
    code/ylikuutio/triangulation/triangulation_enums.hpp
    code/ylikuutio/triangulation/triangulation_templates.hpp
    code/ylikuutio/triangulation/vertex_normals.cpp
    code/ylikuutio/triangulation/vertex_normals.hpp
    code/ylikuutio/triangulation/vertices.cpp
    code/ylikuutio/triangulation/vertices.hpp
    )
# add_dependencies(ylikuutio rescan)

# Ajokki
add_executable(ajokki
    # ajokki, in alphabetical order
    code/ajokki/ajokki.cpp
    code/ajokki/ajokki_background_colors.cpp
    code/ajokki/ajokki_background_colors.hpp
    code/ajokki/ajokki_cleanup_callbacks.cpp
    code/ajokki/ajokki_cleanup_callbacks.hpp
    code/ajokki/ajokki_console.cpp
    code/ajokki/ajokki_console.hpp
    code/ajokki/ajokki_console_callbacks.cpp
    code/ajokki/ajokki_console_callbacks.hpp
    code/ajokki/ajokki_debug.cpp
    code/ajokki/ajokki_debug.hpp
    code/ajokki/ajokki_keyboard_callbacks.cpp
    code/ajokki/ajokki_keyboard_callbacks.hpp
    code/ajokki/ajokki_location_and_orientation.cpp
    code/ajokki/ajokki_location_and_orientation.hpp
    code/ajokki/ajokki_movement.cpp
    code/ajokki/ajokki_movement.hpp
    )
add_dependencies(ajokki rescan)
target_link_libraries(ajokki ylikuutio ${ALL_LIBS})

if (ENABLE_SCRIPTING_WITH_TINYSCHEME)
    # TinyScheme-test
    add_executable(tinyscheme_test code/tinyscheme/tinyscheme_test.cpp
        )
    target_link_libraries(tinyscheme_test tinyscheme)
endif()

# Xcode and Visual working directories
set_target_properties(ajokki PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")
set_target_properties(ajokki PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code/ajokki/")
create_target_launcher(ajokki WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/code/ajokki/")

# Tests
if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    set(FILES_TO_TEST
        code/ylikuutio/callback_system/callback_engine.cpp
        code/ylikuutio/callback_system/callback_engine.hpp
        code/ylikuutio/callback_system/callback_object.cpp
        code/ylikuutio/callback_system/callback_object.hpp
        code/ylikuutio/callback_system/callback_parameter.cpp
        code/ylikuutio/callback_system/callback_parameter.hpp
        code/ylikuutio/common/any_value.cpp
        code/ylikuutio/common/any_value.hpp
        code/ylikuutio/common/globals.hpp
        code/ylikuutio/file/file_loader.cpp
        code/ylikuutio/file/file_loader.hpp
        code/ylikuutio/geometry/line.cpp
        code/ylikuutio/geometry/line.hpp
        code/ylikuutio/geometry/line2D.cpp
        code/ylikuutio/geometry/line2D.hpp
        code/ylikuutio/geometry/line_line_intersection.cpp
        code/ylikuutio/geometry/line_line_intersection.hpp
        code/ylikuutio/geometry/line_segment2D.cpp
        code/ylikuutio/geometry/line_segment2D.hpp
        code/ylikuutio/geometry/line_segment_line_segment_intersection.cpp
        code/ylikuutio/geometry/line_segment_line_segment_intersection.hpp
        code/ylikuutio/geometry/transformation.cpp
        code/ylikuutio/geometry/transformation.hpp
        code/ylikuutio/graph/node_struct.hpp
        code/ylikuutio/hierarchy/hierarchy_templates.hpp
        code/ylikuutio/interpolation/bilinear_interpolation2D.hpp
        code/ylikuutio/linear_algebra/matrix.cpp
        code/ylikuutio/linear_algebra/matrix.hpp
        code/ylikuutio/linear_algebra/matrix_functions.cpp
        code/ylikuutio/linear_algebra/matrix_functions.hpp
        code/ylikuutio/linear_algebra/tensor3.cpp
        code/ylikuutio/linear_algebra/tensor3.hpp
        code/ylikuutio/loaders/font_loader.cpp
        code/ylikuutio/loaders/font_loader.hpp
        code/ylikuutio/ontology/glyph_struct.hpp
        code/ylikuutio/ontology/material_struct.hpp
        code/ylikuutio/ontology/object_struct.hpp
        code/ylikuutio/ontology/shader_struct.hpp
        code/ylikuutio/ontology/species_struct.hpp
        code/ylikuutio/ontology/text3D_struct.hpp
        code/ylikuutio/ontology/vector_font_struct.hpp
        code/ylikuutio/string/ylikuutio_string.cpp
        code/ylikuutio/string/ylikuutio_string.hpp
        code/ylikuutio/triangulation/face_normals.cpp
        code/ylikuutio/triangulation/face_normals.hpp
        code/ylikuutio/triangulation/indexing.hpp
        code/ylikuutio/triangulation/quad_triangulation.hpp
        code/ylikuutio/triangulation/triangulate_quads_struct.hpp
        code/ylikuutio/triangulation/triangulation_enums.hpp
        code/ylikuutio/triangulation/vertex_normals.cpp
        code/ylikuutio/triangulation/vertex_normals.hpp
        code/ylikuutio/triangulation/vertices.cpp
        code/ylikuutio/triangulation/vertices.hpp
        )
    set(UNIT_TESTS
        code/ylikuutio/tests/googletest/test_any_value.cpp
        code/ylikuutio/tests/googletest/test_bilinear_interpolation2D.cpp
        code/ylikuutio/tests/googletest/test_callback_system.cpp
        code/ylikuutio/tests/googletest/test_file_loader.cpp
        code/ylikuutio/tests/googletest/test_font_loader.cpp
        code/ylikuutio/tests/googletest/test_node_struct.cpp
        code/ylikuutio/tests/googletest/test_shader_struct.cpp
        code/ylikuutio/tests/googletest/test_material_struct.cpp
        code/ylikuutio/tests/googletest/test_species_struct.cpp
        code/ylikuutio/tests/googletest/test_vector_font_struct.cpp
        code/ylikuutio/tests/googletest/test_glyph_struct.cpp
        code/ylikuutio/tests/googletest/test_object_struct.cpp
        code/ylikuutio/tests/googletest/test_heightmap_loader.cpp
        code/ylikuutio/tests/googletest/test_line2D.cpp
        code/ylikuutio/tests/googletest/test_line_line_intersection.cpp
        code/ylikuutio/tests/googletest/test_line_segment_line_segment_intersection.cpp
        code/ylikuutio/tests/googletest/test_linear_algebra.cpp
        code/ylikuutio/tests/googletest/test_pugixml.cpp
        code/ylikuutio/tests/googletest/test_ylikuutio_string.cpp)
    set(MAIN_FILE code/ylikuutio/tests/googletest/main.cpp)

    add_library(codeToTest ${FILES_TO_TEST})

    add_executable(do_tests_googletest ${MAIN_FILE})
    target_link_libraries(do_tests_googletest codeToTest)

    add_executable(unit_tests_with_Google_Test code/ylikuutio/tests/googletest/test_main.cpp ${UNIT_TESTS})
    target_link_libraries(unit_tests_with_Google_Test gtest libgtest rt pthread codeToTest)

    # Xcode and Visual working directories
    set_target_properties(unit_tests_with_Google_Test PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code/tests/googletest/")
    create_target_launcher(unit_tests_with_Google_Test WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/code/tests/googletest/")
endif()

source_group(common REGULAR_EXPRESSION ".*/code/common/.*" )
source_group(shaders REGULAR_EXPRESSION ".*/.*shader$" )
