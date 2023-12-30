# CMake entry point
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0004 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(planetary_simulation VERSION 0.0.1)
project(planetary_simulation LANGUAGES CXX Fortran)

include(FortranCInterface)
FortranCInterface_VERIFY(CXX)

set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Command line arguments not supported by Visual Studio.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wextra -Wuninitialized -Werror=return-type")
endif()

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

if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    # for Google Test.
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/77962730563eece3525f40b8769e4ca0c6baf64c.zip
        )

    FetchContent_MakeAvailable(googletest)

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
endif()

configure_file(run/input.dat input.dat COPYONLY)
configure_file(run/empty_file_for_testing.dat  empty_file_for_testing.dat COPYONLY)
configure_file(run/one_line_for_testing.dat    one_line_for_testing.dat COPYONLY)
configure_file(run/three_lines_for_testing.dat three_lines_for_testing.dat COPYONLY)

# Planetary simulation library
add_library(planetary_simulation STATIC
    src/constants.f90
    src/file.f90
    src/my_kind.f90
    src/object.f90
    src/planetary_motion.f90
    src/planetary_system.f90
    src/string.f90
    src/verlet_integration.f90
    )
    target_compile_features(planetary_simulation PUBLIC cxx_std_20)
    set_target_properties(planetary_simulation PROPERTIES CXX_EXTENSIONS OFF)

    FortranCInterface_HEADER(src/tests/planetary_simulation.h
        planet
        planet)

add_executable(simulate
    src/planetary_motion.f90
)
target_link_libraries(simulate planetary_simulation)

# Tests
if(DO_UNIT_TESTS_WITH_GOOGLE_TEST)
    enable_testing()

    set(UNIT_TESTS
        src/tests/test_read_file.cpp
        src/tests/test_get_line.cpp
        src/tests/test_get_has_line_code.cpp
        src/tests/test_get_first_token.cpp
    )
    set(MAIN_FILE src/tests/googletest/main.cpp)

    add_executable(unit_tests_with_googletest src/tests/test_main.cpp ${UNIT_TESTS})
    set_property(TARGET unit_tests_with_googletest PROPERTY COMPILE_FLAGS "-DGOOGLE_TEST")

    target_compile_features(unit_tests_with_googletest PUBLIC cxx_std_20)
    set_target_properties(unit_tests_with_googletest PROPERTIES CXX_EXTENSIONS OFF)
    target_link_libraries(unit_tests_with_googletest gtest_main planetary_simulation)

    include(GoogleTest)
    gtest_discover_tests(unit_tests_with_googletest)
endif()
