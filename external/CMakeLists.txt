add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -D_CRT_SECURE_NO_WARNINGS
    )

if(NOT (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Android"))
    # do not try co compile GLEW when targeting Android.
    add_definitions(
        -DGLEW_STATIC
        )
endif()

include_directories(
    # asio/asio/include/
    FastNoiseSIMD/
    glm/
    OpenFBX/src/
    pugixml/src/
    )

if(NOT (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Android"))
    # do not try co compile GLEW when targeting Android.
    include_directories(
        glew-2.0.0/include/
        )
endif()

# Compile external dependencies

# pugixml
add_subdirectory(pugixml)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if(NOT CROSS_COMPILE_FOR_WINDOWS)
        set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            )
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        ${CMAKE_DL_LIBS}
        )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### ASIO ###
# add_subdirectory(asio)

### GLEW ###

if(NOT (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Android"))
    add_library(GLEW_200 STATIC)
    target_sources(GLEW_200 PRIVATE
        glew-2.0.0/src/glew.c)
    target_link_libraries(GLEW_200
        ${OPENGL_LIBRARY}
        ${EXTRA_LIBS}
        )
endif()

if(COMPILE_ZLIB_FROM_SOURCE)
    add_subdirectory(zlib)
endif()

if(COMPILE_LIBPNG_FROM_SOURCE)
    add_subdirectory(libpng-1.6.37)
endif()

add_library(miniz STATIC
    OpenFBX/src/miniz.c
    OpenFBX/src/miniz.h
    )
add_library(OpenFBX STATIC
    OpenFBX/src/ofbx.cpp
    OpenFBX/src/ofbx.h
    )
add_dependencies(OpenFBX miniz)
target_link_libraries(OpenFBX miniz)
set_property(TARGET OpenFBX PROPERTY COMPILE_FLAGS "-std=c++14")

if(COMPILE_SDL_FROM_SOURCE)
    add_subdirectory(SDL)
endif()
