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
    assimp/include/
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

# assimp
if(NOT(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Android"))
    add_subdirectory(assimp)
endif()

if (COMPILE_SDL_FROM_SOURCE)
    include_directories(
        SDL2-2.0.9/src
        SDL2-2.0.9/src/loadso
        SDL2-2.0.9/src/loadso/dummy
        SDL2-2.0.9/src/loadso/windows
        SDL2-2.0.9/src/loadso/dlopen
        SDL2-2.0.9/src/main
        SDL2-2.0.9/src/main/dummy
        SDL2-2.0.9/src/main/haiku
        SDL2-2.0.9/src/main/android
        SDL2-2.0.9/src/main/winrt
        SDL2-2.0.9/src/main/nacl
        SDL2-2.0.9/src/main/psp
        SDL2-2.0.9/src/main/windows
        SDL2-2.0.9/src/hidapi
        SDL2-2.0.9/src/hidapi/hidapi
        SDL2-2.0.9/src/hidapi/pc
        SDL2-2.0.9/src/hidapi/libusb
        SDL2-2.0.9/src/hidapi/android
        SDL2-2.0.9/src/hidapi/android/jni
        SDL2-2.0.9/src/hidapi/ios
        SDL2-2.0.9/src/hidapi/linux
        SDL2-2.0.9/src/hidapi/mac
        SDL2-2.0.9/src/hidapi/testgui
        SDL2-2.0.9/src/hidapi/testgui/TestGUI.app.in
        SDL2-2.0.9/src/hidapi/testgui/TestGUI.app.in/Contents
        SDL2-2.0.9/src/hidapi/testgui/TestGUI.app.in/Contents/Resources
        SDL2-2.0.9/src/hidapi/testgui/TestGUI.app.in/Contents/Resources/English.lproj
        SDL2-2.0.9/src/hidapi/windows
        SDL2-2.0.9/src/hidapi/windows/ddk_build
        SDL2-2.0.9/src/hidapi/hidtest
        SDL2-2.0.9/src/hidapi/udev
        SDL2-2.0.9/src/hidapi/doxygen
        SDL2-2.0.9/src/hidapi/m4
        SDL2-2.0.9/src/audio
        SDL2-2.0.9/src/audio/dummy
        SDL2-2.0.9/src/audio/haiku
        SDL2-2.0.9/src/audio/directsound
        SDL2-2.0.9/src/audio/arts
        SDL2-2.0.9/src/audio/winmm
        SDL2-2.0.9/src/audio/emscripten
        SDL2-2.0.9/src/audio/android
        SDL2-2.0.9/src/audio/dsp
        SDL2-2.0.9/src/audio/coreaudio
        SDL2-2.0.9/src/audio/nacl
        SDL2-2.0.9/src/audio/wasapi
        SDL2-2.0.9/src/audio/pulseaudio
        SDL2-2.0.9/src/audio/sun
        SDL2-2.0.9/src/audio/jack
        SDL2-2.0.9/src/audio/fusionsound
        SDL2-2.0.9/src/audio/psp
        SDL2-2.0.9/src/audio/disk
        SDL2-2.0.9/src/audio/paudio
        SDL2-2.0.9/src/audio/nas
        SDL2-2.0.9/src/audio/sndio
        SDL2-2.0.9/src/audio/netbsd
        SDL2-2.0.9/src/audio/esd
        SDL2-2.0.9/src/audio/alsa
        SDL2-2.0.9/src/audio/qsa
        SDL2-2.0.9/src/stdlib
        SDL2-2.0.9/src/atomic
        SDL2-2.0.9/src/render
        SDL2-2.0.9/src/render/metal
        SDL2-2.0.9/src/render/psp
        SDL2-2.0.9/src/render/opengles2
        SDL2-2.0.9/src/render/direct3d
        SDL2-2.0.9/src/render/direct3d11
        SDL2-2.0.9/src/render/opengles
        SDL2-2.0.9/src/render/opengl
        SDL2-2.0.9/src/render/software
        SDL2-2.0.9/src/timer
        SDL2-2.0.9/src/timer/dummy
        SDL2-2.0.9/src/timer/haiku
        SDL2-2.0.9/src/timer/psp
        SDL2-2.0.9/src/timer/windows
        SDL2-2.0.9/src/timer/unix
        SDL2-2.0.9/src/joystick
        SDL2-2.0.9/src/joystick/bsd
        SDL2-2.0.9/src/joystick/dummy
        SDL2-2.0.9/src/joystick/haiku
        SDL2-2.0.9/src/joystick/hidapi
        SDL2-2.0.9/src/joystick/emscripten
        SDL2-2.0.9/src/joystick/android
        SDL2-2.0.9/src/joystick/linux
        SDL2-2.0.9/src/joystick/darwin
        SDL2-2.0.9/src/joystick/iphoneos
        SDL2-2.0.9/src/joystick/psp
        SDL2-2.0.9/src/joystick/windows
        SDL2-2.0.9/src/joystick/steam
        SDL2-2.0.9/src/power
        SDL2-2.0.9/src/power/haiku
        SDL2-2.0.9/src/power/emscripten
        SDL2-2.0.9/src/power/android
        SDL2-2.0.9/src/power/winrt
        SDL2-2.0.9/src/power/uikit
        SDL2-2.0.9/src/power/linux
        SDL2-2.0.9/src/power/psp
        SDL2-2.0.9/src/power/windows
        SDL2-2.0.9/src/power/macosx
        SDL2-2.0.9/src/sensor
        SDL2-2.0.9/src/sensor/dummy
        SDL2-2.0.9/src/sensor/coremotion
        SDL2-2.0.9/src/sensor/android
        SDL2-2.0.9/src/dynapi
        SDL2-2.0.9/src/haptic
        SDL2-2.0.9/src/haptic/dummy
        SDL2-2.0.9/src/haptic/android
        SDL2-2.0.9/src/haptic/linux
        SDL2-2.0.9/src/haptic/darwin
        SDL2-2.0.9/src/haptic/windows
        SDL2-2.0.9/src/test
        SDL2-2.0.9/src/cpuinfo
        SDL2-2.0.9/src/thread
        SDL2-2.0.9/src/thread/generic
        SDL2-2.0.9/src/thread/pthread
        SDL2-2.0.9/src/thread/psp
        SDL2-2.0.9/src/thread/windows
        SDL2-2.0.9/src/thread/stdcpp
        SDL2-2.0.9/src/file
        SDL2-2.0.9/src/file/cocoa
        SDL2-2.0.9/src/libm
        SDL2-2.0.9/src/core
        SDL2-2.0.9/src/core/android
        SDL2-2.0.9/src/core/winrt
        SDL2-2.0.9/src/core/linux
        SDL2-2.0.9/src/core/windows
        SDL2-2.0.9/src/core/unix
        SDL2-2.0.9/src/filesystem
        SDL2-2.0.9/src/filesystem/cocoa
        SDL2-2.0.9/src/filesystem/dummy
        SDL2-2.0.9/src/filesystem/haiku
        SDL2-2.0.9/src/filesystem/emscripten
        SDL2-2.0.9/src/filesystem/android
        SDL2-2.0.9/src/filesystem/winrt
        SDL2-2.0.9/src/filesystem/nacl
        SDL2-2.0.9/src/filesystem/windows
        SDL2-2.0.9/src/filesystem/unix
        SDL2-2.0.9/src/video
        SDL2-2.0.9/src/video/cocoa
        SDL2-2.0.9/src/video/dummy
        SDL2-2.0.9/src/video/haiku
        SDL2-2.0.9/src/video/kmsdrm
        SDL2-2.0.9/src/video/emscripten
        SDL2-2.0.9/src/video/yuv2rgb
        SDL2-2.0.9/src/video/android
        SDL2-2.0.9/src/video/winrt
        SDL2-2.0.9/src/video/uikit
        SDL2-2.0.9/src/video/nacl
        SDL2-2.0.9/src/video/wayland
        SDL2-2.0.9/src/video/vivante
        SDL2-2.0.9/src/video/x11
        SDL2-2.0.9/src/video/psp
        SDL2-2.0.9/src/video/qnx
        SDL2-2.0.9/src/video/directfb
        SDL2-2.0.9/src/video/windows
        SDL2-2.0.9/src/video/raspberry
        SDL2-2.0.9/src/video/pandora
        SDL2-2.0.9/src/video/mir
        SDL2-2.0.9/src/video/khronos
        SDL2-2.0.9/src/video/khronos/GLES2
        SDL2-2.0.9/src/video/khronos/vulkan
        SDL2-2.0.9/src/video/khronos/KHR
        SDL2-2.0.9/src/video/khronos/EGL
        SDL2-2.0.9/src/events
        )
endif()

# SFML
if (COMPILE_SFML_FROM_SOURCE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        include_directories(
            SFML-2.4.2/include/
            SFML-2.4.2/src/
            SFML-2.4.2/extlibs/headers/
            SFML-2.4.2/extlibs/headers/AL/
            )
    else()
        include_directories(
            SFML-2.4.2/include/
            SFML-2.4.2/src/
            )
    endif()
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

# sfml-system
if(COMPILE_SFML_FROM_SOURCE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_library(sfml-system STATIC
            SFML-2.4.2/src/SFML/System/Clock.cpp
            SFML-2.4.2/src/SFML/System/Err.cpp
            SFML-2.4.2/src/SFML/System/FileInputStream.cpp
            SFML-2.4.2/src/SFML/System/Lock.cpp
            SFML-2.4.2/src/SFML/System/MemoryInputStream.cpp
            SFML-2.4.2/src/SFML/System/Mutex.cpp
            SFML-2.4.2/src/SFML/System/Sleep.cpp
            SFML-2.4.2/src/SFML/System/String.cpp
            SFML-2.4.2/src/SFML/System/Thread.cpp
            SFML-2.4.2/src/SFML/System/ThreadLocal.cpp
            SFML-2.4.2/src/SFML/System/Time.cpp
            SFML-2.4.2/src/SFML/System/Unix/ClockImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/MutexImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/SleepImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/ThreadImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/ThreadLocalImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/ClockImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/MutexImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/SleepImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/ThreadImpl.cpp
            SFML-2.4.2/src/SFML/System/Unix/ThreadLocalImpl.cpp
            )
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
        add_library(sfml-system STATIC
            SFML-2.4.2/src/SFML/System/Clock.cpp
            SFML-2.4.2/src/SFML/System/Err.cpp
            SFML-2.4.2/src/SFML/System/FileInputStream.cpp
            SFML-2.4.2/src/SFML/System/Lock.cpp
            SFML-2.4.2/src/SFML/System/MemoryInputStream.cpp
            SFML-2.4.2/src/SFML/System/Mutex.cpp
            SFML-2.4.2/src/SFML/System/Sleep.cpp
            SFML-2.4.2/src/SFML/System/String.cpp
            SFML-2.4.2/src/SFML/System/Thread.cpp
            SFML-2.4.2/src/SFML/System/ThreadLocal.cpp
            SFML-2.4.2/src/SFML/System/Time.cpp
            SFML-2.4.2/src/SFML/System/Android/Activity.cpp
            SFML-2.4.2/src/SFML/System/Android/Activity.hpp
            SFML-2.4.2/src/SFML/System/Android/NativeActivity.cpp
            SFML-2.4.2/src/SFML/System/Android/ResourceStream.cpp
            SFML-2.4.2/src/SFML/System/Android/ResourceStream.hpp
            )
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        add_library(sfml-system STATIC
            SFML-2.4.2/src/SFML/System/Clock.cpp
            SFML-2.4.2/src/SFML/System/Err.cpp
            SFML-2.4.2/src/SFML/System/FileInputStream.cpp
            SFML-2.4.2/src/SFML/System/Lock.cpp
            SFML-2.4.2/src/SFML/System/MemoryInputStream.cpp
            SFML-2.4.2/src/SFML/System/Mutex.cpp
            SFML-2.4.2/src/SFML/System/Sleep.cpp
            SFML-2.4.2/src/SFML/System/String.cpp
            SFML-2.4.2/src/SFML/System/Thread.cpp
            SFML-2.4.2/src/SFML/System/ThreadLocal.cpp
            SFML-2.4.2/src/SFML/System/Time.cpp
            SFML-2.4.2/src/SFML/System/Win32/ClockImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/MutexImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/SleepImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/ThreadImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/ThreadLocalImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/ClockImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/MutexImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/SleepImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/ThreadImpl.cpp
            SFML-2.4.2/src/SFML/System/Win32/ThreadLocalImpl.cpp
            )
        set_property(TARGET sfml-system PROPERTY COMPILE_FLAGS "-DSFML_STATIC -DSFML_STATIC_LIBRARIES -DSFML_USE_STATIC_STD_LIBS")
    endif()

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        add_library(sfml-audio STATIC
            SFML-2.4.2/src/SFML/Audio/ALCheck.cpp
            SFML-2.4.2/src/SFML/Audio/AlResource.cpp
            SFML-2.4.2/src/SFML/Audio/AudioDevice.cpp
            SFML-2.4.2/src/SFML/Audio/InputSoundFile.cpp
            SFML-2.4.2/src/SFML/Audio/Listener.cpp
            SFML-2.4.2/src/SFML/Audio/Music.cpp
            SFML-2.4.2/src/SFML/Audio/OutputSoundFile.cpp
            SFML-2.4.2/src/SFML/Audio/Sound.cpp
            SFML-2.4.2/src/SFML/Audio/SoundBuffer.cpp
            SFML-2.4.2/src/SFML/Audio/SoundBufferRecorder.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileFactory.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileReaderFlac.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileReaderOgg.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileReaderWav.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileWriterFlac.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileWriterOgg.cpp
            SFML-2.4.2/src/SFML/Audio/SoundFileWriterWav.cpp
            SFML-2.4.2/src/SFML/Audio/SoundRecorder.cpp
            SFML-2.4.2/src/SFML/Audio/SoundSource.cpp
            SFML-2.4.2/src/SFML/Audio/SoundStream.cpp
            SFML-2.4.2/src/SFML/Audio/ALCheck.hpp
            SFML-2.4.2/src/SFML/Audio/AudioDevice.hpp
            SFML-2.4.2/src/SFML/Audio/CMakeLists.txt
            SFML-2.4.2/src/SFML/Audio/SoundFileReaderFlac.hpp
            SFML-2.4.2/src/SFML/Audio/SoundFileReaderOgg.hpp
            SFML-2.4.2/src/SFML/Audio/SoundFileReaderWav.hpp
            SFML-2.4.2/src/SFML/Audio/SoundFileWriterFlac.hpp
            SFML-2.4.2/src/SFML/Audio/SoundFileWriterOgg.hpp
            SFML-2.4.2/src/SFML/Audio/SoundFileWriterWav.hpp
            # SFML-2.4.2/extlibs/headers/AL/al.h
            # SFML-2.4.2/extlibs/headers/FLAC/assert.h
            )
        add_dependencies(sfml-audio sfml-system)
    endif()

    if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(sfml-audio
            sfml-system
            pthread
            ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-mingw/x64/libFLAC.a
            ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-mingw/x64/libopenal32.a
            ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-mingw/x64/libvorbisfile.a
            ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-mingw/x64/libvorbis.a
            ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-mingw/x64/libogg.a
            ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-mingw/x64/libvorbisenc.a
            )
        set_property(TARGET sfml-audio PROPERTY COMPILE_FLAGS "-DSFML_STATIC -DSFML_STATIC_LIBRARIES -DSFML_USE_STATIC_STD_LIBS")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if(SFML_COMPILER_MSVC AND SFML_MSVC_VERSION LESS 14)
            target_link_libraries(sfml-audio
                sfml-system
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/flac.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/freetype.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/jpeg.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/ogg.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/openal32.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/vorbis.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/vorbisenc.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc/x64/vorbisfile.lib
                )
        elseif(SFML_COMPILER_MSVC)
            target_link_libraries(sfml-audio
                sfml-system
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/flac.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/freetype.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/jpeg.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/ogg.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/openal32.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/vorbis.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/vorbisenc.lib
                ${CMAKE_SOURCE_DIR}/external/SFML-2.4.2/extlibs/libs-msvc-universal/x64/vorbisfile.lib
                )
        endif()
        set_property(TARGET sfml-audio PROPERTY COMPILE_FLAGS "-DSFML_STATIC -DSFML_STATIC_LIBRARIES -DSFML_USE_STATIC_STD_LIBS")
    endif()
endif()

if(COMPILE_SDL_FROM_SOURCE)
    add_subdirectory(SDL2-2.0.9)
endif()
