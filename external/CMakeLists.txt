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

# pugixml
add_subdirectory(pugixml)

# FastNoiseSIMD
add_subdirectory(FastNoiseSIMD)

### GLFW ###

add_subdirectory(glfw-3.2)

# TinySceme #
if(ENABLE_SCRIPTING_WITH_TINYSCHEME)
    add_subdirectory(tinyscheme-1.41)
endif()

# Assimp #
if(ENABLE_ASSET_IMPORTING_WITH_ASSIMP)
    add_subdirectory(assimp)
endif()

include_directories(
    glfw-3.2/include/GLFW/
    glew-2.0.0/include/
    FastNoiseSIMD/
    tinyscheme-1.41/

    gdal-2.1.1/
    gdal-2.1.1/alg/
    gdal-2.1.1/apps/
    gdal-2.1.1/apps/
    gdal-2.1.1/frmts/
    gdal-2.1.1/frmts/aaigrid/
    gdal-2.1.1/frmts/adrg/
    gdal-2.1.1/frmts/aigrid/
    gdal-2.1.1/frmts/airsar/
    gdal-2.1.1/frmts/arg/
    gdal-2.1.1/frmts/blx/
    gdal-2.1.1/frmts/bmp/
    gdal-2.1.1/frmts/bsb/
    gdal-2.1.1/frmts/cals/
    gdal-2.1.1/frmts/ceos/
    gdal-2.1.1/frmts/ceos2/
    gdal-2.1.1/frmts/coasp/
    gdal-2.1.1/frmts/cosar/
    gdal-2.1.1/frmts/ctg/
    gdal-2.1.1/frmts/dimap/
    gdal-2.1.1/frmts/dted/
    gdal-2.1.1/frmts/e00grid/
    gdal-2.1.1/frmts/elas/
    gdal-2.1.1/frmts/envisat/
    gdal-2.1.1/frmts/ers/
    gdal-2.1.1/frmts/fit/
    gdal-2.1.1/frmts/gff/
    gdal-2.1.1/frmts/gif/
    gdal-2.1.1/frmts/grib/
    gdal-2.1.1/frmts/gsg/
    gdal-2.1.1/frmts/gtiff/
    gdal-2.1.1/frmts/gtiff/libgeotiff/
    gdal-2.1.1/frmts/gtiff/libtiff/
    gdal-2.1.1/frmts/gxf/
    gdal-2.1.1/frmts/hf2/
    gdal-2.1.1/frmts/hfa/
    gdal-2.1.1/frmts/idrisi/
    gdal-2.1.1/frmts/ilwis/
    gdal-2.1.1/frmts/ingr/
    gdal-2.1.1/frmts/iris/
    gdal-2.1.1/frmts/iso8211/
    gdal-2.1.1/frmts/jaxapalsar/
    gdal-2.1.1/frmts/jdem/
    gdal-2.1.1/frmts/jpeg/
    gdal-2.1.1/frmts/jpeg/
    gdal-2.1.1/frmts/jpeg/
    gdal-2.1.1/frmts/kmlsuperoverlay/
    gdal-2.1.1/frmts/l1b/
    gdal-2.1.1/frmts/leveller/
    gdal-2.1.1/frmts/map/
    gdal-2.1.1/frmts/mem/
    gdal-2.1.1/frmts/mrf/
    gdal-2.1.1/frmts/mrf/libLERC/
    gdal-2.1.1/frmts/msgn/
    gdal-2.1.1/frmts/ngsgeoid/
    gdal-2.1.1/frmts/nitf/
    gdal-2.1.1/frmts/northwood/
    gdal-2.1.1/frmts/ozi/
    gdal-2.1.1/frmts/pcidsk/
    gdal-2.1.1/frmts/pcraster/
    gdal-2.1.1/frmts/pdf/
    gdal-2.1.1/frmts/pds/
    gdal-2.1.1/frmts/png/
    gdal-2.1.1/frmts/r/
    gdal-2.1.1/frmts/raw/
    gdal-2.1.1/frmts/rik/
    gdal-2.1.1/frmts/rmf/
    gdal-2.1.1/frmts/rs2/
    gdal-2.1.1/frmts/safe/
    gdal-2.1.1/frmts/saga/
    gdal-2.1.1/frmts/sdts/
    gdal-2.1.1/frmts/sentinel2/
    gdal-2.1.1/frmts/sgi/
    gdal-2.1.1/frmts/srtmhgt/
    gdal-2.1.1/frmts/terragen/
    gdal-2.1.1/frmts/til/
    gdal-2.1.1/frmts/tsx/
    gdal-2.1.1/frmts/usgsdem/
    gdal-2.1.1/frmts/vrt/
    gdal-2.1.1/frmts/xpm/
    gdal-2.1.1/frmts/xyz/
    gdal-2.1.1/frmts/zlib/
    gdal-2.1.1/frmts/zmap/
    gdal-2.1.1/gcore/
    gdal-2.1.1/gcore/mdreader/
    gdal-2.1.1/ogr/
    gdal-2.1.1/ogr/ogrsf_frmts/
    gdal-2.1.1/ogr/ogrsf_frmts/aeronavfaa/
    gdal-2.1.1/ogr/ogrsf_frmts/arcgen/
    gdal-2.1.1/ogr/ogrsf_frmts/avc/
    gdal-2.1.1/ogr/ogrsf_frmts/bna/
    gdal-2.1.1/ogr/ogrsf_frmts/csv/
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/
    gdal-2.1.1/ogr/ogrsf_frmts/edigeo/
    gdal-2.1.1/ogr/ogrsf_frmts/generic/
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/
    gdal-2.1.1/ogr/ogrsf_frmts/georss/
    gdal-2.1.1/ogr/ogrsf_frmts/gml/
    gdal-2.1.1/ogr/ogrsf_frmts/gmt/
    gdal-2.1.1/ogr/ogrsf_frmts/gpsbabel/
    gdal-2.1.1/ogr/ogrsf_frmts/gpx/
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/
    gdal-2.1.1/ogr/ogrsf_frmts/htf/
    gdal-2.1.1/ogr/ogrsf_frmts/idrisi/
    gdal-2.1.1/ogr/ogrsf_frmts/jml/
    gdal-2.1.1/ogr/ogrsf_frmts/kml/
    gdal-2.1.1/ogr/ogrsf_frmts/mem/
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/
    gdal-2.1.1/ogr/ogrsf_frmts/openair/
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/
    gdal-2.1.1/ogr/ogrsf_frmts/pds/
    gdal-2.1.1/ogr/ogrsf_frmts/pgdump/
    gdal-2.1.1/ogr/ogrsf_frmts/rec/
    gdal-2.1.1/ogr/ogrsf_frmts/s57/
    gdal-2.1.1/ogr/ogrsf_frmts/sdts/
    gdal-2.1.1/ogr/ogrsf_frmts/segukooa/
    gdal-2.1.1/ogr/ogrsf_frmts/segy/
    gdal-2.1.1/ogr/ogrsf_frmts/selafin/
    gdal-2.1.1/ogr/ogrsf_frmts/shape/
    gdal-2.1.1/ogr/ogrsf_frmts/sua/
    gdal-2.1.1/ogr/ogrsf_frmts/svg/
    gdal-2.1.1/ogr/ogrsf_frmts/sxf/
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/
    gdal-2.1.1/ogr/ogrsf_frmts/vdv/
    gdal-2.1.1/ogr/ogrsf_frmts/vrt/
    gdal-2.1.1/ogr/ogrsf_frmts/wasp/
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/
    gdal-2.1.1/port/

    # manually added due to builds failed due to missing files.
    gdal-2.1.1/frmts/jpeg/libjpeg/
    gdal-2.1.1/frmts/png/libpng/
    gdal-2.1.1/frmts/gif/giflib/
    gdal-2.1.1/frmts/pcraster/libcsf/
    gdal-2.1.1/frmts/pcidsk/sdk/
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

add_library(tinyscheme
    tinyscheme-1.41/dynload.c
    tinyscheme-1.41/dynload.h
    tinyscheme-1.41/opdefines.h
    tinyscheme-1.41/scheme.c
    tinyscheme-1.41/scheme.h
    tinyscheme-1.41/scheme-private.h
    )
set_property(TARGET tinyscheme PROPERTY COMPILE_FLAGS "-DSTANDALONE=0 -DUSE_INTERFACE=1")

# GDAL/OGR 2.1.1

### ANTTWEAKBAR ###
# 
# set(ANTTWEAKBAR_SOURCE
# 	AntTweakBar-1.16/src/LoadOGL.cpp
# 	AntTweakBar-1.16/src/LoadOGLCore.cpp
# 	AntTweakBar-1.16/src/TwColors.cpp
# 	AntTweakBar-1.16/src/TwBar.cpp
# 	AntTweakBar-1.16/src/TwEventGLFW.c
# 	AntTweakBar-1.16/src/TwFonts.cpp
# 	AntTweakBar-1.16/src/TwMgr.cpp
# 	AntTweakBar-1.16/src/TwOpenGL.cpp
# 	AntTweakBar-1.16/src/TwOpenGLCore.cpp
# 	AntTweakBar-1.16/src/TwPrecomp.cpp
# )
# 
# if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # If on Xcode, rename files to .mm
# file(COPY ${ANTTWEAKBAR_SOURCE} DESTINATION AntTweakBar-ObjectiveC/)
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGL.cpp      ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGL.mm     )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGLCore.cpp  ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGLCore.mm )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwColors.cpp     ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwColors.mm    )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwBar.cpp        ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwBar.mm       )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwEventGLFW.c    ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwEventGLFW.m  )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwFonts.cpp      ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwFonts.mm     )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwMgr.cpp        ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwMgr.mm       )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGL.cpp     ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGL.mm    )
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGLCore.cpp ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGLCore.mm)
# file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwPrecomp.cpp    ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwPrecomp.mm   )
# 
# set(ANTTWEAKBAR_SOURCE
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGL.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGLCore.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwColors.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwBar.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwEventGLFW.m
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwFonts.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwMgr.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGL.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGLCore.mm
# 	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwPrecomp.mm
# )
# include_directories(
# 	${CMAKE_SOURCE_DIR}/external/AntTweakBar-1.16/src/
# )
# add_definitions(
# 	-D_MACOSX
# )
# elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# add_definitions(
# 	-D_UNIX
# )
# elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
# add_definitions(
# 	-D_WINDOWS
# )
# 
# endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
# 
# set(ANTTWEAKBAR_HEADERS
# 	AntTweakBar-1.16/src/AntPerfTimer.h
# 	AntTweakBar-1.16/src/LoadOGL.h
# 	AntTweakBar-1.16/src/LoadOGLCore.h
# 	AntTweakBar-1.16/src/MiniGLFW.h
# 	AntTweakBar-1.16/src/resource.h
# 	AntTweakBar-1.16/src/TwBar.h
# 	AntTweakBar-1.16/src/TwColors.h
# 	AntTweakBar-1.16/src/TwFonts.h
# 	AntTweakBar-1.16/src/TwGraph.h
# 	AntTweakBar-1.16/src/TwMgr.h
# 	AntTweakBar-1.16/src/TwOpenGL.h
# 	AntTweakBar-1.16/src/TwOpenGLCore.h
# 	AntTweakBar-1.16/src/TwPrecomp.h
# )
# 
# include_directories(
# 	AntTweakBar-1.16/include/
# )
# 
# add_library( ANTTWEAKBAR_116_OGLCORE_GLFW STATIC
# 	${ANTTWEAKBAR_SOURCE}
# 	${ANTTWEAKBAR_HEADERS}
# )
# 
# target_link_libraries(ANTTWEAKBAR_116_OGLCORE_GLFW
# 	${OPENGL_LIBRARY}
# 	${EXTRA_LIBS}
# )

### ASSIMP ###
# AssImp already has a CMakeLists.txt so let's use these
# 
# # Compile built-in, modified version of Zlib
# include(CheckIncludeFile)
# include(CheckTypeSize)
# include(CheckFunctionExists)
# add_subdirectory( assimp-3.0.1270/contrib/zlib )
# 
# # Compile without Boost
# include_directories( assimp-3.0.1270/code/BoostWorkaround )
# add_definitions( -DASSIMP_BUILD_BOOST_WORKAROUND )
# 
# # Compile AssImp
# set( LIB_INSTALL_DIR "lib")
# set(LIBASSIMP_COMPONENT libassimp3.0-r1270-OGLtuts)
# set(ZLIB_LIBRARIES zlib)
# set(BUILD_STATIC_LIB ON)
# #set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib)
# add_subdirectory( assimp-3.0.1270/code )

### BULLET ###
# Bullet already has a CMakeLists.txt so let's use these
# 
# set(BULLET_VERSION 2.81)
# include_directories(
# 	bullet-2.81-rev2613/src
# )
# add_subdirectory( bullet-2.81-rev2613/src/BulletSoftBody)
# add_subdirectory( bullet-2.81-rev2613/src/BulletCollision)
# add_subdirectory( bullet-2.81-rev2613/src/BulletDynamics)
# add_subdirectory( bullet-2.81-rev2613/src/LinearMath)
