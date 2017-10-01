if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
    add_definitions( "/MP" )
endif()

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    )

# Compile external dependencies
# add_subdirectory(gdal-2.1.1)

# Compile external dependencies

# Assimp
add_subdirectory(assimp)

# pugixml
add_subdirectory(pugixml)

# FastNoiseSIMD
add_subdirectory(FastNoiseSIMD)

### GLFW ###
add_subdirectory(glfw-3.2)

# TinySceme #
if(ENABLE_SCRIPTING_WITH_TINYSCHEME)
    add_subdirectory(tinyscheme-1.41)
    include_directories(
        tinyscheme-1.41/
        )
endif()

include_directories(
    assimp/include/
    FastNoiseSIMD/
    glew-2.0.0/include/
    glfw-3.2/include/
    glm/
    pugixml/src/
    .
    )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if(NOT CROSS_COMPILE_FOR_WINDOWS)
        set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        ${CMAKE_DL_LIBS}
        ${GLFW_LIBRARIES}
        )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
    glew-2.0.0/src/glew.c
    )

set(GLEW_HEADERS
    )

add_library(GLEW_200 STATIC
    ${GLEW_SOURCE}
    ${GLEW_INCLUDE}
    )

target_link_libraries(GLEW_200
    ${OPENGL_LIBRARY}
    ${EXTRA_LIBS}
    )

add_library(tinyscheme STATIC
    tinyscheme-1.41/dynload.c
    tinyscheme-1.41/dynload.h
    tinyscheme-1.41/opdefines.h
    tinyscheme-1.41/scheme.c
    tinyscheme-1.41/scheme.h
    tinyscheme-1.41/scheme-private.h
    )
set_property(TARGET tinyscheme PROPERTY COMPILE_FLAGS "-DSTANDALONE=0 -DUSE_INTERFACE=1")
