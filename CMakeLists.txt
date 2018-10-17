# CMake entry point
cmake_minimum_required(VERSION 2.6.2)
project(ylikuutio)

# http://stackoverflow.com/questions/11783932/how-to-add-linker-or-compile-flag-in-cmake-file/11797272#11797272
# SET(GCC_COVERAGE_LINK_FLAGS "-ldl")
# SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# comment the following line to disable scripting with S7 Scheme.
set(ENABLE_SCRIPTING_WITH_S7_SCHEME true)

# comment the following line to use `libsdl2-dev` shipped with Linux.
set(COMPILE_SDL_FROM_SOURCE true)

# comment the following line to use `libsfml-dev` shipped with Linux.
set(COMPILE_SFML_FROM_SOURCE true)

# comment the following line to disable unit tests with Google Test.
# set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)

# uncomment the following line to disable updating of external projects.
set(DISABLE_UPDATE_STEP true)

if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Android")
    find_library(OpenGL REQUIRED)
else()
    find_package(OpenGL REQUIRED)
endif()

find_package(Threads REQUIRED)

if (NOT(COMPILE_SFML_FROM_SOURCE))
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
    find_package(SFML 2 REQUIRED system audio)
endif()

if (NOT(COMPILE_SDL_FROM_SOURCE))
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
    find_package(SDL2 REQUIRED)
endif()

if (NOT(COMPILE_SDL_FROM_SOURCE))
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
endif()

# Compile external dependencies
add_subdirectory (external)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSFML_STATIC -std=c++14 -O3 -Wall")

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

if (COMPILE_SFML_FROM_SOURCE)
    include_directories(
        external/SFML-2.4.2/include/
        external/SFML-2.4.2/src
        external/SFML-2.4.2/extlibs/headers/
        external/SFML-2.4.2/extlibs/headers/AL/
        )
else()
    include_directories(
        ${SFML_INCLUDE_DIR}
        )
endif()

if(COMPILE_SDL_FROM_SOURCE)
    include_directories(
        external/SDL2-2.0.8/include/
        )
else()
    include_directories(
        ${SDL2_INCLUDE_DIRS}
        )
endif()

include_directories(
    # external/asio/asio/include/
    external/assimp/include/
    external/FastNoiseSIMD/
    external/glew-2.0.0/include/
    external/glm/
    external/OpenFBX/src/
    external/pugixml/src/
    .
    )

if(ENABLE_SCRIPTING_WITH_S7_SCHEME)
    include_directories(
        external/s7/
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
            # custom patch command
            PATCH_COMMAND git reset --hard 77962730563eece3525f40b8769e4ca0c6baf64c
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
            # custom patch command
            PATCH_COMMAND git reset --hard 77962730563eece3525f40b8769e4ca0c6baf64c
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
            # custom patch command
            PATCH_COMMAND git reset --hard 77962730563eece3525f40b8769e4ca0c6baf64c
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
            # custom patch command
            PATCH_COMMAND git reset --hard 77962730563eece3525f40b8769e4ca0c6baf64c
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
    GLEW_200
    pugixml
    miniz
    OpenFBX
    )

if (COMPILE_SFML_FROM_SOURCE)
    set(ALL_LIBS
        ${ALL_LIBS}
        sfml-system
        sfml-audio
        )
else()
    set(ALL_LIBS
        ${ALL_LIBS}
        ${SFML_LIBRARIES}
        )
endif()


if (COMPILE_SDL_FROM_SOURCE)
    set(ALL_LIBS
        ${ALL_LIBS}
        SDL2-static
        )
else()
    set(ALL_LIBS
        ${ALL_LIBS}
        ${SDL2_LIBRARIES}
        )
endif()

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    )

# Shaders.
configure_file(code/ylikuutio/shaders/StandardShading.vertexshader StandardShading.vertexshader COPYONLY)
configure_file(code/ylikuutio/shaders/StandardShading.fragmentshader StandardShading.fragmentshader COPYONLY)
configure_file(code/ylikuutio/shaders/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(code/ylikuutio/shaders/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)

# S7 Scheme code.
configure_file(code/s7/hello_world.scm hello_world.scm COPYONLY)

# 3D models.
# Suzanne.
configure_file(res/objects/custom/suzanne.obj suzanne.obj COPYONLY)
# Freight train.
configure_file(res/objects/www.blendswap.com/46359_freight_train/freight_train.fbx freight_train.fbx COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_chassis.bmp freight_train_chassis.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_box_expage.bmp freight_train_box_expage.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_body.bmp freight_train_body.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_expage1.bmp freight_train_expage1.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_expage2.bmp freight_train_expage2.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_gray_concrete.bmp freight_train_gray_concrete.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_iron_texture_by_pabloalvin.bmp freight_train_iron_texture_by_pabloalvin.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_stone.bmp freight_train_stone.bmp COPYONLY)
# Turbo polizei.
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/turbo_polizei.fbx turbo_polizei.fbx COPYONLY)
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/textures/car.png car.png COPYONLY)
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/textures/wheell.png wheell.png COPYONLY)
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/textures/car.bmp car.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/textures/wheell.bmp wheell.bmp COPYONLY)
# Fantasy house with balcony.
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/fantasy_house_with_balcony.fbx fantasy_house_with_balcony.fbx COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_bricks.bmp fantasy_house_with_balcony_bricks.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_copper_roof.bmp fantasy_house_with_balcony_copper_roof.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_door2.bmp fantasy_house_with_balcony_door2.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_door3.bmp fantasy_house_with_balcony_door3.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_plaster.bmp fantasy_house_with_balcony_plaster.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_roof.bmp fantasy_house_with_balcony_roof.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_stone_wall.bmp fantasy_house_with_balcony_stone_wall.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_window.bmp fantasy_house_with_balcony_window.bmp COPYONLY)
configure_file(res/objects/www.blendswap.com/55007_fantasy_house_with_balcony/textures/fantasy_house_with_balcony_wood_floor.bmp fantasy_house_with_balcony_wood_floor.bmp COPYONLY)
# Horse.
configure_file(res/objects/www.blendswap.com/76528_horse/horse.fbx horse.fbx COPYONLY)
# Cat.
configure_file(res/objects/www.blendswap.com/86110_rigged_and_animated_cat/cat.fbx cat.fbx COPYONLY)

# Textures.
configure_file(res/textures/GrassGreenTexture0002.bmp GrassGreenTexture0002.bmp COPYONLY)
configure_file(res/textures/orange_fur_texture.bmp orange_fur_texture.bmp COPYONLY)
configure_file(res/textures/pavers1b2.bmp pavers1b2.bmp COPYONLY)
configure_file(res/textures/numbers_123456_black_and_white.bmp numbers_123456_black_and_white.bmp COPYONLY)

# Fonts.
configure_file(res/fonts/kongtext/kongtext.svg kongtext.svg COPYONLY)
configure_file(res/fonts/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(res/fonts/Holstein.bmp Holstein.bmp COPYONLY)

# Maps.
configure_file(res/height_maps/noise1024x1024.bmp noise1024x1024.bmp COPYONLY)
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/height_maps/noise128x128.bmp noise128x128.bmp COPYONLY)
configure_file(res/height_maps/N59E024.hgt N59E024.hgt COPYONLY)
configure_file(res/height_maps/S17W069.hgt S17W069.hgt COPYONLY)
configure_file(res/height_maps/L4133D.asc L4133D.asc COPYONLY)
configure_file(res/height_maps/N5424G.asc N5424G.asc COPYONLY)
configure_file(res/height_maps/test_3x3_0_1_2_4_8_16_32_64_128.asc test_3x3_0_1_2_4_8_16_32_64_128.asc COPYONLY)
configure_file(res/laser_scanning_data/L4133D1.laz L4133D1.laz COPYONLY)
configure_file(res/maps/Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm COPYONLY)
configure_file(res/maps/Exactum_Physicum_Helsinki_Finland.osm Exactum_Physicum_Helsinki_Finland.osm COPYONLY)

# Audio.
configure_file(res/audio/freesound.org/395487__frankum__tecno-pop-base-and-guitar-2.ogg 395487__frankum__tecno-pop-base-and-guitar-2.ogg COPYONLY)
configure_file(res/audio/freesound.org/414257__sss-samples__chipland-loop-120-bpm-a-major.wav 414257__sss-samples__chipland-loop-120-bpm-a-major.wav COPYONLY)
configure_file(res/audio/freesound.org/414269__jpmusic82__arp-bass-loop-128-bpm.mp3 414269__jpmusic82__arp-bass-loop-128-bpm.mp3 COPYONLY)
configure_file(res/audio/freesound.org/414270__greek555__sample-97-bpm.wav 414270__greek555__sample-97-bpm.wav COPYONLY)
configure_file(res/audio/freesound.org/416882__greek555__blue-play.ogg 416882__greek555__blue-play.ogg COPYONLY)
configure_file(res/audio/freesound.org/419588__greek555__dreaming-of-me.ogg 419588__greek555__dreaming-of-me.ogg COPYONLY)

# Image files for tests.
configure_file(res/height_maps/noise256x256.bmp noise256x256.bmp COPYONLY)
configure_file(res/textures/test3x3.bmp test3x3.bmp COPYONLY)

# Ylikuutio
add_library(ylikuutio STATIC
    # audio, in alphabetical order
    code/ylikuutio/audio/audio_master.cpp
    code/ylikuutio/audio/audio_master.hpp

    # callback_system, in alphabetical order
    code/ylikuutio/callback_system/callback_engine.cpp
    code/ylikuutio/callback_system/callback_engine.hpp
    code/ylikuutio/callback_system/callback_magic_numbers.hpp
    code/ylikuutio/callback_system/callback_object.cpp
    code/ylikuutio/callback_system/callback_object.hpp
    code/ylikuutio/callback_system/callback_parameter.cpp
    code/ylikuutio/callback_system/callback_parameter.hpp
    code/ylikuutio/callback_system/key_and_callback_struct.hpp

    # command_line, in alphabetical order
    code/ylikuutio/command_line/command_line_master.cpp
    code/ylikuutio/command_line/command_line_master.hpp

    # common, in alphabetical order
    code/ylikuutio/common/any_value.cpp
    code/ylikuutio/common/any_value.hpp
    code/ylikuutio/common/globals.hpp
    code/ylikuutio/common/pi.hpp
    code/ylikuutio/common/printing_struct.hpp
    code/ylikuutio/common/spherical_coordinates_struct.hpp

    # config, in alphabetical order.
    code/ylikuutio/config/activate_callback.hpp
    code/ylikuutio/config/read_callback.hpp
    code/ylikuutio/config/setting.cpp
    code/ylikuutio/config/setting.hpp
    code/ylikuutio/config/setting_master.cpp
    code/ylikuutio/config/setting_master.hpp
    code/ylikuutio/config/setting_struct.hpp

    # console, in alphabetical order.
    code/ylikuutio/console/console.cpp
    code/ylikuutio/console/console.hpp
    code/ylikuutio/console/console_callbacks.cpp
    code/ylikuutio/console/console_command_callback.hpp
    code/ylikuutio/console/console_callback_object.cpp
    code/ylikuutio/console/console_callback_object.hpp

    # file, in alphabetical order.
    code/ylikuutio/file/file_loader.cpp
    code/ylikuutio/file/file_loader.hpp
    code/ylikuutio/file/file_writer.cpp
    code/ylikuutio/file/file_writer.hpp

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
    code/ylikuutio/geometry/spherical_terrain_struct.hpp
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

    # input, in alphabetical order
    code/ylikuutio/input/input.cpp
    code/ylikuutio/input/input.hpp

    # interpolation, in alphabetical order
    code/ylikuutio/interpolation/bilinear_interpolation2D.hpp

    # linear algebra, in alphabetical order.
    code/ylikuutio/linear_algebra/matrix.cpp
    code/ylikuutio/linear_algebra/matrix.hpp
    code/ylikuutio/linear_algebra/matrix_functions.cpp
    code/ylikuutio/linear_algebra/matrix_functions.hpp
    code/ylikuutio/linear_algebra/tensor3.cpp
    code/ylikuutio/linear_algebra/tensor3.hpp

    # load, in alphabetical order.
    code/ylikuutio/load/ascii_grid_loader.cpp
    code/ylikuutio/load/ascii_grid_loader.hpp
    code/ylikuutio/load/bmp_heightmap_loader.cpp
    code/ylikuutio/load/bmp_heightmap_loader.hpp
    code/ylikuutio/load/bmp_loader.cpp
    code/ylikuutio/load/bmp_loader.hpp
    code/ylikuutio/load/fbx_species_loader.cpp
    code/ylikuutio/load/fbx_species_loader.hpp
    code/ylikuutio/load/fbx_symbiosis_loader.cpp
    code/ylikuutio/load/fbx_symbiosis_loader.hpp
    code/ylikuutio/load/font_loader.cpp
    code/ylikuutio/load/font_loader.hpp
    code/ylikuutio/load/heightmap_loader_struct.hpp
    code/ylikuutio/load/obj_loader.cpp
    code/ylikuutio/load/obj_loader.hpp
    code/ylikuutio/load/shader_loader.cpp
    code/ylikuutio/load/shader_loader.hpp
    code/ylikuutio/load/species_loader.cpp
    code/ylikuutio/load/species_loader.hpp
    code/ylikuutio/load/species_loader_struct.hpp
    code/ylikuutio/load/srtm_heightmap_loader.cpp
    code/ylikuutio/load/srtm_heightmap_loader.hpp
    code/ylikuutio/load/symbiosis_loader.cpp
    code/ylikuutio/load/symbiosis_loader.hpp
    code/ylikuutio/load/symbiosis_loader_struct.hpp
    code/ylikuutio/load/texture_loader.cpp
    code/ylikuutio/load/texture_loader.hpp

    # map, in alphabetical order
    code/ylikuutio/map/ylikuutio_map.hpp

    # memory, in alphabetical order
    code/ylikuutio/memory/memory_templates.hpp

    # network, in alphabetical order
    # code/ylikuutio/network/tcp_connection.cpp
    # code/ylikuutio/network/tcp_connection.hpp
    # code/ylikuutio/network/tcp_server.cpp
    # code/ylikuutio/network/tcp_server.hpp

    # ontology, in alphabetical order
    code/ylikuutio/ontology/biont.cpp
    code/ylikuutio/ontology/biont.hpp
    code/ylikuutio/ontology/biont_struct.hpp
    code/ylikuutio/ontology/camera.cpp
    code/ylikuutio/ontology/camera.hpp
    code/ylikuutio/ontology/camera_struct.hpp
    code/ylikuutio/ontology/chunk.cpp
    code/ylikuutio/ontology/chunk.hpp
    code/ylikuutio/ontology/chunk_master.cpp
    code/ylikuutio/ontology/chunk_master.hpp
    code/ylikuutio/ontology/chunk_struct.hpp
    code/ylikuutio/ontology/creature.cpp
    code/ylikuutio/ontology/creature.hpp
    code/ylikuutio/ontology/gl_attrib_locations.cpp
    code/ylikuutio/ontology/gl_attrib_locations.hpp
    code/ylikuutio/ontology/glyph_object_creation.cpp
    code/ylikuutio/ontology/glyph_object_creation.hpp
    code/ylikuutio/ontology/entity.cpp
    code/ylikuutio/ontology/entity.hpp
    code/ylikuutio/ontology/entity_factory.cpp
    code/ylikuutio/ontology/entity_factory.hpp
    code/ylikuutio/ontology/family_templates.hpp
    code/ylikuutio/ontology/font2D.cpp
    code/ylikuutio/ontology/font2D.hpp
    code/ylikuutio/ontology/glyph.cpp
    code/ylikuutio/ontology/glyph.hpp
    code/ylikuutio/ontology/glyph_struct.hpp
    code/ylikuutio/ontology/ground_level.cpp
    code/ylikuutio/ontology/ground_level.hpp
    code/ylikuutio/ontology/holobiont.cpp
    code/ylikuutio/ontology/holobiont.hpp
    code/ylikuutio/ontology/holobiont_struct.hpp
    code/ylikuutio/ontology/material.cpp
    code/ylikuutio/ontology/material.hpp
    code/ylikuutio/ontology/material_struct.hpp
    code/ylikuutio/ontology/model.cpp
    code/ylikuutio/ontology/model.hpp
    code/ylikuutio/ontology/movable.cpp
    code/ylikuutio/ontology/movable.hpp
    code/ylikuutio/ontology/object.cpp
    code/ylikuutio/ontology/object.hpp
    code/ylikuutio/ontology/object_struct.hpp
    code/ylikuutio/ontology/render_templates.hpp
    code/ylikuutio/ontology/rail_vehicle.cpp
    code/ylikuutio/ontology/rail_vehicle.hpp
    code/ylikuutio/ontology/road_vehicle.cpp
    code/ylikuutio/ontology/road_vehicle.hpp
    code/ylikuutio/ontology/scene.cpp
    code/ylikuutio/ontology/scene.hpp
    code/ylikuutio/ontology/shader.cpp
    code/ylikuutio/ontology/shader.hpp
    code/ylikuutio/ontology/shader_struct.hpp
    code/ylikuutio/ontology/species.cpp
    code/ylikuutio/ontology/species.hpp
    code/ylikuutio/ontology/species_or_glyph.hpp
    code/ylikuutio/ontology/species_struct.hpp
    code/ylikuutio/ontology/symbiont_material.cpp
    code/ylikuutio/ontology/symbiont_material.hpp
    code/ylikuutio/ontology/symbiont_species.cpp
    code/ylikuutio/ontology/symbiont_species.hpp
    code/ylikuutio/ontology/symbiosis.cpp
    code/ylikuutio/ontology/symbiosis.hpp
    code/ylikuutio/ontology/symbiosis_struct.hpp
    code/ylikuutio/ontology/terrain_generation_callbacks.cpp
    code/ylikuutio/ontology/terrain_generation_callbacks.hpp
    code/ylikuutio/ontology/text3D.hpp
    code/ylikuutio/ontology/text3D.cpp
    code/ylikuutio/ontology/text3D_struct.hpp
    code/ylikuutio/ontology/universe.cpp
    code/ylikuutio/ontology/universe.hpp
    code/ylikuutio/ontology/universe_struct.hpp
    code/ylikuutio/ontology/vector_font.cpp
    code/ylikuutio/ontology/vector_font.hpp
    code/ylikuutio/ontology/vector_font_struct.hpp
    code/ylikuutio/ontology/vehicle.cpp
    code/ylikuutio/ontology/vehicle.hpp
    code/ylikuutio/ontology/vertex_graph.cpp
    code/ylikuutio/ontology/vertex_graph.hpp
    code/ylikuutio/ontology/vertex_node.cpp
    code/ylikuutio/ontology/vertex_node.hpp
    code/ylikuutio/ontology/world.cpp
    code/ylikuutio/ontology/world.hpp

    # opengl, in alphabetical order
    code/ylikuutio/opengl/opengl.cpp
    code/ylikuutio/opengl/opengl.hpp
    code/ylikuutio/opengl/vboindexer.cpp
    code/ylikuutio/opengl/vboindexer.hpp

    # shaders, in alphabetical order
    code/ylikuutio/shaders/StandardShading.fragmentshader
    code/ylikuutio/shaders/StandardShading.vertexshader
    code/ylikuutio/shaders/TextVertexShader.fragmentshader
    code/ylikuutio/shaders/TextVertexShader.vertexshader

    # string, in alphabetical order
    code/ylikuutio/string/ylikuutio_string.cpp
    code/ylikuutio/string/ylikuutio_string.hpp

    # time, in alphabetical order
    code/ylikuutio/time/time.cpp
    code/ylikuutio/time/time.hpp

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

# yli_convert
add_executable(yli_convert
    # yli_convert, in alphabetical order
    code/tools/yli_convert.cpp
    )
target_link_libraries(yli_convert ylikuutio ${ALL_LIBS} assimp)
set_target_properties(yli_convert PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")

# Ajokki
add_executable(ajokki
    # ajokki, in alphabetical order
    code/ajokki/ajokki.cpp
    code/ajokki/ajokki_altiplano_scene.cpp
    code/ajokki/ajokki_altiplano_scene.hpp
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
    code/ajokki/ajokki_helsinki_east_downtown_scene.cpp
    code/ajokki/ajokki_helsinki_east_downtown_scene.hpp
    code/ajokki/ajokki_joensuu_center_west_scene.cpp
    code/ajokki/ajokki_joensuu_center_west_scene.hpp
    code/ajokki/ajokki_keyboard_callbacks.cpp
    code/ajokki/ajokki_keyboard_callbacks.hpp
    code/ajokki/ajokki_location_and_orientation.cpp
    code/ajokki/ajokki_location_and_orientation.hpp
    code/ajokki/ajokki_movement.cpp
    code/ajokki/ajokki_movement.hpp
    code/ajokki/ajokki_tallinn_scene.cpp
    code/ajokki/ajokki_tallinn_scene.hpp
    code/ajokki/ajokki_wireframe.cpp
    code/ajokki/ajokki_wireframe.hpp
    )
target_link_libraries(ajokki ylikuutio ${ALL_LIBS})

if (ENABLE_SCRIPTING_WITH_S7_SCHEME)
    # S7 Scheme test
    add_executable(s7_test code/s7/s7_test.cpp
        )
    target_link_libraries(s7_test s7 pthread)
endif()

# Asio-test
if(FALSE)
    add_executable(asio_chat_server
        code/asio/asio_chat_server.cpp
        )
    target_link_libraries(asio_chat_server pthread)

    add_executable(asio_chat_client
        code/asio/asio_chat_client.cpp
        )
    target_link_libraries(asio_chat_client pthread)

    add_executable(asio_nslookup
        code/asio/asio_nslookup.cpp
        )
    target_link_libraries(asio_nslookup pthread)
endif()

# Xcode and Visual working directories
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
        code/ylikuutio/command_line/command_line_master.cpp
        code/ylikuutio/command_line/command_line_master.hpp
        code/ylikuutio/common/any_value.cpp
        code/ylikuutio/common/any_value.hpp
        code/ylikuutio/common/globals.hpp
        code/ylikuutio/file/file_loader.cpp
        code/ylikuutio/file/file_loader.hpp
        code/ylikuutio/file/file_writer.cpp
        code/ylikuutio/file/file_writer.hpp
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
        code/ylikuutio/load/ascii_grid_loader.cpp
        code/ylikuutio/load/ascii_grid_loader.hpp
        code/ylikuutio/load/fbx_species_loader.cpp
        code/ylikuutio/load/fbx_species_loader.hpp
        code/ylikuutio/load/font_loader.cpp
        code/ylikuutio/load/font_loader.hpp
        code/ylikuutio/memory/memory_templates.hpp
        code/ylikuutio/ontology/glyph_struct.hpp
        code/ylikuutio/ontology/material_struct.hpp
        code/ylikuutio/ontology/object_struct.hpp
        code/ylikuutio/ontology/shader_struct.hpp
        code/ylikuutio/ontology/species_struct.hpp
        code/ylikuutio/ontology/text3D_struct.hpp
        code/ylikuutio/ontology/vector_font_struct.hpp
        code/ylikuutio/ontology/universe.cpp
        code/ylikuutio/ontology/universe.hpp
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
        code/ylikuutio/tests/googletest/test_ascii_grid_loader.cpp
        # code/ylikuutio/tests/googletest/test_asio.cpp
        code/ylikuutio/tests/googletest/test_bilinear_interpolation2D.cpp
        code/ylikuutio/tests/googletest/test_callback_system.cpp
        code/ylikuutio/tests/googletest/test_check_and_report_if_some_string_matches.cpp
        code/ylikuutio/tests/googletest/test_command_line_master.cpp
        code/ylikuutio/tests/googletest/test_extract_last_part_of_string.cpp
        code/ylikuutio/tests/googletest/test_extract_string.cpp
        code/ylikuutio/tests/googletest/test_extract_string_with_several_endings.cpp
        code/ylikuutio/tests/googletest/test_extract_unicode_value_from_string.cpp
        code/ylikuutio/tests/googletest/test_fbx_loader.cpp
        code/ylikuutio/tests/googletest/test_file_loader.cpp
        code/ylikuutio/tests/googletest/test_font_loader.cpp
        code/ylikuutio/tests/googletest/test_glyph_struct.cpp
        code/ylikuutio/tests/googletest/test_heightmap_loader.cpp
        code/ylikuutio/tests/googletest/test_line2D.cpp
        code/ylikuutio/tests/googletest/test_line_line_intersection.cpp
        code/ylikuutio/tests/googletest/test_line_segment_line_segment_intersection.cpp
        code/ylikuutio/tests/googletest/test_linear_algebra.cpp
        code/ylikuutio/tests/googletest/test_material_struct.cpp
        code/ylikuutio/tests/googletest/test_node_struct.cpp
        code/ylikuutio/tests/googletest/test_obj_loader.cpp
        code/ylikuutio/tests/googletest/test_object_struct.cpp
        code/ylikuutio/tests/googletest/test_pugixml.cpp
        code/ylikuutio/tests/googletest/test_shader_struct.cpp
        code/ylikuutio/tests/googletest/test_species_struct.cpp
        code/ylikuutio/tests/googletest/test_vector_font_struct.cpp)
    set(MAIN_FILE code/ylikuutio/tests/googletest/main.cpp)

    add_library(code_to_test ${FILES_TO_TEST})
    add_dependencies(code_to_test OpenFBX)

    add_executable(do_tests_googletest ${MAIN_FILE})
    add_dependencies(do_tests_googletest OpenFBX)
    target_link_libraries(do_tests_googletest code_to_test)

    add_executable(unit_tests_with_googletest code/ylikuutio/tests/googletest/test_main.cpp ${UNIT_TESTS})
    target_link_libraries(unit_tests_with_googletest gtest libgtest rt pthread code_to_test)

    # Xcode and Visual working directories
    set_target_properties(unit_tests_with_googletest PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code/tests/googletest/")
    create_target_launcher(unit_tests_with_googletest WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/code/tests/googletest/")
endif()

source_group(common REGULAR_EXPRESSION ".*/code/common/.*" )
source_group(shaders REGULAR_EXPRESSION ".*/.*shader$" )
