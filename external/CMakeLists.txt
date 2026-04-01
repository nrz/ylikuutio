add_definitions(
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    )

include_directories(
    SDL/include/
    glew-2.0.0/include/
    glm/
    zlib/
    libpng-1.6.44/
    pugixml/src/
    OpenFBX/src/
    )

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

### GLEW ###

add_library(GLEW_200 STATIC)
target_sources(GLEW_200 PRIVATE
    glew-2.0.0/src/glew.c)
target_link_libraries(GLEW_200
    ${OPENGL_LIBRARY}
    ${EXTRA_LIBS}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND NOT CMAKE_CROSSCOMPILING)
    include(FetchContent)
    set(ZLIB_BUILD_TESTING CACHE INTERNAL OFF)
    set(ZLIB_INSTALL_COMPAT_DLL CACHE INTERNAL OFF)
    set(ZLIB_CONF_WRITTEN FALSE)
    FetchContent_Declare(
        zlib
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/zlib
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_MakeAvailable(zlib)

    # Make the ALIAS that libpng expects, if necessary
    if(NOT TARGET ZLIB::ZLIB)
        add_library(ZLIB::ZLIB UNKNOWN IMPORTED)
        set(ZLIB_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/zlib)
        set_target_properties(ZLIB::ZLIB PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            "${ZLIB_INCLUDE_DIRS}")

        if (ZLIB_VERSION)
            set_target_properties(ZLIB::ZLIB PROPERTIES VERSION "${ZLIB_VERSION}")
        endif()
        set_target_properties(ZLIB::ZLIB PROPERTIES IMPORTED_LOCATION "${ZLIB_LIBRARIES}" LINK_LIBRARIES "${ZLIB_LIBRARIES}")
        add_dependencies(ZLIB::ZLIB zlib)
    endif()

    set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${CMAKE_SOURCE_DIR}/external/zlib/lib/pkgconfig")

    set(PNG_SHARED CACHE INTERNAL OFF)
    set(PNG_TESTS CACHE INTERNAL OFF)
    set(PNG_TOOLS CACHE INTERNAL OFF)
elseif(COMPILE_ZLIB_FROM_SOURCE)
    # Make the ALIAS that libpng expects, if necessary
    if(NOT TARGET ZLIB::ZLIB)
        if(TARGET zlibstatic)
            add_library(ZLIB::ZLIB ALIAS zlibstatic)
        elseif(TARGET zlib)
            add_library(ZLIB::ZLIB ALIAS zlib)
        endif()
    endif()

    add_subdirectory(zlib)
endif()

if(COMPILE_LIBPNG_FROM_SOURCE)
    add_subdirectory(libpng-1.6.44)
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
