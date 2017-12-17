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

# pugixml
add_subdirectory(pugixml)

### GLFW ###
add_subdirectory(glfw)

include_directories(
    asio/asio/include/
    FastNoiseSIMD/
    glew-2.0.0/include/
    glfw/include/
    glm/
    pugixml/src/
    OpenFBX/src/
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

### ASIO ###
add_subdirectory(asio)

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
