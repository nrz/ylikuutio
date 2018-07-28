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

# SFML
if (COMPILE_SFML_FROM_SOURCE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        include_directories(
            # asio/asio/include/
            FastNoiseSIMD/
            glew-2.0.0/include/
            glfw/include/
            glm/
            OpenFBX/src/
            pugixml/src/
            SFML-2.4.2/include/
            SFML-2.4.2/src/
            SFML-2.4.2/extlibs/headers/
            SFML-2.4.2/extlibs/headers/AL/
            .
            )
    else()
        include_directories(
            # asio/asio/include/
            FastNoiseSIMD/
            glew-2.0.0/include/
            glfw/include/
            glm/
            OpenFBX/src/
            pugixml/src/
            SFML-2.4.2/include/
            SFML-2.4.2/src/
            .
            )
    endif()
else()
    include_directories(
        # asio/asio/include/
        FastNoiseSIMD/
        glew-2.0.0/include/
        glfw/include/
        glm/
        OpenFBX/src/
        pugixml/src/
        .
        )
endif()

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
# add_subdirectory(asio)

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
