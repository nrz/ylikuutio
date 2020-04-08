if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
    add_definitions( "/MP" )
endif()

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

if (COMPILE_SDL_FROM_SOURCE)
    include_directories(
        SDL2-2.0.12/src
        SDL2-2.0.12/src/loadso
        SDL2-2.0.12/src/loadso/dummy
        SDL2-2.0.12/src/loadso/windows
        SDL2-2.0.12/src/loadso/dlopen
        SDL2-2.0.12/src/main
        SDL2-2.0.12/src/main/dummy
        SDL2-2.0.12/src/main/haiku
        SDL2-2.0.12/src/main/android
        SDL2-2.0.12/src/main/winrt
        SDL2-2.0.12/src/main/uikit
        SDL2-2.0.12/src/main/nacl
        SDL2-2.0.12/src/main/psp
        SDL2-2.0.12/src/main/windows
        SDL2-2.0.12/src/hidapi
        SDL2-2.0.12/src/hidapi/hidapi
        SDL2-2.0.12/src/hidapi/pc
        SDL2-2.0.12/src/hidapi/libusb
        SDL2-2.0.12/src/hidapi/android
        SDL2-2.0.12/src/hidapi/android/jni
        SDL2-2.0.12/src/hidapi/ios
        SDL2-2.0.12/src/hidapi/linux
        SDL2-2.0.12/src/hidapi/mac
        SDL2-2.0.12/src/hidapi/testgui
        SDL2-2.0.12/src/hidapi/testgui/TestGUI.app.in
        SDL2-2.0.12/src/hidapi/testgui/TestGUI.app.in/Contents
        SDL2-2.0.12/src/hidapi/testgui/TestGUI.app.in/Contents/Resources
        SDL2-2.0.12/src/hidapi/testgui/TestGUI.app.in/Contents/Resources/English.lproj
        SDL2-2.0.12/src/hidapi/windows
        SDL2-2.0.12/src/hidapi/windows/ddk_build
        SDL2-2.0.12/src/hidapi/hidtest
        SDL2-2.0.12/src/hidapi/udev
        SDL2-2.0.12/src/hidapi/doxygen
        SDL2-2.0.12/src/hidapi/m4
        SDL2-2.0.12/src/audio
        SDL2-2.0.12/src/audio/dummy
        SDL2-2.0.12/src/audio/haiku
        SDL2-2.0.12/src/audio/directsound
        SDL2-2.0.12/src/audio/openslES
        SDL2-2.0.12/src/audio/arts
        SDL2-2.0.12/src/audio/winmm
        SDL2-2.0.12/src/audio/emscripten
        SDL2-2.0.12/src/audio/android
        SDL2-2.0.12/src/audio/dsp
        SDL2-2.0.12/src/audio/coreaudio
        SDL2-2.0.12/src/audio/nacl
        SDL2-2.0.12/src/audio/wasapi
        SDL2-2.0.12/src/audio/pulseaudio
        SDL2-2.0.12/src/audio/sun
        SDL2-2.0.12/src/audio/jack
        SDL2-2.0.12/src/audio/fusionsound
        SDL2-2.0.12/src/audio/psp
        SDL2-2.0.12/src/audio/disk
        SDL2-2.0.12/src/audio/paudio
        SDL2-2.0.12/src/audio/nas
        SDL2-2.0.12/src/audio/sndio
        SDL2-2.0.12/src/audio/netbsd
        SDL2-2.0.12/src/audio/esd
        SDL2-2.0.12/src/audio/alsa
        SDL2-2.0.12/src/audio/qsa
        SDL2-2.0.12/src/stdlib
        SDL2-2.0.12/src/atomic
        SDL2-2.0.12/src/render
        SDL2-2.0.12/src/render/metal
        SDL2-2.0.12/src/render/psp
        SDL2-2.0.12/src/render/opengles2
        SDL2-2.0.12/src/render/direct3d
        SDL2-2.0.12/src/render/direct3d11
        SDL2-2.0.12/src/render/opengles
        SDL2-2.0.12/src/render/opengl
        SDL2-2.0.12/src/render/software
        SDL2-2.0.12/src/timer
        SDL2-2.0.12/src/timer/dummy
        SDL2-2.0.12/src/timer/haiku
        SDL2-2.0.12/src/timer/psp
        SDL2-2.0.12/src/timer/windows
        SDL2-2.0.12/src/timer/unix
        SDL2-2.0.12/src/joystick
        SDL2-2.0.12/src/joystick/bsd
        SDL2-2.0.12/src/joystick/dummy
        SDL2-2.0.12/src/joystick/haiku
        SDL2-2.0.12/src/joystick/hidapi
        SDL2-2.0.12/src/joystick/hidapi/steam
        SDL2-2.0.12/src/joystick/emscripten
        SDL2-2.0.12/src/joystick/android
        SDL2-2.0.12/src/joystick/linux
        SDL2-2.0.12/src/joystick/darwin
        SDL2-2.0.12/src/joystick/iphoneos
        SDL2-2.0.12/src/joystick/psp
        SDL2-2.0.12/src/joystick/windows
        SDL2-2.0.12/src/joystick/steam
        SDL2-2.0.12/src/power
        SDL2-2.0.12/src/power/haiku
        SDL2-2.0.12/src/power/emscripten
        SDL2-2.0.12/src/power/android
        SDL2-2.0.12/src/power/winrt
        SDL2-2.0.12/src/power/uikit
        SDL2-2.0.12/src/power/linux
        SDL2-2.0.12/src/power/psp
        SDL2-2.0.12/src/power/windows
        SDL2-2.0.12/src/power/macosx
        SDL2-2.0.12/src/sensor
        SDL2-2.0.12/src/sensor/dummy
        SDL2-2.0.12/src/sensor/coremotion
        SDL2-2.0.12/src/sensor/android
        SDL2-2.0.12/src/dynapi
        SDL2-2.0.12/src/haptic
        SDL2-2.0.12/src/haptic/dummy
        SDL2-2.0.12/src/haptic/android
        SDL2-2.0.12/src/haptic/linux
        SDL2-2.0.12/src/haptic/darwin
        SDL2-2.0.12/src/haptic/windows
        SDL2-2.0.12/src/test
        SDL2-2.0.12/src/cpuinfo
        SDL2-2.0.12/src/thread
        SDL2-2.0.12/src/thread/generic
        SDL2-2.0.12/src/thread/pthread
        SDL2-2.0.12/src/thread/psp
        SDL2-2.0.12/src/thread/windows
        SDL2-2.0.12/src/thread/stdcpp
        SDL2-2.0.12/src/file
        SDL2-2.0.12/src/file/cocoa
        SDL2-2.0.12/src/libm
        SDL2-2.0.12/src/core
        SDL2-2.0.12/src/core/android
        SDL2-2.0.12/src/core/winrt
        SDL2-2.0.12/src/core/linux
        SDL2-2.0.12/src/core/windows
        SDL2-2.0.12/src/core/unix
        SDL2-2.0.12/src/filesystem
        SDL2-2.0.12/src/filesystem/cocoa
        SDL2-2.0.12/src/filesystem/dummy
        SDL2-2.0.12/src/filesystem/haiku
        SDL2-2.0.12/src/filesystem/emscripten
        SDL2-2.0.12/src/filesystem/android
        SDL2-2.0.12/src/filesystem/winrt
        SDL2-2.0.12/src/filesystem/nacl
        SDL2-2.0.12/src/filesystem/windows
        SDL2-2.0.12/src/filesystem/unix
        SDL2-2.0.12/src/video
        SDL2-2.0.12/src/video/cocoa
        SDL2-2.0.12/src/video/dummy
        SDL2-2.0.12/src/video/haiku
        SDL2-2.0.12/src/video/kmsdrm
        SDL2-2.0.12/src/video/emscripten
        SDL2-2.0.12/src/video/yuv2rgb
        SDL2-2.0.12/src/video/android
        SDL2-2.0.12/src/video/winrt
        SDL2-2.0.12/src/video/uikit
        SDL2-2.0.12/src/video/nacl
        SDL2-2.0.12/src/video/wayland
        SDL2-2.0.12/src/video/arm
        SDL2-2.0.12/src/video/vivante
        SDL2-2.0.12/src/video/x11
        SDL2-2.0.12/src/video/psp
        SDL2-2.0.12/src/video/qnx
        SDL2-2.0.12/src/video/directfb
        SDL2-2.0.12/src/video/windows
        SDL2-2.0.12/src/video/raspberry
        SDL2-2.0.12/src/video/pandora
        SDL2-2.0.12/src/video/khronos
        SDL2-2.0.12/src/video/khronos/GLES2
        SDL2-2.0.12/src/video/khronos/vulkan
        SDL2-2.0.12/src/video/khronos/KHR
        SDL2-2.0.12/src/video/khronos/EGL
        SDL2-2.0.12/src/video/offscreen
        SDL2-2.0.12/src/events
        )
endif()

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
endif()

add_library(stb STATIC
    stb/stb_image.h
    )
set_property(TARGET stb PROPERTY LINKER_LANGUAGE C)
set_property(TARGET stb PROPERTY COMPILE_FLAGS "-std=c89")

add_library(s7 STATIC
    s7/mus-config.h
    s7/s7.c
    s7/s7.h
    )

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
    add_subdirectory(SDL2-2.0.12)
endif()
