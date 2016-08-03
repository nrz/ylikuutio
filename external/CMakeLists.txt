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

### GLFW ###

add_subdirectory (glfw-3.2)

include_directories(
    glfw-3.2/include/GLFW/
    glew-2.0.0/include/
    )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        -lGL -lGLU -lXrandr -lXext -lX11 -lrt
        ${CMAKE_DL_LIBS}
        ${GLFW_LIBRARIES}
        )
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


add_library( GLEW_200 STATIC
    ${GLEW_SOURCE}
    ${GLEW_INCLUDE}
    )

target_link_libraries(GLEW_200
    ${OPENGL_LIBRARY}
    ${EXTRA_LIBS}
    )

# GDAL/OGR 2.1.1

set(GDAL_211_SOURCE
    gdal-2.1.1/port/cpl_conv.cpp
    gdal-2.1.1/port/cpl_conv.h
    gdal-2.1.1/port/cpl_error.cpp
    gdal-2.1.1/port/cpl_error.h
    gdal-2.1.1/port/cpl_string.cpp
    gdal-2.1.1/port/cpl_string.h
    gdal-2.1.1/port/cplgetsymbol.cpp
    gdal-2.1.1/port/cplstringlist.cpp
    gdal-2.1.1/port/cpl_strtod.cpp
    gdal-2.1.1/port/cpl_path.cpp
    gdal-2.1.1/port/cpl_csv.cpp
    gdal-2.1.1/port/cpl_csv.h
    gdal-2.1.1/port/cpl_findfile.cpp
    gdal-2.1.1/port/cpl_minixml.cpp
    gdal-2.1.1/port/cpl_minixml.h
    gdal-2.1.1/port/cpl_multiproc.cpp
    gdal-2.1.1/port/cpl_multiproc.h
    gdal-2.1.1/port/cpl_list.cpp
    gdal-2.1.1/port/cpl_list.h
    gdal-2.1.1/port/cpl_getexecpath.cpp
    gdal-2.1.1/port/cplstring.cpp
    gdal-2.1.1/port/cpl_vsil_win32.cpp
    gdal-2.1.1/port/cpl_vsisimple.cpp
    gdal-2.1.1/port/cpl_vsil.cpp
    gdal-2.1.1/port/cpl_vsi_mem.cpp
    gdal-2.1.1/port/cpl_vsil_unix_stdio_64.cpp
    gdal-2.1.1/port/cpl_http.cpp
    gdal-2.1.1/port/cpl_http.h
    gdal-2.1.1/port/cpl_hash_set.cpp
    gdal-2.1.1/port/cpl_hash_set.h
    gdal-2.1.1/port/cplkeywordparser.cpp
    gdal-2.1.1/port/cplkeywordparser.h
    gdal-2.1.1/port/cpl_recode.cpp
    gdal-2.1.1/port/cpl_recode_iconv.cpp
    gdal-2.1.1/port/cpl_recode_stub.cpp
    gdal-2.1.1/port/cpl_quad_tree.cpp
    gdal-2.1.1/port/cpl_quad_tree.h
    gdal-2.1.1/port/cpl_atomic_ops.cpp
    gdal-2.1.1/port/cpl_atomic_ops.h
    gdal-2.1.1/port/cpl_vsil_subfile.cpp
    gdal-2.1.1/port/cpl_time.cpp
    gdal-2.1.1/port/cpl_time.h
    gdal-2.1.1/port/cpl_vsil_stdout.cpp
    gdal-2.1.1/port/cpl_vsil_sparsefile.cpp
    gdal-2.1.1/port/cpl_vsil_abstract_archive.cpp
    gdal-2.1.1/port/cpl_vsil_tar.cpp
    gdal-2.1.1/port/cpl_vsil_stdin.cpp
    gdal-2.1.1/port/cpl_vsil_buffered_reader.cpp
    gdal-2.1.1/port/cpl_base64.cpp
    gdal-2.1.1/port/cpl_vsil_curl.cpp
    gdal-2.1.1/port/cpl_vsil_curl_streaming.cpp
    gdal-2.1.1/port/cpl_vsil_cache.cpp
    gdal-2.1.1/port/cpl_xml_validate.cpp
    gdal-2.1.1/port/cpl_spawn.cpp
    gdal-2.1.1/port/cpl_spawn.h
    gdal-2.1.1/port/cpl_google_oauth2.cpp
    gdal-2.1.1/port/cpl_progress.cpp
    gdal-2.1.1/port/cpl_progress.h
    gdal-2.1.1/port/cpl_virtualmem.cpp
    gdal-2.1.1/port/cpl_virtualmem.h
    gdal-2.1.1/port/cpl_worker_thread_pool.cpp
    gdal-2.1.1/port/cpl_worker_thread_pool.h
    gdal-2.1.1/port/cpl_vsil_crypt.cpp
    gdal-2.1.1/port/cpl_sha256.cpp
    gdal-2.1.1/port/cpl_sha256.h
    gdal-2.1.1/port/cpl_aws.cpp
    gdal-2.1.1/port/cpl_aws.h
    gdal-2.1.1/port/cpl_vsi_error.cpp
    gdal-2.1.1/port/cpl_vsi_error.h
    gdal-2.1.1/port/cpl_vsil_gzip.cpp
    gdal-2.1.1/port/cpl_minizip_ioapi.cpp
    gdal-2.1.1/port/cpl_minizip_ioapi.h
    gdal-2.1.1/port/cpl_minizip_unzip.cpp
    gdal-2.1.1/port/cpl_minizip_unzip.h
    gdal-2.1.1/port/cpl_minizip_zip.cpp
    gdal-2.1.1/port/cpl_minizip_zip.h
    gdal-2.1.1/gcore/mdreader/reader_digital_globe.cpp
    gdal-2.1.1/gcore/mdreader/reader_digital_globe.h
    gdal-2.1.1/gcore/mdreader/reader_geo_eye.cpp
    gdal-2.1.1/gcore/mdreader/reader_geo_eye.h
    gdal-2.1.1/gcore/mdreader/reader_orb_view.cpp
    gdal-2.1.1/gcore/mdreader/reader_orb_view.h
    gdal-2.1.1/gcore/mdreader/reader_pleiades.cpp
    gdal-2.1.1/gcore/mdreader/reader_pleiades.h
    gdal-2.1.1/gcore/mdreader/reader_rdk1.cpp
    gdal-2.1.1/gcore/mdreader/reader_rdk1.h
    gdal-2.1.1/gcore/mdreader/reader_landsat.cpp
    gdal-2.1.1/gcore/mdreader/reader_landsat.h
    gdal-2.1.1/gcore/mdreader/reader_spot.cpp
    gdal-2.1.1/gcore/mdreader/reader_spot.h
    gdal-2.1.1/gcore/mdreader/reader_rapid_eye.cpp
    gdal-2.1.1/gcore/mdreader/reader_rapid_eye.h
    gdal-2.1.1/gcore/mdreader/reader_alos.cpp
    gdal-2.1.1/gcore/mdreader/reader_alos.h
    gdal-2.1.1/gcore/mdreader/reader_eros.cpp
    gdal-2.1.1/gcore/mdreader/reader_eros.h
    gdal-2.1.1/gcore/mdreader/reader_kompsat.cpp
    gdal-2.1.1/gcore/mdreader/reader_kompsat.h
    gdal-2.1.1/alg/gdalmediancut.cpp
    gdal-2.1.1/alg/gdaldither.cpp
    gdal-2.1.1/alg/gdal_crs.c
    gdal-2.1.1/alg/gdaltransformer.cpp
    gdal-2.1.1/alg/gdalsimplewarp.cpp
    gdal-2.1.1/alg/gdalwarper.cpp
    gdal-2.1.1/alg/gdalwarper.h
    gdal-2.1.1/alg/gdalwarpkernel.cpp
    gdal-2.1.1/alg/gdalwarpoperation.cpp
    gdal-2.1.1/alg/gdalchecksum.cpp
    gdal-2.1.1/alg/gdal_rpc.cpp
    gdal-2.1.1/alg/gdal_tps.cpp
    gdal-2.1.1/alg/thinplatespline.cpp
    gdal-2.1.1/alg/thinplatespline.h
    gdal-2.1.1/alg/llrasterize.cpp
    gdal-2.1.1/alg/gdalrasterize.cpp
    gdal-2.1.1/alg/gdalgeoloc.cpp
    gdal-2.1.1/alg/gdalgrid.cpp
    gdal-2.1.1/alg/gdalgrid.h
    gdal-2.1.1/alg/gdalcutline.cpp
    gdal-2.1.1/alg/gdalproximity.cpp
    gdal-2.1.1/alg/rasterfill.cpp
    gdal-2.1.1/alg/gdalrasterpolygonenumerator.cpp
    gdal-2.1.1/alg/gdalsievefilter.cpp
    gdal-2.1.1/alg/gdalwarpkernel_opencl.c
    gdal-2.1.1/alg/gdalwarpkernel_opencl.h
    gdal-2.1.1/alg/polygonize.cpp
    gdal-2.1.1/alg/contour.cpp
    gdal-2.1.1/alg/gdaltransformgeolocs.cpp
    gdal-2.1.1/alg/gdal_octave.cpp
    gdal-2.1.1/alg/gdal_simplesurf.cpp
    gdal-2.1.1/alg/gdal_simplesurf.h
    gdal-2.1.1/alg/gdalmatching.cpp
    gdal-2.1.1/alg/delaunay.c
    gdal-2.1.1/alg/gdalpansharpen.cpp
    gdal-2.1.1/alg/gdalpansharpen.h
    gdal-2.1.1/alg/gdalgridavx.cpp
    gdal-2.1.1/alg/gdalgridsse.cpp
    gdal-2.1.1/frmts/gdalallregister.cpp
    gdal-2.1.1/frmts/gxf/gxfdataset.cpp
    gdal-2.1.1/frmts/gxf/gxfopen.c
    gdal-2.1.1/frmts/gxf/gxfopen.h
    gdal-2.1.1/frmts/gxf/gxf_proj4.c
    gdal-2.1.1/frmts/gxf/gxf_ogcwkt.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/xtiff.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_free.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_get.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_names.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_new.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_print.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_set.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_tiffp.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_tiffp.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_write.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_normalize.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_normalize.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geotiff_proj4.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_extra.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_trans.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_simpletags.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_simpletags.h
    gdal-2.1.1/frmts/hfa/hfaopen.cpp
    gdal-2.1.1/frmts/hfa/hfaentry.cpp
    gdal-2.1.1/frmts/hfa/hfadictionary.cpp
    gdal-2.1.1/frmts/hfa/hfafield.cpp
    gdal-2.1.1/frmts/hfa/hfatype.cpp
    gdal-2.1.1/frmts/hfa/hfaband.cpp
    gdal-2.1.1/frmts/hfa/hfacompress.cpp
    gdal-2.1.1/frmts/hfa/hfadataset.cpp
    gdal-2.1.1/frmts/hfa/hfa_overviews.cpp
    gdal-2.1.1/frmts/aigrid/aigdataset.cpp
    gdal-2.1.1/frmts/aigrid/gridlib.c
    gdal-2.1.1/frmts/aigrid/aigopen.c
    gdal-2.1.1/frmts/aigrid/aigccitt.c
    gdal-2.1.1/frmts/aaigrid/aaigriddataset.cpp
    gdal-2.1.1/frmts/ceos/ceosopen.c
    gdal-2.1.1/frmts/ceos/ceosopen.h
    gdal-2.1.1/frmts/ceos/ceosdataset.cpp
    gdal-2.1.1/frmts/ceos2/sar_ceosdataset.cpp
    gdal-2.1.1/frmts/ceos2/ceosrecipe.c
    gdal-2.1.1/frmts/ceos2/ceossar.c
    gdal-2.1.1/frmts/ceos2/ceos.c
    gdal-2.1.1/frmts/ceos2/ceos.h
    gdal-2.1.1/frmts/ceos2/link.c
    gdal-2.1.1/frmts/iso8211/ddfmodule.cpp
    gdal-2.1.1/frmts/iso8211/ddfutils.cpp
    gdal-2.1.1/frmts/iso8211/ddffielddefn.cpp
    gdal-2.1.1/frmts/iso8211/ddfrecord.cpp
    gdal-2.1.1/frmts/iso8211/ddffield.cpp
    gdal-2.1.1/frmts/iso8211/ddfsubfielddefn.cpp
    gdal-2.1.1/frmts/xpm/xpmdataset.cpp
    gdal-2.1.1/frmts/sdts/sdtsiref.cpp
    gdal-2.1.1/frmts/sdts/sdtscatd.cpp
    gdal-2.1.1/frmts/sdts/sdtslinereader.cpp
    gdal-2.1.1/frmts/sdts/sdtslib.cpp
    gdal-2.1.1/frmts/sdts/sdtspointreader.cpp
    gdal-2.1.1/frmts/sdts/sdtsattrreader.cpp
    gdal-2.1.1/frmts/sdts/sdtstransfer.cpp
    gdal-2.1.1/frmts/sdts/sdtspolygonreader.cpp
    gdal-2.1.1/frmts/sdts/sdtsxref.cpp
    gdal-2.1.1/frmts/sdts/sdtsrasterreader.cpp
    gdal-2.1.1/frmts/sdts/sdtsindexedreader.cpp
    gdal-2.1.1/frmts/sdts/sdtsdataset.cpp
    gdal-2.1.1/frmts/raw/rawdataset.cpp
    gdal-2.1.1/frmts/raw/rawdataset.h
    gdal-2.1.1/frmts/raw/ehdrdataset.cpp
    gdal-2.1.1/frmts/raw/pauxdataset.cpp
    gdal-2.1.1/frmts/raw/doq1dataset.cpp
    gdal-2.1.1/frmts/raw/doq2dataset.cpp
    gdal-2.1.1/frmts/raw/mffdataset.cpp
    gdal-2.1.1/frmts/raw/hkvdataset.cpp
    gdal-2.1.1/frmts/raw/pnmdataset.cpp
    gdal-2.1.1/frmts/raw/fujibasdataset.cpp
    gdal-2.1.1/frmts/raw/envidataset.cpp
    gdal-2.1.1/frmts/raw/gscdataset.cpp
    gdal-2.1.1/frmts/raw/fastdataset.cpp
    gdal-2.1.1/frmts/raw/atlsci_spheroid.cpp
    gdal-2.1.1/frmts/raw/atlsci_spheroid.h
    gdal-2.1.1/frmts/raw/btdataset.cpp
    gdal-2.1.1/frmts/raw/landataset.cpp
    gdal-2.1.1/frmts/raw/cpgdataset.cpp
    gdal-2.1.1/frmts/raw/idadataset.cpp
    gdal-2.1.1/frmts/raw/ndfdataset.cpp
    gdal-2.1.1/frmts/raw/dipxdataset.cpp
    gdal-2.1.1/frmts/raw/genbindataset.cpp
    gdal-2.1.1/frmts/raw/lcpdataset.cpp
    gdal-2.1.1/frmts/raw/eirdataset.cpp
    gdal-2.1.1/frmts/raw/gtxdataset.cpp
    gdal-2.1.1/frmts/raw/loslasdataset.cpp
    gdal-2.1.1/frmts/raw/ntv2dataset.cpp
    gdal-2.1.1/frmts/raw/ace2dataset.cpp
    gdal-2.1.1/frmts/raw/snodasdataset.cpp
    gdal-2.1.1/frmts/raw/ctable2dataset.cpp
    gdal-2.1.1/frmts/raw/krodataset.cpp
    gdal-2.1.1/frmts/raw/roipacdataset.cpp
    gdal-2.1.1/frmts/raw/iscedataset.cpp
    gdal-2.1.1/frmts/dted/dted_api.c
    gdal-2.1.1/frmts/dted/dted_api.h
    gdal-2.1.1/frmts/dted/dteddataset.cpp
    gdal-2.1.1/frmts/dted/dted_create.c
    gdal-2.1.1/frmts/dted/dted_ptstream.c
    gdal-2.1.1/frmts/mem/memdataset.cpp
    gdal-2.1.1/frmts/mem/memdataset.h
    gdal-2.1.1/frmts/jdem/jdemdataset.cpp
    gdal-2.1.1/frmts/envisat/EnvisatFile.c
    gdal-2.1.1/frmts/envisat/EnvisatFile.h
    gdal-2.1.1/frmts/envisat/records.c
    gdal-2.1.1/frmts/envisat/records.h
    gdal-2.1.1/frmts/envisat/adsrange.cpp
    gdal-2.1.1/frmts/envisat/unwrapgcps.cpp
    gdal-2.1.1/frmts/envisat/envisatdataset.cpp
    gdal-2.1.1/frmts/elas/elasdataset.cpp
    gdal-2.1.1/frmts/fit/fitdataset.cpp
    gdal-2.1.1/frmts/fit/fit.cpp
    gdal-2.1.1/frmts/fit/fit.h
    gdal-2.1.1/frmts/vrt/vrtdataset.cpp
    gdal-2.1.1/frmts/vrt/vrtdataset.h
    gdal-2.1.1/frmts/vrt/vrtrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtdriver.cpp
    gdal-2.1.1/frmts/vrt/vrtsources.cpp
    gdal-2.1.1/frmts/vrt/vrtfilters.cpp
    gdal-2.1.1/frmts/vrt/vrtsourcedrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtrawrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtwarped.cpp
    gdal-2.1.1/frmts/vrt/vrtderivedrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtpansharpened.cpp
    gdal-2.1.1/frmts/usgsdem/usgsdemdataset.cpp
    gdal-2.1.1/frmts/usgsdem/usgsdem_create.cpp
    gdal-2.1.1/frmts/l1b/l1bdataset.cpp
    gdal-2.1.1/frmts/bmp/bmpdataset.cpp
    gdal-2.1.1/frmts/airsar/airsardataset.cpp
    gdal-2.1.1/frmts/rs2/rs2dataset.cpp
    gdal-2.1.1/frmts/ilwis/ilwisdataset.cpp
    gdal-2.1.1/frmts/ilwis/ilwisdataset.h
    gdal-2.1.1/frmts/ilwis/ilwiscoordinatesystem.cpp
    gdal-2.1.1/frmts/rmf/rmfdataset.cpp
    gdal-2.1.1/frmts/rmf/rmfdataset.h
    gdal-2.1.1/frmts/rmf/rmflzw.cpp
    gdal-2.1.1/frmts/rmf/rmfdem.cpp
    gdal-2.1.1/frmts/leveller/levellerdataset.cpp
    gdal-2.1.1/frmts/sgi/sgidataset.cpp
    gdal-2.1.1/frmts/srtmhgt/srtmhgtdataset.cpp
    gdal-2.1.1/frmts/idrisi/IdrisiDataset.cpp
    gdal-2.1.1/frmts/gsg/gsagdataset.cpp
    gdal-2.1.1/frmts/gsg/gsbgdataset.cpp
    gdal-2.1.1/frmts/gsg/gs7bgdataset.cpp
    gdal-2.1.1/frmts/ingr/IntergraphDataset.cpp
    gdal-2.1.1/frmts/ingr/IntergraphDataset.h
    gdal-2.1.1/frmts/ingr/IntergraphBand.cpp
    gdal-2.1.1/frmts/ingr/IntergraphBand.h
    gdal-2.1.1/frmts/ingr/IngrTypes.cpp
    gdal-2.1.1/frmts/ingr/IngrTypes.h
    gdal-2.1.1/frmts/ingr/JpegHelper.cpp
    gdal-2.1.1/frmts/ingr/JpegHelper.h
    gdal-2.1.1/frmts/ers/ersdataset.cpp
    gdal-2.1.1/frmts/ers/ershdrnode.cpp
    gdal-2.1.1/frmts/ers/ershdrnode.h
    gdal-2.1.1/frmts/jaxapalsar/jaxapalsardataset.cpp
    gdal-2.1.1/frmts/dimap/dimapdataset.cpp
    gdal-2.1.1/frmts/gff/gff_dataset.cpp
    gdal-2.1.1/frmts/cosar/cosar_dataset.cpp
    gdal-2.1.1/frmts/pds/pdsdataset.cpp
    gdal-2.1.1/frmts/pds/isis2dataset.cpp
    gdal-2.1.1/frmts/pds/isis3dataset.cpp
    gdal-2.1.1/frmts/pds/vicardataset.cpp
    gdal-2.1.1/frmts/pds/nasakeywordhandler.cpp
    gdal-2.1.1/frmts/pds/nasakeywordhandler.h
    gdal-2.1.1/frmts/pds/vicarkeywordhandler.cpp
    gdal-2.1.1/frmts/pds/vicarkeywordhandler.h
    gdal-2.1.1/frmts/adrg/adrgdataset.cpp
    gdal-2.1.1/frmts/adrg/srpdataset.cpp
    gdal-2.1.1/frmts/coasp/coasp_dataset.cpp
    gdal-2.1.1/frmts/tsx/tsxdataset.cpp
    gdal-2.1.1/frmts/terragen/terragendataset.cpp
    gdal-2.1.1/frmts/blx/blxdataset.cpp
    gdal-2.1.1/frmts/blx/blx.c
    gdal-2.1.1/frmts/blx/blx.h
    gdal-2.1.1/frmts/msgn/msgndataset.cpp
    gdal-2.1.1/frmts/msgn/msg_basic_types.cpp
    gdal-2.1.1/frmts/msgn/msg_basic_types.h
    gdal-2.1.1/frmts/msgn/msg_reader_core.cpp
    gdal-2.1.1/frmts/msgn/msg_reader_core.h
    gdal-2.1.1/frmts/til/tildataset.cpp
    gdal-2.1.1/frmts/r/rdataset.cpp
    gdal-2.1.1/frmts/r/rcreatecopy.cpp
    gdal-2.1.1/frmts/northwood/grddataset.cpp
    gdal-2.1.1/frmts/northwood/grcdataset.cpp
    gdal-2.1.1/frmts/northwood/northwood.cpp
    gdal-2.1.1/frmts/northwood/northwood.h
    gdal-2.1.1/frmts/saga/sagadataset.cpp
    gdal-2.1.1/frmts/xyz/xyzdataset.cpp
    gdal-2.1.1/frmts/hf2/hf2dataset.cpp
    gdal-2.1.1/frmts/kmlsuperoverlay/kmlsuperoverlaydataset.cpp
    gdal-2.1.1/frmts/kmlsuperoverlay/kmlsuperoverlaydataset.h
    gdal-2.1.1/frmts/ctg/ctgdataset.cpp
    gdal-2.1.1/frmts/e00grid/e00griddataset.cpp
    gdal-2.1.1/frmts/zmap/zmapdataset.cpp
    gdal-2.1.1/frmts/ngsgeoid/ngsgeoiddataset.cpp
    gdal-2.1.1/frmts/iris/irisdataset.cpp
    gdal-2.1.1/frmts/map/mapdataset.cpp
    gdal-2.1.1/frmts/cals/calsdataset.cpp
    gdal-2.1.1/frmts/safe/safedataset.cpp
    gdal-2.1.1/frmts/sentinel2/sentinel2dataset.cpp
    gdal-2.1.1/frmts/mrf/marfa_dataset.cpp
    gdal-2.1.1/frmts/mrf/mrf_band.cpp
    gdal-2.1.1/frmts/mrf/JPEG_band.cpp
    gdal-2.1.1/frmts/mrf/PNG_band.cpp
    gdal-2.1.1/frmts/mrf/JPNG_band.cpp
    gdal-2.1.1/frmts/mrf/Raw_band.cpp
    gdal-2.1.1/frmts/mrf/Tif_band.cpp
    gdal-2.1.1/frmts/mrf/mrf_util.cpp
    gdal-2.1.1/frmts/mrf/mrf_overview.cpp
    gdal-2.1.1/frmts/mrf/JPEG12_band.cpp
    gdal-2.1.1/frmts/mrf/JPEG_band.cpp
    gdal-2.1.1/frmts/mrf/JPEG12_band.cpp
    gdal-2.1.1/frmts/mrf/LERC_band.cpp
    gdal-2.1.1/frmts/mrf/libLERC/BitMask.cpp
    gdal-2.1.1/frmts/mrf/libLERC/BitMask.h
    gdal-2.1.1/frmts/mrf/libLERC/BitMask2.cpp
    gdal-2.1.1/frmts/mrf/libLERC/BitMask2.h
    gdal-2.1.1/frmts/mrf/libLERC/BitStuffer.cpp
    gdal-2.1.1/frmts/mrf/libLERC/BitStuffer.h
    gdal-2.1.1/frmts/mrf/libLERC/BitStuffer2.cpp
    gdal-2.1.1/frmts/mrf/libLERC/BitStuffer2.h
    gdal-2.1.1/frmts/mrf/libLERC/CntZImage.cpp
    gdal-2.1.1/frmts/mrf/libLERC/CntZImage.h
    gdal-2.1.1/frmts/mrf/libLERC/Huffman.cpp
    gdal-2.1.1/frmts/mrf/libLERC/Huffman.h
    gdal-2.1.1/frmts/mrf/libLERC/RLE.cpp
    gdal-2.1.1/frmts/mrf/libLERC/RLE.h
    gdal-2.1.1/frmts/mrf/libLERC/Lerc2.cpp
    gdal-2.1.1/frmts/mrf/libLERC/Lerc2.h
    gdal-2.1.1/frmts/grib/gribdataset.cpp
    gdal-2.1.1/frmts/bsb/bsb_read.c
    gdal-2.1.1/frmts/bsb/bsb_read.h
    gdal-2.1.1/frmts/bsb/bsbdataset.cpp
    gdal-2.1.1/frmts/gif/gifdataset.cpp
    gdal-2.1.1/frmts/gif/biggifdataset.cpp
    gdal-2.1.1/frmts/gif/gifabstractdataset.cpp
    gdal-2.1.1/frmts/gif/gifabstractdataset.h
    gdal-2.1.1/frmts/jpeg/jpgdataset.cpp
    gdal-2.1.1/frmts/jpeg/vsidataio.cpp
    gdal-2.1.1/frmts/jpeg/vsidataio.h
    gdal-2.1.1/frmts/jpeg/jpgdataset_12.cpp
    gdal-2.1.1/frmts/jpeg/vsidataio_12.cpp
    gdal-2.1.1/frmts/png/pngdataset.cpp
    gdal-2.1.1/frmts/pcraster/pcrasterdataset.cpp
    gdal-2.1.1/frmts/pcraster/pcrasterdataset.h
    gdal-2.1.1/frmts/pcraster/pcrastermisc.cpp
    gdal-2.1.1/frmts/pcraster/pcrasterrasterband.cpp
    gdal-2.1.1/frmts/pcraster/pcrasterrasterband.h
    gdal-2.1.1/frmts/pcraster/pcrasterutil.cpp
    gdal-2.1.1/frmts/pcraster/pcrasterutil.h
    gdal-2.1.1/frmts/zlib/adler32.c
    gdal-2.1.1/frmts/zlib/compress.c
    gdal-2.1.1/frmts/zlib/crc32.c
    gdal-2.1.1/frmts/zlib/crc32.h
    gdal-2.1.1/frmts/zlib/deflate.c
    gdal-2.1.1/frmts/zlib/deflate.h
    gdal-2.1.1/frmts/zlib/gzio.c
    gdal-2.1.1/frmts/zlib/infback.c
    gdal-2.1.1/frmts/zlib/inffast.c
    gdal-2.1.1/frmts/zlib/inffast.h
    gdal-2.1.1/frmts/zlib/inflate.c
    gdal-2.1.1/frmts/zlib/inflate.h
    gdal-2.1.1/frmts/zlib/inftrees.c
    gdal-2.1.1/frmts/zlib/inftrees.h
    gdal-2.1.1/frmts/zlib/trees.c
    gdal-2.1.1/frmts/zlib/trees.h
    gdal-2.1.1/frmts/zlib/uncompr.c
    gdal-2.1.1/frmts/zlib/zutil.c
    gdal-2.1.1/frmts/zlib/zutil.h
    gdal-2.1.1/frmts/pcidsk/pcidskdataset2.cpp
    gdal-2.1.1/frmts/pcidsk/pcidskdataset2.h
    gdal-2.1.1/frmts/pcidsk/ogrpcidsklayer.cpp
    gdal-2.1.1/frmts/pcidsk/vsi_pcidsk_io.cpp
    gdal-2.1.1/frmts/pcidsk/gdal_edb.cpp
    gdal-2.1.1/frmts/rik/rikdataset.cpp
    gdal-2.1.1/frmts/ozi/ozidataset.cpp
    gdal-2.1.1/frmts/pdf/pdfdataset.cpp
    gdal-2.1.1/frmts/pdf/pdfio.cpp
    gdal-2.1.1/frmts/pdf/pdfio.h
    gdal-2.1.1/frmts/pdf/pdfobject.cpp
    gdal-2.1.1/frmts/pdf/pdfobject.h
    gdal-2.1.1/frmts/pdf/pdfcreatecopy.cpp
    gdal-2.1.1/frmts/pdf/pdfcreatecopy.h
    gdal-2.1.1/frmts/pdf/ogrpdflayer.cpp
    gdal-2.1.1/frmts/pdf/pdfwritabledataset.cpp
    gdal-2.1.1/frmts/pdf/pdfreadvectors.cpp
    gdal-2.1.1/frmts/arg/argdataset.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrsfdriverregistrar.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrsfdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrregisterall.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_gensql.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_gensql.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_attrind.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_miattrind.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerdecorator.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerdecorator.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrwarpedlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrwarpedlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrunionlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrunionlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerpool.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerpool.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexedlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexedlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexeddatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexeddatasource.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogremulatedtransaction.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogremulatedtransaction.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogreditablelayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogreditablelayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_bin.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_binwr.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_e00gen.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_e00parse.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_e00write.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_e00read.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_mbyte.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_mbyte.h
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_misc.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/avc_rawbin.c
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravcbindriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravcbindatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravcbinlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravclayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravcdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravce00layer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravce00datasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/avc/ogravce00driver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/bna/ogrbnadriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/bna/ogrbnadatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/bna/ogrbnalayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/bna/ogrbnaparser.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/bna/ogrbnaparser.h
    gdal-2.1.1/ogr/ogrsf_frmts/csv/ogrcsvdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/csv/ogrcsvdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/csv/ogrcsvlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/ogrdgndriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/ogrdgndatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/ogrdgnlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/dgnopen.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/dgnread.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/dgnfloat.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/dgnhelp.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/dgnwrite.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dgn/dgnstroke.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/arraylist.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/arraylist.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/debug.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/debug.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_tokener.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_tokener.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_util.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_util.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/linkhash.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/linkhash.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/printbuf.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/printbuf.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object_iterator.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object_iterator.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_c_version.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_c_version.h
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlpropertydefn.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlfeatureclass.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlfeature.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlreader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlreader.h
    gdal-2.1.1/ogr/ogrsf_frmts/gml/parsexsd.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/parsexsd.h
    gdal-2.1.1/ogr/ogrsf_frmts/gml/resolvexlinks.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/hugefileresolver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlutils.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlutils.h
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlreadstate.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlhandler.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/trstring.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gfstemplate.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlregistry.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/gmlregistry.h
    gdal-2.1.1/ogr/ogrsf_frmts/gml/ogrgmldriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/ogrgmldatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gml/ogrgmllayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gmt/ogrgmtdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gmt/ogrgmtdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gmt/ogrgmtlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogrmemdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogrmemdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogrmemlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/kml/ogr2kmlgeometry.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/kml/ogrkmldriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/kml/ogrkmldatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/kml/ogrkmllayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_rawbinblock.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_mapheaderblock.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_mapindexblock.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_mapobjectblock.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_mapcoordblock.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_feature.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_feature_mif.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_mapfile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_idfile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_datfile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_tabfile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_miffile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_utils.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_utils.h
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_imapinfofile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_middatafile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_bounds.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_maptoolblock.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_tooldef.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_coordsys.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_spatialref.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_ogr_driver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_ogr_driver.h
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_indfile.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_tabview.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_ogr_datasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_geometry.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_geometry.h
    gdal-2.1.1/ogr/ogrsf_frmts/mitab/mitab_tabseamless.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntffilereader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntfrecord.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ogrntfdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ogrntfdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ogrntflayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntf_estlayers.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ogrntffeatureclasslayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntf_generic.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntf_raster.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntf_codelist.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/ntf/ntfstroke.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gpx/ogrgpxdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gpx/ogrgpxdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gpx/ogrgpxlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/rec/ogrrecdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/rec/ogrrecdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/rec/ogrreclayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/rec/ll_recio.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/ogrs57driver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/ogrs57datasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/ogrs57layer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/s57reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/s57writer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/ddfrecordindex.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/s57classregistrar.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/s57filecollector.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/s57/s57featuredefns.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sdts/ogrsdtsdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sdts/ogrsdtsdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sdts/ogrsdtslayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/shape/shape2ogr.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/shape/shpopen.c
    gdal-2.1.1/ogr/ogrsf_frmts/shape/dbfopen.c
    gdal-2.1.1/ogr/ogrsf_frmts/shape/shptree.c
    gdal-2.1.1/ogr/ogrsf_frmts/shape/sbnsearch.c
    gdal-2.1.1/ogr/ogrsf_frmts/shape/shp_vsi.c
    gdal-2.1.1/ogr/ogrsf_frmts/shape/shp_vsi.h
    gdal-2.1.1/ogr/ogrsf_frmts/shape/ogrshapedriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/shape/ogrshapedatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/shape/ogrshapelayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/ogrtigerdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/ogrtigerdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/ogrtigerlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerfilebase.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigercompletechain.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigeraltname.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerfeatureids.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerzipcodes.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerlandmarks.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerarealandmarks.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerkeyfeatures.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerpolygon.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerpolygoncorrections.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerentitynames.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerpolygoneconomic.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigeridhistory.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerpolychainlink.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerpip.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerspatialmetadata.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigertlidrange.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerzerocellid.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigeroverunder.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerzipplus4.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/tiger/tigerpoint.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/vrt/ogrvrtdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/vrt/ogrvrtlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/vrt/ogrvrtdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/geoconcept.c
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/geoconcept.h
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/geoconcept_syscoord.c
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/geoconcept_syscoord.h
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptdriver.h
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptdatasource.h
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogrxplanedriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogrxplanedatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogrxplanelayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_geo_utils.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_geo_utils.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_apt_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_apt_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_nav_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_nav_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_fix_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_fix_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_awy_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_awy_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/georss/ogrgeorssdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/georss/ogrgeorssdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/georss/ogrgeorsslayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/ogrgtmdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/ogrgtmdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/ogrgtmlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/gtm.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/gtm.h
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/gtmwaypointlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gtm/gtmtracklayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxflayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfreader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxf_blockmap.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxf_dimension.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfwriterds.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfwriterlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/intronurbs.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxf_polyline_smooth.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxf_polyline_smooth.h
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfblockslayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxfblockswriterlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogrdxf_hatch.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogr_autocad_services.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/dxf/ogr_autocad_services.h
    gdal-2.1.1/ogr/ogrsf_frmts/pgdump/ogrpgdumpdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/pgdump/ogrpgdumpdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/pgdump/ogrpgdumplayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gpsbabel/ogrgpsbabeldriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gpsbabel/ogrgpsbabeldatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/gpsbabel/ogrgpsbabelwritedatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sua/ogrsuadriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sua/ogrsuadatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sua/ogrsualayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openair/ogropenairdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openair/ogropenairdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openair/ogropenairlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openair/ogropenairlabellayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/pds/ogrpdsdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/pds/ogrpdsdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/pds/ogrpdslayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/htf/ogrhtfdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/htf/ogrhtfdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/htf/ogrhtflayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/aeronavfaa/ograeronavfaadriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/aeronavfaa/ograeronavfaadatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/aeronavfaa/ograeronavfaalayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/edigeo/ogredigeodriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/edigeo/ogredigeodatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/edigeo/ogredigeolayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/svg/ogrsvgdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/svg/ogrsvgdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/svg/ogrsvglayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/idrisi/ogridrisidriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/idrisi/ogridrisidatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/idrisi/ogridrisilayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/arcgen/ograrcgendriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/arcgen/ograrcgendatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/arcgen/ograrcgenlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/segukooa/ogrsegukooadriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/segukooa/ogrsegukooadatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/segukooa/ogrsegukooalayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/segy/ogrsegydriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/segy/ogrsegydatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/segy/ogrsegylayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sxf/ogrsxfdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sxf/ogrsxfdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/sxf/ogrsxflayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/ogropenfilegdbdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/ogropenfilegdbdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/ogropenfilegdblayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/filegdbtable.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/filegdbtable.h
    gdal-2.1.1/ogr/ogrsf_frmts/openfilegdb/filegdbindex.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/wasp/ogrwaspdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/wasp/ogrwaspdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/wasp/ogrwasplayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/selafin/ogrselafindriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/selafin/ogrselafindatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/selafin/ogrselafinlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/selafin/io_selafin.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/selafin/io_selafin.h
    gdal-2.1.1/ogr/ogrsf_frmts/jml/ogrjmldataset.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/jml/ogrjmllayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/jml/ogrjmlwriterlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/vdv/ogrvdvdatasource.cpp
    gdal-2.1.1/apps/commonutils.cpp
    gdal-2.1.1/apps/commonutils.h
    gdal-2.1.1/apps/gdalinfo_lib.cpp
    gdal-2.1.1/apps/gdal_translate_lib.cpp
    gdal-2.1.1/apps/gdalwarp_lib.cpp
    gdal-2.1.1/apps/ogr2ogr_lib.cpp
    gdal-2.1.1/apps/gdaldem_lib.cpp
    gdal-2.1.1/apps/nearblack_lib.cpp
    gdal-2.1.1/apps/gdal_grid_lib.cpp
    gdal-2.1.1/apps/gdal_rasterize_lib.cpp
    gdal-2.1.1/apps/gdalbuildvrt_lib.cpp
    gdal-2.1.1/apps/gdalinfo_bin.cpp
    gdal-2.1.1/apps/gdalserver.c
    gdal-2.1.1/apps/gdal_translate_bin.cpp
    gdal-2.1.1/apps/gdaladdo.cpp
    gdal-2.1.1/apps/gdalwarp_bin.cpp
    gdal-2.1.1/apps/nearblack_bin.cpp
    gdal-2.1.1/apps/gdalmanage.cpp
    gdal-2.1.1/apps/gdalenhance.cpp
    gdal-2.1.1/apps/gdaltransform.cpp
    gdal-2.1.1/apps/gdaldem_bin.cpp
    gdal-2.1.1/apps/gdallocationinfo.cpp
    gdal-2.1.1/apps/gdalsrsinfo.cpp
    gdal-2.1.1/apps/gdal_contour.cpp
    gdal-2.1.1/apps/gdaltindex.c
    gdal-2.1.1/apps/gdal_rasterize_bin.cpp
    gdal-2.1.1/apps/gdal_grid_bin.cpp
    gdal-2.1.1/apps/ogrinfo.cpp
    gdal-2.1.1/apps/ogr2ogr_bin.cpp
    gdal-2.1.1/apps/ogrtindex.cpp
    gdal-2.1.1/apps/ogrlineref.cpp
    gdal-2.1.1/apps/testepsg.cpp
    gdal-2.1.1/apps/gdalbuildvrt_bin.cpp
    )

include_directories(
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
    )

add_library(GDAL_211 STATIC
    ${GDAL_211_SOURCE}
    )

target_link_libraries(GDAL_211
    )

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
# add_subdirectory( bullet-2.81-rev2613/src/BulletSoftBody )
# add_subdirectory( bullet-2.81-rev2613/src/BulletCollision )
# add_subdirectory( bullet-2.81-rev2613/src/BulletDynamics )
# add_subdirectory( bullet-2.81-rev2613/src/LinearMath )

