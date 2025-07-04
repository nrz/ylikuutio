# CMake entry point
cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0004 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0072 NEW)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(ylikuutio VERSION 0.0.10)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    project(ylikuutio LANGUAGES C CXX)
else()
    project(ylikuutio LANGUAGES C CXX Fortran)
    include(FortranCInterface)
    FortranCInterface_VERIFY(CXX)
endif()

#-------------------------------------------------------+
# the options part intended to be modified begins here. |
#-------------------------------------------------------+

# http://stackoverflow.com/questions/11783932/how-to-add-linker-or-compile-flag-in-cmake-file/11797272#11797272
# SET(GCC_COVERAGE_LINK_FLAGS "-ldl")
# SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Modify the below line to control whether to compile SDL from source on Linux.
set(COMPILE_SDL_FROM_SOURCE false)

# Modify the below line to control whether to compile libpng from source on Linux.
set(COMPILE_LIBPNG_FROM_SOURCE false)

# Modify the below line to control whether to compile zlib from source on Linux.
set(COMPILE_ZLIB_FROM_SOURCE false)

#-------------------------------------------------------+
# the options part intended to be modified ends here.   |
#-------------------------------------------------------+

find_package(OpenGL REQUIRED)

# Build config should be in the following order: Linux, Darwin, Windows.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Use Vulkan on Linux.
    find_package(Vulkan REQUIRED)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # TODO: implement MoltenVK support for MacOS.
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # TODO: implement Vulkan support for Windows.
endif()

find_package(Threads REQUIRED)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Compile unit tests when compiling natively on Linux.
    set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)
elseif(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Crosscompiling from Linux to Windows must compile SDL and libpng from source.
    # Dynamic linking of SDL when crosscompiling from Linux to Windows is not supported.
    set(COMPILE_SDL_FROM_SOURCE true)

    # Crosscompiling from Linux to Windows must compile libpng from source.
    set(COMPILE_LIBPNG_FROM_SOURCE true)

    # Crosscompiling from Linux to Windows must compile zlib from source.
    set(COMPILE_ZLIB_FROM_SOURCE true)

    # Do not compile unit tests when crosscompiling from Linux to Windows.
    set(DO_UNIT_TESTS_WITH_GOOGLE_TEST false)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Native compiling on MacOS must compile SDL from source.
    set(COMPILE_SDL_FROM_SOURCE true)

    # Native compiling on MacOS must compile libpng from source.
    set(COMPILE_LIBPNG_FROM_SOURCE true)

    # Native compiling on MacOS must compile zlib from source.
    set(COMPILE_ZLIB_FROM_SOURCE true)

    # Do not compile unit tests when building on MacOS.
    set(DO_UNIT_TESTS_WITH_GOOGLE_TEST false)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Native compiling on Windows must compile SDL from source.
    set(COMPILE_SDL_FROM_SOURCE true)

    # Native compiling on Windows must compile libpng from source.
    set(COMPILE_LIBPNG_FROM_SOURCE true)

    # Native compiling on Windows must compile zlib from source.
    set(COMPILE_ZLIB_FROM_SOURCE true)

    # Do not compile unit tests when building on Windows.
    set(DO_UNIT_TESTS_WITH_GOOGLE_TEST false)
endif()

# When doing a regular build on Linux, SDL can be linked either statically or dynamically.
if(NOT(COMPILE_SDL_FROM_SOURCE))
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
    find_package(SDL2 REQUIRED)
endif()

# Compile external dependencies
add_subdirectory (external)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Command line arguments not supported by Visual Studio.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wextra -Wuninitialized -Werror=return-type")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wextra -Wuninitialized -Werror=return-type -Werror=nonnull")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -O3 -Wextra -Wuninitialized -Werror=return-type")
endif()

# set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "ERROR: in-source builds are not supported! Please create a build directory and build from there!")
endif()
if(CMAKE_SOURCE_DIR MATCHES " ")
    message("WARNING: Your source directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()
if(CMAKE_BINARY_DIR MATCHES " ")
    message("WARNING: Your build directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(COMPILE_SDL_FROM_SOURCE)
    include_directories(
        external/SDL/include/
        )
else()
    include_directories(
        ${SDL2_INCLUDE_DIRS}
        )
endif()

if(COMPILE_LIBPNG_FROM_SOURCE)
    include_directories(
        external/libpng-1.6.44/
        )
else()
    # Use libsdl shipped with the GNU/Linux distribution.
    find_package(PNG REQUIRED)

    if (DEFINED "PNG_INCLUDE_DIRS")
        include_directories(
            ${PNG_INCLUDE_DIRS}
            )
    else()
        include_directories(
            ${PNG_INCLUDE_DIR}
            )
    endif()
endif()

if(COMPILE_ZLIB_FROM_SOURCE)
    include_directories(
        external/zlib/
        )
else()
    # Use zlib shipped with the GNU/Linux distribution.
    find_package(ZLIB REQUIRED)

    if (DEFINED "ZLIB_INCLUDE_DIRS")
        include_directories(
            ${ZLIB_INCLUDE_DIRS}
            )
    else()
        include_directories(
            ${ZLIB_INCLUDE_DIR}
            )
    endif()
endif()

include_directories(
    # external/asio/asio/include/
    external/FastNoiseSIMD/
    external/glew-2.0.0/include/
    external/glm/
    external/OpenFBX/src/
    external/pugixml/src/
    external/soloud/include/
    .
    )

if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    # for Google Test.
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        )

    FetchContent_MakeAvailable(googletest)

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND NOT CMAKE_CROSSCOMPILING)
    set(THREAD_LIBS
    )
else()
    set(THREAD_LIBS
        pthread
    )
endif()

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    GLEW_200
    pugixml
    miniz
    OpenFBX
    soloud
    )

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

if (COMPILE_ZLIB_FROM_SOURCE)
    set(ALL_LIBS
        ${ALL_LIBS}
        zlib
        )
else()
    if (DEFINED "ZLIB_LIBRARIES")
        set(ALL_LIBS
            ${ALL_LIBS}
            ${ZLIB_LIBRARIES}
            )
    else()
        set(ALL_LIBS
            ${ALL_LIBS}
            ${ZLIB_LIBRARY}
            )
    endif()
endif()

if (COMPILE_LIBPNG_FROM_SOURCE)
    set(ALL_LIBS
        ${ALL_LIBS}
        png_static
        )
else()
    if (DEFINED "PNG_LIBRARIES")
        set(ALL_LIBS
            ${ALL_LIBS}
            ${PNG_LIBRARIES}
            )
    else()
        set(ALL_LIBS
            ${ALL_LIBS}
            ${PNG_LIBRARY}
            )
    endif()
endif()

add_definitions(
    -DGLEW_STATIC
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -D_CRT_SECURE_NO_WARNINGS
    -DPNG_NO_SETJMP
    )

# zlib.
if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND NOT CMAKE_CROSSCOMPILING)
    configure_file("${CMAKE_SOURCE_DIR}/external/zlib/zconf.h.included" "${CMAKE_SOURCE_DIR}/external/zlib/zconf.h" COPYONLY)
endif()

# Shaders.
configure_file(code/ylikuutio/shaders/floyd_warshall.frag floyd_warshall.frag COPYONLY)
configure_file(code/ylikuutio/shaders/go_west.frag go_west.frag COPYONLY)
configure_file(code/ylikuutio/shaders/vanish_west.frag vanish_west.frag COPYONLY)
configure_file(code/ylikuutio/shaders/identity.vert identity.vert COPYONLY)
configure_file(code/ylikuutio/shaders/identity.frag identity.frag COPYONLY)
configure_file(code/ylikuutio/shaders/standard_shading.vert standard_shading.vert COPYONLY)
configure_file(code/ylikuutio/shaders/standard_shading.frag standard_shading.frag COPYONLY)
configure_file(code/ylikuutio/shaders/grayscale_standard_shading.frag grayscale_standard_shading.frag COPYONLY)
configure_file(code/ylikuutio/shaders/sobel_x.frag sobel_x.frag COPYONLY)
configure_file(code/ylikuutio/shaders/sobel_y.frag sobel_y.frag COPYONLY)
configure_file(code/ylikuutio/shaders/sobel_gradient_magnitude.frag sobel_gradient_magnitude.frag COPYONLY)
configure_file(code/ylikuutio/shaders/text_vertex_shader.vert text_vertex_shader.vert COPYONLY)
configure_file(code/ylikuutio/shaders/text_vertex_shader.frag text_vertex_shader.frag COPYONLY)

# 3D models.
# Suzanne.
configure_file(res/objects/custom/suzanne.obj suzanne.obj COPYONLY)
configure_file(res/objects/custom/suzanne_old.obj suzanne_old.obj COPYONLY)
# Freight train.
configure_file(res/objects/www.blendswap.com/46359_freight_train/freight_train.fbx freight_train.fbx COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_chassis.png freight_train_chassis.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_box_expage.png freight_train_box_expage.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_body.png freight_train_body.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_expage1.png freight_train_expage1.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_expage2.png freight_train_expage2.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_gray_concrete.png freight_train_gray_concrete.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_iron_texture_by_pabloalvin.png freight_train_iron_texture_by_pabloalvin.png COPYONLY)
configure_file(res/objects/www.blendswap.com/46359_freight_train/textures/freight_train_stone.png freight_train_stone.png COPYONLY)
# Turbo polizei.
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/turbo_polizei_png_textures.fbx turbo_polizei_png_textures.fbx COPYONLY)
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/textures/car.png car.png COPYONLY)
configure_file(res/objects/www.blendswap.com/74227_Porsche_997_turbo_polizei_lowpoly/textures/wheell.png wheell.png COPYONLY)
# Horse.
configure_file(res/objects/www.blendswap.com/76528_horse/horse.fbx horse.fbx COPYONLY)
# Cat.
configure_file(res/objects/www.blendswap.com/86110_rigged_and_animated_cat/cat.fbx cat.fbx COPYONLY)

# Textures.
configure_file(res/textures/GrassGreenTexture0002.png GrassGreenTexture0002.png COPYONLY)
configure_file(res/textures/orange_fur_texture.png orange_fur_texture.png COPYONLY)
configure_file(res/textures/pavers1b2.png pavers1b2.png COPYONLY)
configure_file(res/textures/numbers_123456_black_and_white.png numbers_123456_black_and_white.png COPYONLY)

# Fonts.
configure_file(res/fonts/kongtext/kongtext.svg kongtext.svg COPYONLY)
configure_file(res/fonts/Holstein.DDS Holstein.DDS COPYONLY)
configure_file(res/fonts/Holstein.png Holstein.png COPYONLY)

# Maps.
configure_file(res/height_maps/noise1024x1024.png noise1024x1024.png COPYONLY)
configure_file(res/height_maps/noise256x256.png noise256x256.png COPYONLY)
configure_file(res/height_maps/noise128x128.png noise128x128.png COPYONLY)
configure_file(res/height_maps/N59E024.hgt N59E024.hgt COPYONLY)
configure_file(res/height_maps/S17W069.hgt S17W069.hgt COPYONLY)
configure_file(res/height_maps/L4133D.asc L4133D.asc COPYONLY)
configure_file(res/height_maps/N5424G.asc N5424G.asc COPYONLY)
configure_file(res/height_maps/test_3x3_0_1_2_4_8_16_32_64_128.asc test_3x3_0_1_2_4_8_16_32_64_128.asc COPYONLY)
configure_file(res/laser_scanning_data/L4133D1.laz L4133D1.laz COPYONLY)
configure_file(res/maps/Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm COPYONLY)
configure_file(res/maps/Exactum_Physicum_Helsinki_Finland.osm Exactum_Physicum_Helsinki_Finland.osm COPYONLY)

# Graphs.
configure_file(res/graphs/more_finnish_railway_stations_float.csv more_finnish_railway_stations_float.csv COPYONLY)
configure_file(res/graphs/more_finnish_railway_stations_unsigned_integer.csv more_finnish_railway_stations_unsigned_integer.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_float.csv some_finnish_railway_stations_float.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_integer.csv some_finnish_railway_stations_integer.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_unsigned_integer.csv some_finnish_railway_stations_unsigned_integer.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_unsigned_integer_mini.csv some_finnish_railway_stations_unsigned_integer_mini.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_float_with_fill.csv some_finnish_railway_stations_float_with_fill.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_float_megameters_with_fill.csv some_finnish_railway_stations_float_megameters_with_fill.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_unsigned_integer_with_fill.csv some_finnish_railway_stations_unsigned_integer_with_fill.csv COPYONLY)
configure_file(res/graphs/some_finnish_railway_stations_unsigned_integer_mini_with_fill.csv some_finnish_railway_stations_unsigned_integer_mini_with_fill.csv COPYONLY)

# Audio.
configure_file(res/audio/freesound.org/395487__frankum__tecno-pop-base-and-guitar-2.ogg 395487__frankum__tecno-pop-base-and-guitar-2.ogg COPYONLY)
configure_file(res/audio/freesound.org/414257__sss-samples__chipland-loop-120-bpm-a-major.wav 414257__sss-samples__chipland-loop-120-bpm-a-major.wav COPYONLY)
configure_file(res/audio/freesound.org/414269__jpmusic82__arp-bass-loop-128-bpm.mp3 414269__jpmusic82__arp-bass-loop-128-bpm.mp3 COPYONLY)
configure_file(res/audio/freesound.org/414270__greek555__sample-97-bpm.wav 414270__greek555__sample-97-bpm.wav COPYONLY)
configure_file(res/audio/freesound.org/416882__greek555__blue-play.ogg 416882__greek555__blue-play.ogg COPYONLY)
configure_file(res/audio/freesound.org/419588__greek555__dreaming-of-me.ogg 419588__greek555__dreaming-of-me.ogg COPYONLY)

# Image files for tests.
configure_file(res/height_maps/noise256x256.png noise256x256.png COPYONLY)
configure_file(res/textures/test3x3.png test3x3.png COPYONLY)

# Copy data files for Avaruus.
configure_file(run/input.dat                   input.dat COPYONLY)
configure_file(run/empty_file_for_testing.dat  empty_file_for_testing.dat COPYONLY)
configure_file(run/one_line_for_testing.dat    one_line_for_testing.dat COPYONLY)
configure_file(run/three_lines_for_testing.dat three_lines_for_testing.dat COPYONLY)

# Copy scripts for Avaruus.
configure_file(code/avaruus/bash/process_output_file_2_objects     process_output_file_2_objects COPYONLY)
configure_file(code/avaruus/bash/process_output_file_solar_system  process_output_file_solar_system COPYONLY)
configure_file(code/avaruus/python/visualize_2_objects             visualize_2_objects COPYONLY)
configure_file(code/avaruus/python/visualize_solar_system          visualize_solar_system COPYONLY)

# Ylikuutio
add_library(ylikuutio STATIC
    # audio, in alphabetical order
    code/ylikuutio/audio/audio_system.cpp
    code/ylikuutio/audio/audio_system.hpp

    # command_line, in alphabetical order
    code/ylikuutio/command_line/command_line_master.cpp
    code/ylikuutio/command_line/command_line_master.hpp

    # console, in alphabetical order
    code/ylikuutio/console/console_state.hpp
    code/ylikuutio/console/console_state_module.cpp
    code/ylikuutio/console/console_state_module.hpp
    code/ylikuutio/console/current_input.cpp
    code/ylikuutio/console/current_input.hpp
    code/ylikuutio/console/scrollback_buffer.cpp
    code/ylikuutio/console/scrollback_buffer.hpp
    code/ylikuutio/console/scrollback_buffer_const_iterator.hpp
    code/ylikuutio/console/scrollback_buffer_iterator.hpp
    code/ylikuutio/console/temp_input.cpp
    code/ylikuutio/console/temp_input.hpp
    code/ylikuutio/console/text_input.cpp
    code/ylikuutio/console/text_input.hpp
    code/ylikuutio/console/text_input_const_iterator.hpp
    code/ylikuutio/console/text_input_iterator.hpp
    code/ylikuutio/console/text_input_history.cpp
    code/ylikuutio/console/text_input_history.hpp
    code/ylikuutio/console/text_input_history_iterator.hpp
    code/ylikuutio/console/text_line.cpp
    code/ylikuutio/console/text_line.hpp
    code/ylikuutio/console/text_line_const_iterator.hpp

    # core, in alphabetical order
    code/ylikuutio/core/application.cpp
    code/ylikuutio/core/application.hpp
    code/ylikuutio/core/entrypoint.hpp
    code/ylikuutio/core/system_factory.hpp

    # data, in alphabetical order
    code/ylikuutio/data/any_value.cpp
    code/ylikuutio/data/any_value.hpp
    code/ylikuutio/data/data_templates.hpp
    code/ylikuutio/data/datatype.hpp
    code/ylikuutio/data/queue.hpp
    code/ylikuutio/data/queue_iterator.hpp
    code/ylikuutio/data/tuple_templates.hpp
    code/ylikuutio/data/type_enum_provider.hpp
    code/ylikuutio/data/variant_templates.hpp
    code/ylikuutio/data/wrap.hpp

    # event, in alphabetical order
    code/ylikuutio/event/event_system.cpp
    code/ylikuutio/event/event_system.hpp

    # file, in alphabetical order.
    code/ylikuutio/file/file_loader.cpp
    code/ylikuutio/file/file_loader.hpp
    code/ylikuutio/file/file_writer.hpp

    # geometry, in alphabetical order.
    code/ylikuutio/geometry/degrees_to_radians.cpp
    code/ylikuutio/geometry/degrees_to_radians.hpp
    code/ylikuutio/geometry/line.cpp
    code/ylikuutio/geometry/line.hpp
    code/ylikuutio/geometry/line_2d.cpp
    code/ylikuutio/geometry/line_2d.hpp
    code/ylikuutio/geometry/line_3d.cpp
    code/ylikuutio/geometry/line_3d.hpp
    code/ylikuutio/geometry/line_line_intersection.cpp
    code/ylikuutio/geometry/line_line_intersection.hpp
    code/ylikuutio/geometry/line_segment.cpp
    code/ylikuutio/geometry/line_segment.hpp
    code/ylikuutio/geometry/line_segment_2d.cpp
    code/ylikuutio/geometry/line_segment_2d.hpp
    code/ylikuutio/geometry/line_segment_3d.cpp
    code/ylikuutio/geometry/line_segment_3d.hpp
    code/ylikuutio/geometry/line_segment_line_segment_intersection.cpp
    code/ylikuutio/geometry/line_segment_line_segment_intersection.hpp
    code/ylikuutio/geometry/radians_to_degrees.cpp
    code/ylikuutio/geometry/radians_to_degrees.hpp

    # graph, in alphabetical order.
    code/ylikuutio/graph/shortest_paths.cpp
    code/ylikuutio/graph/shortest_paths.hpp

    # hierarchy, in alphabetical order.
    code/ylikuutio/hierarchy/hierarchy_templates.hpp

    # input, in alphabetical order
    code/ylikuutio/input/input.cpp
    code/ylikuutio/input/input.hpp
    code/ylikuutio/input/input_system.cpp
    code/ylikuutio/input/input_system.hpp

    # interpolation, in alphabetical order
    code/ylikuutio/interpolation/bilinear_interpolation.hpp
    code/ylikuutio/interpolation/bilinear_interpolation_struct.hpp

    # linear algebra, in alphabetical order.
    code/ylikuutio/linear_algebra/matrix.cpp
    code/ylikuutio/linear_algebra/matrix.hpp
    code/ylikuutio/linear_algebra/matrix_functions.cpp
    code/ylikuutio/linear_algebra/matrix_functions.hpp
    code/ylikuutio/linear_algebra/tensor3.cpp
    code/ylikuutio/linear_algebra/tensor3.hpp
    code/ylikuutio/linear_algebra/vector_functions.hpp

    # lisp, in alphabetical order.
    code/ylikuutio/lisp/executor.cpp
    code/ylikuutio/lisp/executor.hpp
    code/ylikuutio/lisp/function_arg_extractor.hpp
    code/ylikuutio/lisp/lisp_templates.hpp
    code/ylikuutio/lisp/parser.hpp
    code/ylikuutio/lisp/token.cpp
    code/ylikuutio/lisp/token.hpp
    code/ylikuutio/lisp/token_type.hpp

    # load, in alphabetical order.
    code/ylikuutio/load/ascii_grid_heightmap_loader.cpp
    code/ylikuutio/load/ascii_grid_heightmap_loader.hpp
    code/ylikuutio/load/common_texture_loader.cpp
    code/ylikuutio/load/common_texture_loader.hpp
    code/ylikuutio/load/csv_loader.hpp
    code/ylikuutio/load/csv_texture_loader.cpp
    code/ylikuutio/load/csv_texture_loader.hpp
    code/ylikuutio/load/fbx_model_loader.cpp
    code/ylikuutio/load/fbx_model_loader.hpp
    code/ylikuutio/load/fbx_symbiosis_loader.cpp
    code/ylikuutio/load/fbx_symbiosis_loader.hpp
    code/ylikuutio/load/fbx_texture_loader.cpp
    code/ylikuutio/load/fbx_texture_loader.hpp
    code/ylikuutio/load/heightmap_loader_struct.hpp
    code/ylikuutio/load/image_file_loader.cpp
    code/ylikuutio/load/image_file_loader.hpp
    code/ylikuutio/load/image_loader_struct.hpp
    code/ylikuutio/load/model_loader.cpp
    code/ylikuutio/load/model_loader.hpp
    code/ylikuutio/load/model_loader_struct.hpp
    code/ylikuutio/load/obj_loader.cpp
    code/ylikuutio/load/obj_loader.hpp
    code/ylikuutio/load/png_heightmap_loader.cpp
    code/ylikuutio/load/png_heightmap_loader.hpp
    code/ylikuutio/load/png_loader.cpp
    code/ylikuutio/load/png_loader.hpp
    code/ylikuutio/load/shader_loader.cpp
    code/ylikuutio/load/shader_loader.hpp
    code/ylikuutio/load/srtm_heightmap_loader.cpp
    code/ylikuutio/load/srtm_heightmap_loader.hpp
    code/ylikuutio/load/symbiosis_loader.cpp
    code/ylikuutio/load/symbiosis_loader.hpp
    code/ylikuutio/load/symbiosis_loader_struct.hpp

    # map, in alphabetical order
    code/ylikuutio/map/ylikuutio_map.hpp

    # memory, in alphabetical order
    code/ylikuutio/memory/constructible_module.hpp
    code/ylikuutio/memory/generic_memory_allocator.hpp
    code/ylikuutio/memory/generic_memory_system.hpp
    code/ylikuutio/memory/memory_allocator.hpp
    code/ylikuutio/memory/memory_allocator_types.hpp
    code/ylikuutio/memory/memory_storage.hpp
    code/ylikuutio/memory/memory_system.hpp
    code/ylikuutio/memory/memory_templates.hpp

    # network, in alphabetical order
    # code/ylikuutio/network/tcp_connection.cpp
    # code/ylikuutio/network/tcp_connection.hpp
    # code/ylikuutio/network/tcp_server.cpp
    # code/ylikuutio/network/tcp_server.hpp

    # ontology, in alphabetical order
    code/ylikuutio/ontology/activate_callback.hpp
    code/ylikuutio/ontology/apprentice_iterator.hpp
    code/ylikuutio/ontology/apprentice_module.cpp
    code/ylikuutio/ontology/apprentice_module.hpp
    code/ylikuutio/ontology/audio_track.cpp
    code/ylikuutio/ontology/audio_track.hpp
    code/ylikuutio/ontology/audio_track_struct.hpp
    code/ylikuutio/ontology/biont.cpp
    code/ylikuutio/ontology/biont.hpp
    code/ylikuutio/ontology/biont_struct.hpp
    code/ylikuutio/ontology/brain.cpp
    code/ylikuutio/ontology/brain.hpp
    code/ylikuutio/ontology/brain_struct.hpp
    code/ylikuutio/ontology/callback_engine.cpp
    code/ylikuutio/ontology/callback_engine.hpp
    code/ylikuutio/ontology/callback_engine_struct.hpp
    code/ylikuutio/ontology/callback_magic_numbers.hpp
    code/ylikuutio/ontology/callback_object.cpp
    code/ylikuutio/ontology/callback_object.hpp
    code/ylikuutio/ontology/callback_object_struct.hpp
    code/ylikuutio/ontology/callback_parameter.cpp
    code/ylikuutio/ontology/callback_parameter.hpp
    code/ylikuutio/ontology/callback_parameter_struct.hpp
    code/ylikuutio/ontology/camera.cpp
    code/ylikuutio/ontology/camera.hpp
    code/ylikuutio/ontology/camera_struct.hpp
    code/ylikuutio/ontology/cartesian_coordinates_module.cpp
    code/ylikuutio/ontology/cartesian_coordinates_module.hpp
    code/ylikuutio/ontology/child_iterator.hpp
    code/ylikuutio/ontology/child_module.cpp
    code/ylikuutio/ontology/child_module.hpp
    code/ylikuutio/ontology/compute_task.cpp
    code/ylikuutio/ontology/compute_task.hpp
    code/ylikuutio/ontology/compute_task_struct.hpp
    code/ylikuutio/ontology/console.cpp
    code/ylikuutio/ontology/console.hpp
    code/ylikuutio/ontology/console_callback_engine.cpp
    code/ylikuutio/ontology/console_callback_engine.hpp
    code/ylikuutio/ontology/console_callback_engine_struct.hpp
    code/ylikuutio/ontology/console_callback_object.cpp
    code/ylikuutio/ontology/console_callback_object.hpp
    code/ylikuutio/ontology/console_callback_object_struct.hpp
    code/ylikuutio/ontology/console_callback_parameter.cpp
    code/ylikuutio/ontology/console_callback_parameter.hpp
    code/ylikuutio/ontology/console_callback_parameter_struct.hpp
    code/ylikuutio/ontology/console_callbacks.cpp
    code/ylikuutio/ontology/console_printing.cpp
    code/ylikuutio/ontology/console_printing.hpp
    code/ylikuutio/ontology/console_struct.hpp
    code/ylikuutio/ontology/ecosystem.cpp
    code/ylikuutio/ontology/ecosystem.hpp
    code/ylikuutio/ontology/ecosystem_struct.hpp
    code/ylikuutio/ontology/entity.cpp
    code/ylikuutio/ontology/entity.hpp
    code/ylikuutio/ontology/entity_callbacks.cpp
    code/ylikuutio/ontology/entity_factory.hpp
    code/ylikuutio/ontology/entity_struct.hpp
    code/ylikuutio/ontology/entity_variable_activation.cpp
    code/ylikuutio/ontology/entity_variable_activation.hpp
    code/ylikuutio/ontology/entity_variable_read.cpp
    code/ylikuutio/ontology/entity_variable_read.hpp
    code/ylikuutio/ontology/family_templates.hpp
    code/ylikuutio/ontology/font_2d.cpp
    code/ylikuutio/ontology/font_2d.hpp
    code/ylikuutio/ontology/font_struct.hpp
    code/ylikuutio/ontology/framebuffer_module.cpp
    code/ylikuutio/ontology/framebuffer_module.hpp
    code/ylikuutio/ontology/framebuffer_module_struct.hpp
    code/ylikuutio/ontology/generic_callback_engine.cpp
    code/ylikuutio/ontology/generic_callback_engine.hpp
    code/ylikuutio/ontology/generic_callback_engine_struct.hpp
    code/ylikuutio/ontology/generic_entity_factory.hpp
    code/ylikuutio/ontology/generic_lisp_function_overload.cpp
    code/ylikuutio/ontology/generic_lisp_function_overload.hpp
    code/ylikuutio/ontology/generic_master_module.cpp
    code/ylikuutio/ontology/generic_master_module.hpp
    code/ylikuutio/ontology/generic_parent_module.cpp
    code/ylikuutio/ontology/generic_parent_module.hpp
    code/ylikuutio/ontology/get_content_callback.hpp
    code/ylikuutio/ontology/gl_attrib_locations.cpp
    code/ylikuutio/ontology/gl_attrib_locations.hpp
    code/ylikuutio/ontology/glyph.cpp
    code/ylikuutio/ontology/glyph.hpp
    code/ylikuutio/ontology/glyph_object.cpp
    code/ylikuutio/ontology/glyph_object.hpp
    code/ylikuutio/ontology/glyph_object_creation.cpp
    code/ylikuutio/ontology/glyph_object_creation.hpp
    code/ylikuutio/ontology/glyph_object_struct.hpp
    code/ylikuutio/ontology/glyph_struct.hpp
    code/ylikuutio/ontology/holobiont.cpp
    code/ylikuutio/ontology/holobiont.hpp
    code/ylikuutio/ontology/holobiont_struct.hpp
    code/ylikuutio/ontology/indexable.hpp
    code/ylikuutio/ontology/input_mode.cpp
    code/ylikuutio/ontology/input_mode.hpp
    code/ylikuutio/ontology/input_mode_apprentice_module.cpp
    code/ylikuutio/ontology/input_mode_apprentice_module.hpp
    code/ylikuutio/ontology/input_mode_child_module.cpp
    code/ylikuutio/ontology/input_mode_child_module.hpp
    code/ylikuutio/ontology/input_mode_struct.hpp
    code/ylikuutio/ontology/input_parameters_and_any_value_to_any_value_callback_with_universe.hpp
    code/ylikuutio/ontology/input_parameters_to_any_value_callback_with_console.hpp
    code/ylikuutio/ontology/lisp_function.cpp
    code/ylikuutio/ontology/lisp_function.hpp
    code/ylikuutio/ontology/lisp_function_overload.hpp
    code/ylikuutio/ontology/lisp_function_struct.hpp
    code/ylikuutio/ontology/locomotion_environment.hpp
    code/ylikuutio/ontology/locomotion_module.cpp
    code/ylikuutio/ontology/locomotion_module.hpp
    code/ylikuutio/ontology/locomotion_module_struct.hpp
    code/ylikuutio/ontology/master_module.hpp
    code/ylikuutio/ontology/master_of_input_modes_module.cpp
    code/ylikuutio/ontology/master_of_input_modes_module.hpp
    code/ylikuutio/ontology/material.cpp
    code/ylikuutio/ontology/material.hpp
    code/ylikuutio/ontology/material_struct.hpp
    code/ylikuutio/ontology/mesh_module.cpp
    code/ylikuutio/ontology/mesh_module.hpp
    code/ylikuutio/ontology/mesh_provider_struct.hpp
    code/ylikuutio/ontology/mission.cpp
    code/ylikuutio/ontology/mission.hpp
    code/ylikuutio/ontology/mission_struct.hpp
    code/ylikuutio/ontology/movable.cpp
    code/ylikuutio/ontology/movable.hpp
    code/ylikuutio/ontology/movable_struct.hpp
    code/ylikuutio/ontology/movable_variable_activation.cpp
    code/ylikuutio/ontology/movable_variable_activation.hpp
    code/ylikuutio/ontology/movable_variable_read.cpp
    code/ylikuutio/ontology/movable_variable_read.hpp
    code/ylikuutio/ontology/object.cpp
    code/ylikuutio/ontology/object.hpp
    code/ylikuutio/ontology/object_struct.hpp
    code/ylikuutio/ontology/orientation_module.cpp
    code/ylikuutio/ontology/orientation_module.hpp
    code/ylikuutio/ontology/parent_of_input_modes_module.cpp
    code/ylikuutio/ontology/parent_of_input_modes_module.hpp
    code/ylikuutio/ontology/parent_of_pipelines_module.cpp
    code/ylikuutio/ontology/parent_of_pipelines_module.hpp
    code/ylikuutio/ontology/read_callback.hpp
    code/ylikuutio/ontology/registry.cpp
    code/ylikuutio/ontology/registry.hpp
    code/ylikuutio/ontology/request.hpp
    code/ylikuutio/ontology/request_resolver.hpp
    code/ylikuutio/ontology/result.hpp
    code/ylikuutio/ontology/rigid_body_module.cpp
    code/ylikuutio/ontology/rigid_body_module.hpp
    code/ylikuutio/ontology/rigid_body_module_struct.hpp
    code/ylikuutio/ontology/scene.cpp
    code/ylikuutio/ontology/scene.hpp
    code/ylikuutio/ontology/scene_struct.hpp
    code/ylikuutio/ontology/terrain.cpp
    code/ylikuutio/ontology/terrain.hpp
    code/ylikuutio/ontology/variable.cpp
    code/ylikuutio/ontology/variable.hpp
    code/ylikuutio/ontology/variable_callbacks.cpp
    code/ylikuutio/ontology/variable_struct.hpp
    code/ylikuutio/ontology/pipeline.cpp
    code/ylikuutio/ontology/pipeline.hpp
    code/ylikuutio/ontology/pipeline_compare.cpp
    code/ylikuutio/ontology/pipeline_compare.hpp
    code/ylikuutio/ontology/pipeline_priority_queue.cpp
    code/ylikuutio/ontology/pipeline_priority_queue.hpp
    code/ylikuutio/ontology/pipeline_struct.hpp
    code/ylikuutio/ontology/shapeshifter.cpp
    code/ylikuutio/ontology/shapeshifter.hpp
    code/ylikuutio/ontology/shapeshifter_form.cpp
    code/ylikuutio/ontology/shapeshifter_form.hpp
    code/ylikuutio/ontology/shapeshifter_form_struct.hpp
    code/ylikuutio/ontology/shapeshifter_sequence.cpp
    code/ylikuutio/ontology/shapeshifter_sequence.hpp
    code/ylikuutio/ontology/shapeshifter_sequence_struct.hpp
    code/ylikuutio/ontology/shapeshifter_struct.hpp
    code/ylikuutio/ontology/shapeshifter_transformation.cpp
    code/ylikuutio/ontology/shapeshifter_transformation.hpp
    code/ylikuutio/ontology/shapeshifter_transformation_struct.hpp
    code/ylikuutio/ontology/species.cpp
    code/ylikuutio/ontology/species.hpp
    code/ylikuutio/ontology/species_struct.hpp
    code/ylikuutio/ontology/symbiont_material.cpp
    code/ylikuutio/ontology/symbiont_material.hpp
    code/ylikuutio/ontology/symbiont_material_struct.hpp
    code/ylikuutio/ontology/symbiont_species.cpp
    code/ylikuutio/ontology/symbiont_species.hpp
    code/ylikuutio/ontology/symbiosis.cpp
    code/ylikuutio/ontology/symbiosis.hpp
    code/ylikuutio/ontology/symbiosis_struct.hpp
    code/ylikuutio/ontology/terrain_generation_callbacks.cpp
    code/ylikuutio/ontology/terrain_generation_callbacks.hpp
    code/ylikuutio/ontology/texture_module.cpp
    code/ylikuutio/ontology/texture_module.hpp
    code/ylikuutio/ontology/text_2d.hpp
    code/ylikuutio/ontology/text_2d.cpp
    code/ylikuutio/ontology/text_3d.hpp
    code/ylikuutio/ontology/text_3d.cpp
    code/ylikuutio/ontology/text_3d_struct.hpp
    code/ylikuutio/ontology/text_struct.hpp
    code/ylikuutio/ontology/universe.cpp
    code/ylikuutio/ontology/universe.hpp
    code/ylikuutio/ontology/universe_callbacks.cpp
    code/ylikuutio/ontology/universe_struct.hpp
    code/ylikuutio/ontology/vector_font.cpp
    code/ylikuutio/ontology/vector_font.hpp
    code/ylikuutio/ontology/vector_font_struct.hpp
    code/ylikuutio/ontology/waypoint.cpp
    code/ylikuutio/ontology/waypoint.hpp
    code/ylikuutio/ontology/waypoint_struct.hpp

    # opengl, in alphabetical order
    code/ylikuutio/opengl/opengl.cpp
    code/ylikuutio/opengl/opengl.hpp
    code/ylikuutio/opengl/opengl_texture.cpp
    code/ylikuutio/opengl/opengl_texture.hpp
    code/ylikuutio/opengl/ubo_block_enums.hpp
    code/ylikuutio/opengl/vboindexer.cpp
    code/ylikuutio/opengl/vboindexer.hpp
    code/ylikuutio/opengl/ylikuutio_glew.hpp

    # render, in alphabetical order
    code/ylikuutio/render/graphics_api_backend.hpp
    code/ylikuutio/render/render_model.hpp
    code/ylikuutio/render/render_struct.hpp
    code/ylikuutio/render/render_system.cpp
    code/ylikuutio/render/render_system.hpp
    code/ylikuutio/render/render_system_struct.hpp
    code/ylikuutio/render/render_templates.hpp

    # sdl, in alphabetical order
    code/ylikuutio/sdl/ylikuutio_sdl.cpp
    code/ylikuutio/sdl/ylikuutio_sdl.hpp

    # shaders, in alphabetical order
    code/ylikuutio/shaders/standard_shading.frag
    code/ylikuutio/shaders/standard_shading.vert
    code/ylikuutio/shaders/text_vertex_shader.frag
    code/ylikuutio/shaders/text_vertex_shader.vert

    # string, in alphabetical order
    code/ylikuutio/string/string_set.cpp
    code/ylikuutio/string/string_set.hpp
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

add_library(snippets STATIC
    # snippets, in alphabetical order
    code/ylikuutio/snippets/background_color_snippets.cpp
    code/ylikuutio/snippets/background_color_snippets.hpp
    code/ylikuutio/snippets/brain_snippets.cpp
    code/ylikuutio/snippets/brain_snippets.hpp
    code/ylikuutio/snippets/callback_snippets.cpp
    code/ylikuutio/snippets/callback_snippets.hpp
    code/ylikuutio/snippets/console_callback_snippets.cpp
    code/ylikuutio/snippets/console_callback_snippets.hpp
    code/ylikuutio/snippets/debug_snippets.cpp
    code/ylikuutio/snippets/debug_snippets.hpp
    code/ylikuutio/snippets/framebuffer_snippets.cpp
    code/ylikuutio/snippets/framebuffer_snippets.hpp
    code/ylikuutio/snippets/keyboard_callback_snippets.cpp
    code/ylikuutio/snippets/keyboard_callback_snippets.hpp
    code/ylikuutio/snippets/location_and_orientation_snippets.cpp
    code/ylikuutio/snippets/location_and_orientation_snippets.hpp
    code/ylikuutio/snippets/movement_snippets.cpp
    code/ylikuutio/snippets/movement_snippets.hpp
    code/ylikuutio/snippets/wireframe_snippets.cpp
    code/ylikuutio/snippets/wireframe_snippets.hpp

    # locomotion snippets, in alphabetical order
    code/ylikuutio/snippets/locomotion/climb_module.cpp
    code/ylikuutio/snippets/locomotion/climb_module.hpp
    code/ylikuutio/snippets/locomotion/dive_module.cpp
    code/ylikuutio/snippets/locomotion/dive_module.hpp
    code/ylikuutio/snippets/locomotion/fly_module.cpp
    code/ylikuutio/snippets/locomotion/fly_module.hpp
    code/ylikuutio/snippets/locomotion/gait_module.cpp
    code/ylikuutio/snippets/locomotion/gait_module.hpp
    code/ylikuutio/snippets/locomotion/rail_vehicle_module.cpp
    code/ylikuutio/snippets/locomotion/rail_vehicle_module.hpp
    code/ylikuutio/snippets/locomotion/road_vehicle_module.cpp
    code/ylikuutio/snippets/locomotion/road_vehicle_module.hpp
    code/ylikuutio/snippets/locomotion/ship_module.cpp
    code/ylikuutio/snippets/locomotion/ship_module.hpp
    code/ylikuutio/snippets/locomotion/swim_module.cpp
    code/ylikuutio/snippets/locomotion/swim_module.hpp
    )

# Ajokki
add_executable(ajokki
    # ajokki, in alphabetical order
    code/ajokki/ajokki.cpp
    code/ajokki/ajokki.hpp
    code/ajokki/lisp/ajokki_console_callbacks.cpp
    code/ajokki/lisp/ajokki_console_callbacks.hpp
    code/ajokki/ecosystem/ajokki_earth_ecosystem.cpp
    code/ajokki/scene/ajokki_helsinki_east_downtown_scene.cpp
    code/ajokki/scene/ajokki_joensuu_center_west_scene.cpp
    )
target_link_libraries(ajokki snippets ylikuutio ${ALL_LIBS} ${THREAD_LIBS})

# GPGPU test
add_executable(gpgpu_test
    # gpgpu_test, in alphabetical order
    code/gpgpu_test/gpgpu_test.cpp
    code/gpgpu_test/gpgpu_test.hpp
    code/gpgpu_test/gpgpu_test_scene.cpp

    # snippets, in alphabetical order
    code/ylikuutio/snippets/keyboard_callback_snippets.cpp
    code/ylikuutio/snippets/keyboard_callback_snippets.hpp
    )
target_link_libraries(gpgpu_test ylikuutio ${ALL_LIBS} ${THREAD_LIBS})

# Hirvi libraries
add_library(hirvi_lib STATIC
    code/hirvi/ontology/cat.cpp
    code/hirvi/ontology/cat.hpp
    code/hirvi/data/datatype.hpp
    code/hirvi/ontology/elk.cpp
    code/hirvi/ontology/elk.hpp
    code/hirvi/ontology/emancipation_module.cpp
    code/hirvi/ontology/emancipation_module.hpp
    code/hirvi/lisp/hirvi_console_callbacks.cpp
    code/hirvi/lisp/hirvi_console_callbacks.hpp
    code/hirvi/ecosystem/hirvi_earth_ecosystem.cpp
    code/hirvi/scene/hirvi_helsinki_east_downtown_scene.cpp
    code/hirvi/ontology/police_car.cpp
    code/hirvi/ontology/police_car.hpp
    code/hirvi/ontology/police_dog.cpp
    code/hirvi/ontology/police_dog.hpp
    code/hirvi/ontology/police_helicopter.cpp
    code/hirvi/ontology/police_helicopter.hpp
    code/hirvi/ontology/police_horse.cpp
    code/hirvi/ontology/police_horse.hpp
    code/hirvi/ontology/police_module.cpp
    code/hirvi/ontology/police_module.hpp
    code/hirvi/ontology/police_train.cpp
    code/hirvi/ontology/police_train.hpp
    code/hirvi/ontology/police_tram.cpp
    code/hirvi/ontology/police_tram.hpp
    code/hirvi/ontology/train.cpp
    code/hirvi/ontology/train.hpp
    )
target_link_libraries(hirvi_lib snippets ylikuutio ${ALL_LIBS} ${THREAD_LIBS})

# Hirvi game application
add_executable(hirvi
    # hirvi, in alphabetical order
    code/hirvi/hirvi.cpp
    code/hirvi/hirvi.hpp
    )
target_link_libraries(hirvi hirvi_lib)

# Mock
add_executable(mock
    # mock, in alphabetical order
    code/mock/mock_application.cpp
    code/mock/mock_application.hpp
    )
target_link_libraries(mock snippets ylikuutio ${ALL_LIBS} ${THREAD_LIBS})

# Tulevaisuus
add_executable(tulevaisuus
    # tulevaisuus, in alphabetical order
    code/tulevaisuus/tulevaisuus.cpp
    code/tulevaisuus/tulevaisuus.hpp
    code/tulevaisuus/tulevaisuus_console_callbacks.cpp
    code/tulevaisuus/tulevaisuus_console_callbacks.hpp
    )
target_link_libraries(tulevaisuus snippets ylikuutio ${ALL_LIBS} ${THREAD_LIBS})

# YliEdit
add_executable(yli_edit
    # yli_edit, in alphabetical order
    code/edit/yli_edit.cpp
    code/edit/yli_edit.hpp
    code/edit/yli_edit_console_callbacks.cpp
    code/edit/yli_edit_console_callbacks.hpp
    )
target_link_libraries(yli_edit snippets ylikuutio ${ALL_LIBS} ${THREAD_LIBS})

# Asio-test
if(FALSE)
    add_executable(asio_chat_server
        code/asio/asio_chat_server.cpp
        )
    target_link_libraries(asio_chat_server ${THREAD_LIBS})

    add_executable(asio_chat_client
        code/asio/asio_chat_client.cpp
        )
    target_link_libraries(asio_chat_client ${THREAD_LIBS})

    add_executable(asio_nslookup
        code/asio/asio_nslookup.cpp
        )
    target_link_libraries(asio_nslookup ${THREAD_LIBS})
endif()

# future-test
add_executable(future_test
    code/thread_test/future_test.cpp
    )
target_link_libraries(future_test ${THREAD_LIBS})

# thread-test
add_executable(thread_test
    code/thread_test/thread_test.cpp
    )
target_link_libraries(thread_test ${THREAD_LIBS})

# dining philosophers
add_executable(dining_philosophers
    code/thread_test/dining_philosophers.cpp
    )
target_link_libraries(dining_philosophers ${THREAD_LIBS})

if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
    # Planetary simulation library
    add_library(planetary_simulation STATIC
        code/avaruus/fortran/constants.f90
        code/avaruus/fortran/file.f90
        code/avaruus/fortran/global_parameters.f90
        code/avaruus/fortran/my_kind.f90
        code/avaruus/fortran/object.f90
        code/avaruus/fortran/physics.f90
        code/avaruus/fortran/parser.f90
        code/avaruus/fortran/avaruus.f90
        code/avaruus/fortran/planetary_system.f90
        code/avaruus/fortran/string.f90
    )
    target_compile_features(planetary_simulation PUBLIC cxx_std_20)
    set_target_properties(planetary_simulation PROPERTIES CXX_EXTENSIONS OFF)

    FortranCInterface_HEADER(code/avaruus/cpp/tests/planetary_simulation.h
        planet
        planet)

    add_executable(avaruus_fortran
        code/avaruus/fortran/avaruus.f90
    )
    target_link_libraries(avaruus_fortran planetary_simulation)
endif()

# Tests
if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    enable_testing()

    set(YLIKUUTIO_UNIT_TESTS
        code/mock/mock_application.cpp
        code/mock/mock_application.hpp
        code/ylikuutio/tests/test_any_value.cpp
        code/ylikuutio/tests/test_ascii_grid_heightmap_loader.cpp
        # code/ylikuutio/tests/test_asio.cpp
        code/ylikuutio/tests/test_audio_track.cpp
        code/ylikuutio/tests/test_bilinear_interpolation.cpp
        code/ylikuutio/tests/test_brain.cpp
        code/ylikuutio/tests/test_brain_snippets.cpp
        code/ylikuutio/tests/test_brain_struct.cpp
        code/ylikuutio/tests/test_callback_engine.cpp
        code/ylikuutio/tests/test_callback_object.cpp
        code/ylikuutio/tests/test_callback_object_struct.cpp
        code/ylikuutio/tests/test_callback_parameter.cpp
        code/ylikuutio/tests/test_callback_parameter_struct.cpp
        code/ylikuutio/tests/test_callback_system.cpp
        code/ylikuutio/tests/test_camera.cpp
        code/ylikuutio/tests/test_cartesian_coordinates_module.cpp
        code/ylikuutio/tests/test_check_and_report_if_some_string_matches.cpp
        code/ylikuutio/tests/test_command_line_master.cpp
        code/ylikuutio/tests/test_compute_task.cpp
        code/ylikuutio/tests/test_compute_task_struct.cpp
        code/ylikuutio/tests/test_console.cpp
        code/ylikuutio/tests/test_console_callback_engine.cpp
        code/ylikuutio/tests/test_console_callback_object.cpp
        code/ylikuutio/tests/test_console_callback_object_struct.cpp
        code/ylikuutio/tests/test_console_callback_parameter.cpp
        code/ylikuutio/tests/test_console_callback_parameter_struct.cpp
        code/ylikuutio/tests/test_console_state_module.cpp
        code/ylikuutio/tests/test_constructible_module.cpp
        code/ylikuutio/tests/test_csv_loader.cpp
        code/ylikuutio/tests/test_current_input.cpp
        code/ylikuutio/tests/test_ecosystem.cpp
        code/ylikuutio/tests/test_extract_last_part_of_string.cpp
        code/ylikuutio/tests/test_extract_string.cpp
        code/ylikuutio/tests/test_extract_string_with_several_endings.cpp
        code/ylikuutio/tests/test_extract_unicode_value_from_string.cpp
        code/ylikuutio/tests/test_fbx_loader.cpp
        code/ylikuutio/tests/test_file_loader.cpp
        code/ylikuutio/tests/test_font_2d.cpp
        code/ylikuutio/tests/test_glyph.cpp
        code/ylikuutio/tests/test_graph.cpp
        code/ylikuutio/tests/test_holobiont.cpp
        code/ylikuutio/tests/test_indexing.cpp
        code/ylikuutio/tests/test_input_method.cpp
        code/ylikuutio/tests/test_input_mode.cpp
        code/ylikuutio/tests/test_line_2d.cpp
        code/ylikuutio/tests/test_line_line_intersection.cpp
        code/ylikuutio/tests/test_line_segment_line_segment_intersection.cpp
        code/ylikuutio/tests/test_lisp_function.cpp
        code/ylikuutio/tests/test_lisp_function_overload.cpp
        code/ylikuutio/tests/test_lisp_function_struct.cpp
        code/ylikuutio/tests/test_linear_algebra.cpp
        code/ylikuutio/tests/test_material.cpp
        code/ylikuutio/tests/test_material_struct.cpp
        code/ylikuutio/tests/test_memory_allocator.cpp
        code/ylikuutio/tests/test_memory_storage.cpp
        code/ylikuutio/tests/test_memory_system.cpp
        code/ylikuutio/tests/test_memory_templates.cpp
        code/ylikuutio/tests/test_model_struct.cpp
        code/ylikuutio/tests/test_obj_loader.cpp
        code/ylikuutio/tests/test_object.cpp
        code/ylikuutio/tests/test_object_struct.cpp
        code/ylikuutio/tests/test_orientation_module.cpp
        code/ylikuutio/tests/test_png_heightmap_loader.cpp
        code/ylikuutio/tests/test_png_loader.cpp
        code/ylikuutio/tests/test_pugixml.cpp
        code/ylikuutio/tests/test_quad_triangulation.cpp
        code/ylikuutio/tests/test_queue.cpp
        code/ylikuutio/tests/test_registry.cpp
        code/ylikuutio/tests/test_request.cpp
        code/ylikuutio/tests/test_scene.cpp
        code/ylikuutio/tests/test_pipeline.cpp
        code/ylikuutio/tests/test_pipeline_struct.cpp
        code/ylikuutio/tests/test_scrollback_buffer.cpp
        code/ylikuutio/tests/test_shapeshifter.cpp
        code/ylikuutio/tests/test_species.cpp
        code/ylikuutio/tests/test_symbiont_material.cpp
        code/ylikuutio/tests/test_symbiont_material_struct.cpp
        code/ylikuutio/tests/test_symbiont_species.cpp
        code/ylikuutio/tests/test_symbiosis.cpp
        code/ylikuutio/tests/test_symbiosis_loader_struct.cpp
        code/ylikuutio/tests/test_symbiosis_struct.cpp
        code/ylikuutio/tests/test_temp_input.cpp
        code/ylikuutio/tests/test_text_2d.cpp
        code/ylikuutio/tests/test_text_3d.cpp
        code/ylikuutio/tests/test_text_input.cpp
        code/ylikuutio/tests/test_text_input_history.cpp
        code/ylikuutio/tests/test_text_line.cpp
        code/ylikuutio/tests/test_token.cpp
        code/ylikuutio/tests/test_triangulation.cpp
        code/ylikuutio/tests/test_universe.cpp
        code/ylikuutio/tests/test_universe_callbacks.cpp
        code/ylikuutio/tests/test_universe_struct.cpp
        code/ylikuutio/tests/test_variable.cpp
        code/ylikuutio/tests/test_variable_struct.cpp
        code/ylikuutio/tests/test_vector_font.cpp
        code/ylikuutio/tests/test_vector_font_struct.cpp
        code/ylikuutio/tests/test_waypoint.cpp
        code/ylikuutio/tests/test_ylikuutio_map.cpp)

    set(HIRVI_UNIT_TESTS
        # Tests for Hirvi.
        code/hirvi/hirvi.cpp
        code/hirvi/hirvi.hpp
        code/hirvi/tests/test_hirvi_application.cpp
        code/hirvi/tests/test_brain.cpp
        code/hirvi/tests/test_callback_engine.cpp
        code/hirvi/tests/test_cat.cpp
        code/hirvi/tests/test_ecosystem.cpp
        code/hirvi/tests/test_material.cpp
        code/hirvi/tests/test_memory.cpp
        code/hirvi/tests/test_pipeline.cpp
        code/hirvi/tests/test_police_car.cpp
        code/hirvi/tests/test_scene.cpp
        code/hirvi/tests/test_species.cpp
        code/hirvi/tests/test_symbiosis.cpp)

    if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
        set(AVARUUS_UNIT_TESTS
            # Tests for Avaruus.
            code/avaruus/cpp/tests/test_read_file.cpp
            code/avaruus/cpp/tests/test_get_line.cpp
            code/avaruus/cpp/tests/test_get_line_i_with_n_token_statement.cpp
            code/avaruus/cpp/tests/test_get_has_line_code.cpp
            code/avaruus/cpp/tests/test_get_first_token.cpp
            code/avaruus/cpp/tests/test_get_n_of_code_lines_between.cpp
            code/avaruus/cpp/tests/test_get_nth_token.cpp
            code/avaruus/cpp/tests/test_parse.cpp
            code/avaruus/cpp/tests/test_parse_global_parameters.cpp
        )
    endif()

    set(MAIN_FILE code/ylikuutio/tests/main.cpp)

    add_executable(test_ylikuutio code/ylikuutio/tests/test_main.cpp ${YLIKUUTIO_UNIT_TESTS})
    set_property(TARGET test_ylikuutio PROPERTY COMPILE_FLAGS "-DGOOGLE_TEST")

    add_executable(test_hirvi code/ylikuutio/tests/test_main.cpp ${HIRVI_UNIT_TESTS})
    set_property(TARGET test_hirvi PROPERTY COMPILE_FLAGS "-DGOOGLE_TEST")

    if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
        add_executable(test_avaruus code/ylikuutio/tests/test_main.cpp ${AVARUUS_UNIT_TESTS})
        set_property(TARGET test_avaruus PROPERTY COMPILE_FLAGS "-DGOOGLE_TEST")

        target_compile_features(test_avaruus PUBLIC cxx_std_20)
        set_target_properties(test_avaruus PROPERTIES CXX_EXTENSIONS OFF)
        target_link_libraries(test_avaruus gtest_main planetary_simulation)
    endif()

    if (DEFINED "PNG_LIBRARIES")
        target_link_libraries(test_ylikuutio gtest_main snippets ylikuutio soloud SDL2 GLEW_200 ${PNG_LIBRARIES} ${THREAD_LIBS})
        target_link_libraries(test_hirvi gtest_main hirvi_lib snippets ylikuutio soloud SDL2 GLEW_200 ${PNG_LIBRARIES} ${THREAD_LIBS})
    else()
        target_link_libraries(test_ylikuutio gtest_main snippets ylikuutio soloud SDL2 GLEW_200 ${PNG_LIBRARY} ${THREAD_LIBS})
        target_link_libraries(test_hirvi gtest_main hirvi_lib snippets ylikuutio soloud SDL2 GLEW_200 ${PNG_LIBRARY} ${THREAD_LIBS})
    endif()

    include(GoogleTest)
    gtest_discover_tests(test_ylikuutio)
endif()
