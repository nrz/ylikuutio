add_definitions(
    -DGLEW_STATIC
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -D_CRT_SECURE_NO_WARNINGS
    )

include_directories(
    # asio/asio/include/
    FastNoiseSIMD/
    glew-2.0.0/include/
    glm/
    OpenFBX/src/
    pugixml/src/
    soloud/include/
    zlib/
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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND NOT CMAKE_CROSSCOMPILING)
    # https://github.com/carla-simulator/carla/issues/6976
    set(ZLIB_INCLUDE_DIR "zlib")
    set(ZLIB_LIBRARY "zlib")
    set(ZLIB_FOUND TRUE)
    set(ZLIB_VERSION 1.3.1)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND NOT CMAKE_CROSSCOMPILING)
    # https://stackoverflow.com/questions/6874883/cmake-hierarchy-zlib-libpng-and-my-own-app
    set(PNG_BUILD_ZLIB ON CACHE BOOL "" FORCE)
    add_subdirectory(libpng-1.6.37)
    target_include_directories(png PUBLIC zlib/ ${CMAKE_CURRENT_BINARY_DIR}/zlib/)
    target_include_directories(png PUBLIC libpng-1.6.37/ ${CMAKE_CURRENT_BINARY_DIR}/libpng-1.6.37/)
elseif(COMPILE_LIBPNG_FROM_SOURCE)
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

if (COMPILE_SDL_FROM_SOURCE)
	add_library(soloud STATIC
		soloud/include/soloud_file_hack_off.h
		soloud/include/soloud_file.h
		soloud/include/soloud_audiosource.h
		soloud/include/soloud_misc.h
		soloud/include/soloud_tedsid.h
		soloud/include/soloud_fft.h
		soloud/include/soloud_lofifilter.h
		soloud/include/soloud_bassboostfilter.h
		soloud/include/soloud_wav.h
		soloud/include/soloud_c.h
		soloud/include/soloud_internal.h
		soloud/include/soloud_biquadresonantfilter.h
		soloud/include/soloud_fftfilter.h
		soloud/include/zx7decompress.h
		soloud/include/soloud_queue.h
		soloud/include/soloud_sfxr.h
		soloud/include/soloud_speech.h
		soloud/include/soloud_duckfilter.h
		soloud/include/soloud_vizsn.h
		soloud/include/soloud_file_hack_on.h
		soloud/include/soloud_error.h
		soloud/include/soloud_robotizefilter.h
		soloud/include/soloud_noise.h
		soloud/include/soloud_flangerfilter.h
		soloud/include/soloud_filter.h
		soloud/include/soloud_thread.h
		soloud/include/soloud_bus.h
		soloud/include/soloud_echofilter.h
		soloud/include/soloud_eqfilter.h
		soloud/include/soloud_waveshaperfilter.h
		soloud/include/soloud_openmpt.h
		soloud/include/soloud_ay.h
		soloud/include/soloud_fader.h
		soloud/include/soloud_wavstream.h
		soloud/include/soloud_monotone.h
		soloud/include/soloud_dcremovalfilter.h
		soloud/include/soloud_freeverbfilter.h
		soloud/include/soloud_vic.h
		soloud/include/soloud.h
		soloud/src/audiosource/vizsn/soloud_vizsn.cpp
		soloud/src/audiosource/ay/sndchip.h
		soloud/src/audiosource/ay/chipplayer.h
		soloud/src/audiosource/ay/sndbuffer.h
		soloud/src/audiosource/ay/sndrender.cpp
		soloud/src/audiosource/ay/sndbuffer.cpp
		soloud/src/audiosource/ay/sndchip.cpp
		soloud/src/audiosource/ay/chipplayer.cpp
		soloud/src/audiosource/ay/sndrender.h
		soloud/src/audiosource/ay/soloud_ay.cpp
		soloud/src/audiosource/monotone/soloud_monotone.cpp
		soloud/src/audiosource/speech/klatt.cpp
		soloud/src/audiosource/speech/resonator.h
		soloud/src/audiosource/speech/darray.cpp
		soloud/src/audiosource/speech/resonator.cpp
		soloud/src/audiosource/speech/tts.h
		soloud/src/audiosource/speech/soloud_speech.cpp
		soloud/src/audiosource/speech/klatt.h
		soloud/src/audiosource/speech/tts.cpp
		soloud/src/audiosource/speech/darray.h
		soloud/src/audiosource/wav/dr_wav.h
		soloud/src/audiosource/wav/soloud_wavstream.cpp
		soloud/src/audiosource/wav/stb_vorbis.h
		soloud/src/audiosource/wav/stb_vorbis.c
		soloud/src/audiosource/wav/dr_mp3.h
		soloud/src/audiosource/wav/dr_impl.cpp
		soloud/src/audiosource/wav/soloud_wav.cpp
		soloud/src/audiosource/wav/dr_flac.h
		soloud/src/audiosource/sfxr/soloud_sfxr.cpp
		soloud/src/audiosource/openmpt/soloud_openmpt_dll.c
		soloud/src/audiosource/openmpt/soloud_openmpt.cpp
		soloud/src/audiosource/tedsid/sid.cpp
		soloud/src/audiosource/tedsid/ted.cpp
		soloud/src/audiosource/tedsid/ted.h
		soloud/src/audiosource/tedsid/sid.h
		soloud/src/audiosource/tedsid/soloud_tedsid.cpp
		soloud/src/audiosource/noise/soloud_noise.cpp
		soloud/src/audiosource/vic/soloud_vic.cpp
		soloud/src/filter/soloud_freeverbfilter.cpp
		soloud/src/filter/soloud_echofilter.cpp
		soloud/src/filter/soloud_fftfilter.cpp
		soloud/src/filter/soloud_dcremovalfilter.cpp
		soloud/src/filter/soloud_biquadresonantfilter.cpp
		soloud/src/filter/soloud_duckfilter.cpp
		soloud/src/filter/soloud_flangerfilter.cpp
		soloud/src/filter/soloud_eqfilter.cpp
		soloud/src/filter/soloud_lofifilter.cpp
		soloud/src/filter/soloud_waveshaperfilter.cpp
		soloud/src/filter/soloud_bassboostfilter.cpp
		soloud/src/filter/soloud_robotizefilter.cpp
		soloud/src/backend/sdl_static/soloud_sdl_static.cpp
		soloud/src/backend/coreaudio/soloud_coreaudio.cpp
		soloud/src/backend/null/soloud_null.cpp
		soloud/src/backend/opensles/soloud_opensles.cpp
		soloud/src/backend/wasapi/soloud_wasapi.cpp
		soloud/src/backend/miniaudio/soloud_miniaudio.cpp
		soloud/src/backend/miniaudio/miniaudio.h
		soloud/src/backend/winmm/soloud_winmm.cpp
		soloud/src/backend/alsa/soloud_alsa.cpp
		soloud/src/backend/xaudio2/soloud_xaudio2.cpp
		soloud/src/backend/sdl/soloud_sdl2_dll.c
		soloud/src/backend/sdl/soloud_sdl2.cpp
		soloud/src/backend/sdl/soloud_sdl1.cpp
		soloud/src/backend/sdl/soloud_sdl1_dll.c
		soloud/src/backend/sdl2_static/soloud_sdl2_static.cpp
		soloud/src/backend/portaudio/soloud_portaudio.cpp
		soloud/src/backend/portaudio/soloud_portaudio_dll.c
		soloud/src/backend/oss/soloud_oss.cpp
		soloud/src/backend/nosound/soloud_nosound.cpp
		soloud/src/backend/jack/soloud_jack.cpp
		soloud/src/backend/openal/soloud_openal.cpp
		soloud/src/backend/openal/soloud_openal_dll.c
		soloud/src/core/soloud_core_basicops.cpp
		soloud/src/core/soloud_fader.cpp
		soloud/src/core/soloud_filter.cpp
		soloud/src/core/soloud_core_voicegroup.cpp
		soloud/src/core/soloud_core_voiceops.cpp
		soloud/src/core/soloud_fft.cpp
		soloud/src/core/soloud_file.cpp
		soloud/src/core/soloud_audiosource.cpp
		soloud/src/core/soloud_core_faderops.cpp
		soloud/src/core/soloud_bus.cpp
		soloud/src/core/soloud_misc.cpp
		soloud/src/core/soloud_thread.cpp
		soloud/src/core/soloud_fft_lut.cpp
		soloud/src/core/soloud.cpp
		soloud/src/core/soloud_core_filterops.cpp
		soloud/src/core/soloud_core_setters.cpp
		soloud/src/core/soloud_queue.cpp
		soloud/src/core/soloud_core_getters.cpp
		soloud/src/core/soloud_core_3d.cpp
		soloud/src/c_api/soloud_c.cpp
	)
	target_link_libraries(soloud SDL2-static)
	set_property(TARGET soloud PROPERTY CMAKE_POSITION_INDEPENDENT_CODE ON)
	set_property(TARGET soloud PROPERTY COMPILE_FLAGS "-DWITH_SDL2_STATIC")
    set_target_properties(soloud PROPERTIES
        C_STANDARD 99)
else()
	add_subdirectory(soloud/contrib)
endif()
