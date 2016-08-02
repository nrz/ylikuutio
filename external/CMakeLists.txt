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
    gdal-2.1.1/alg/contour.cpp
    gdal-2.1.1/alg/gdalchecksum.cpp
    gdal-2.1.1/alg/gdalcutline.cpp
    gdal-2.1.1/alg/gdaldither.cpp
    gdal-2.1.1/alg/gdalgeoloc.cpp
    gdal-2.1.1/alg/gdalgridavx.cpp
    gdal-2.1.1/alg/gdalgrid.cpp
    gdal-2.1.1/alg/gdalgridsse.cpp
    gdal-2.1.1/alg/gdalmatching.cpp
    gdal-2.1.1/alg/gdalmediancut.cpp
    gdal-2.1.1/alg/gdal_octave.cpp
    gdal-2.1.1/alg/gdalpansharpen.cpp
    gdal-2.1.1/alg/gdalproximity.cpp
    gdal-2.1.1/alg/gdalrasterize.cpp
    gdal-2.1.1/alg/gdalrasterpolygonenumerator.cpp
    gdal-2.1.1/alg/gdal_rpc.cpp
    gdal-2.1.1/alg/gdalsievefilter.cpp
    gdal-2.1.1/alg/gdal_simplesurf.cpp
    gdal-2.1.1/alg/gdalsimplewarp.cpp
    gdal-2.1.1/alg/gdal_tps.cpp
    gdal-2.1.1/alg/gdaltransformer.cpp
    gdal-2.1.1/alg/gdaltransformgeolocs.cpp
    gdal-2.1.1/alg/gdalwarper.cpp
    gdal-2.1.1/alg/gdalwarpkernel.cpp
    gdal-2.1.1/alg/gdalwarpoperation.cpp
    gdal-2.1.1/alg/llrasterize.cpp
    gdal-2.1.1/alg/polygonize.cpp
    gdal-2.1.1/alg/rasterfill.cpp
    gdal-2.1.1/alg/thinplatespline.cpp
    gdal-2.1.1/frmts/gtiff/geotiff.cpp
    gdal-2.1.1/frmts/gtiff/gt_citation.cpp
    gdal-2.1.1/frmts/gtiff/gt_jpeg_copy.cpp
    gdal-2.1.1/frmts/gtiff/gt_overview.cpp
    gdal-2.1.1/frmts/gtiff/gt_wkt_srs.cpp
    gdal-2.1.1/frmts/gtiff/tifvsi.cpp

    # in-source build seems to populate `gdal-2.1.1/apps/` with `*.c`,
    # but it has already before that `*.cpp` & `*.h` (I'm not sure about all of them).
    gdal-2.1.1/apps/commonutils.cpp
    gdal-2.1.1/apps/dumpoverviews.cpp
    gdal-2.1.1/apps/gdaladdo.cpp
    gdal-2.1.1/apps/gdalasyncread.cpp
    gdal-2.1.1/apps/gdalbuildvrt_bin.cpp
    gdal-2.1.1/apps/gdalbuildvrt_lib.cpp
    gdal-2.1.1/apps/gdal_contour.cpp
    gdal-2.1.1/apps/gdaldem_bin.cpp
    gdal-2.1.1/apps/gdaldem_lib.cpp
    gdal-2.1.1/apps/gdalenhance.cpp
    gdal-2.1.1/apps/gdal_grid_bin.cpp
    gdal-2.1.1/apps/gdal_grid_lib.cpp
    gdal-2.1.1/apps/gdalinfo_bin.cpp
    gdal-2.1.1/apps/gdalinfo_lib.cpp
    gdal-2.1.1/apps/gdallocationinfo.cpp
    gdal-2.1.1/apps/gdalmanage.cpp
    gdal-2.1.1/apps/gdal_rasterize_bin.cpp
    gdal-2.1.1/apps/gdal_rasterize_lib.cpp
    gdal-2.1.1/apps/gdalsrsinfo.cpp
    gdal-2.1.1/apps/gdaltorture.cpp
    gdal-2.1.1/apps/gdaltransform.cpp
    gdal-2.1.1/apps/gdal_translate_bin.cpp
    gdal-2.1.1/apps/gdal_translate_lib.cpp
    gdal-2.1.1/apps/gdalwarp_bin.cpp
    gdal-2.1.1/apps/gdalwarp_lib.cpp
    gdal-2.1.1/apps/gnmanalyse.cpp
    gdal-2.1.1/apps/gnmmanage.cpp
    gdal-2.1.1/apps/multireadtest.cpp
    gdal-2.1.1/apps/nearblack_bin.cpp
    gdal-2.1.1/apps/nearblack_lib.cpp
    # gdal-2.1.1/apps/ogr2ogr_bin.cpp
    # gdal-2.1.1/apps/ogr2ogr_lib.cpp
    # gdal-2.1.1/apps/ogrdissolve.cpp
    gdal-2.1.1/apps/ogrinfo.cpp
    gdal-2.1.1/apps/ogrlineref.cpp
    gdal-2.1.1/apps/ogrtindex.cpp
    gdal-2.1.1/apps/testepsg.cpp
    gdal-2.1.1/apps/test_ogrsf.cpp
    gdal-2.1.1/apps/testreprojmulti.cpp

    # libgeotiff seems to be written in C.
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_extra.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_free.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_get.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_names.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_new.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_normalize.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_print.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_set.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_simpletags.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_tiffp.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geotiff_proj4.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_trans.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_write.c
    gdal-2.1.1/frmts/gtiff/libgeotiff/xtiff.c

    # libtiff seems to be written in C.
    gdal-2.1.1/frmts/gtiff/libtiff/tif_aux.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_close.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_codec.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_color.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_compress.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_dir.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_dirinfo.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_dirread.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_dirwrite.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_dumpmode.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_error.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_extension.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_fax3.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_fax3sm.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_flush.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_getimage.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_jpeg_12.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_jpeg.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_luv.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_lzma.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_lzw.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_next.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_ojpeg.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_open.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_packbits.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_pixarlog.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_predict.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_print.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_read.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_strip.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_swab.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_thunder.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_tile.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_version.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_vsi.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_warning.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_write.c
    gdal-2.1.1/frmts/gtiff/libtiff/tif_zip.c

    gdal-2.1.1/frmts/mem/memdataset.cpp
    gdal-2.1.1/frmts/raw/ace2dataset.cpp
    gdal-2.1.1/frmts/raw/atlsci_spheroid.cpp
    gdal-2.1.1/frmts/raw/btdataset.cpp
    gdal-2.1.1/frmts/raw/cpgdataset.cpp
    gdal-2.1.1/frmts/raw/ctable2dataset.cpp
    gdal-2.1.1/frmts/raw/dipxdataset.cpp
    gdal-2.1.1/frmts/raw/doq1dataset.cpp
    gdal-2.1.1/frmts/raw/doq2dataset.cpp
    gdal-2.1.1/frmts/raw/ehdrdataset.cpp
    gdal-2.1.1/frmts/raw/eirdataset.cpp
    gdal-2.1.1/frmts/raw/envidataset.cpp
    gdal-2.1.1/frmts/raw/fastdataset.cpp
    gdal-2.1.1/frmts/raw/fujibasdataset.cpp
    gdal-2.1.1/frmts/raw/genbindataset.cpp
    gdal-2.1.1/frmts/raw/gscdataset.cpp
    gdal-2.1.1/frmts/raw/gtxdataset.cpp
    gdal-2.1.1/frmts/raw/hkvdataset.cpp
    gdal-2.1.1/frmts/raw/idadataset.cpp
    gdal-2.1.1/frmts/raw/iscedataset.cpp
    gdal-2.1.1/frmts/raw/krodataset.cpp
    gdal-2.1.1/frmts/raw/landataset.cpp
    gdal-2.1.1/frmts/raw/lcpdataset.cpp
    gdal-2.1.1/frmts/raw/loslasdataset.cpp
    gdal-2.1.1/frmts/raw/mffdataset.cpp
    gdal-2.1.1/frmts/raw/ndfdataset.cpp
    gdal-2.1.1/frmts/raw/ntv2dataset.cpp
    gdal-2.1.1/frmts/raw/pauxdataset.cpp
    gdal-2.1.1/frmts/raw/pnmdataset.cpp
    gdal-2.1.1/frmts/raw/rawdataset.cpp
    gdal-2.1.1/frmts/raw/roipacdataset.cpp
    gdal-2.1.1/frmts/raw/snodasdataset.cpp
    gdal-2.1.1/frmts/vrt/vrtdataset.cpp
    gdal-2.1.1/frmts/vrt/vrtderivedrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtdriver.cpp
    gdal-2.1.1/frmts/vrt/vrtfilters.cpp
    gdal-2.1.1/frmts/vrt/vrtpansharpened.cpp
    gdal-2.1.1/frmts/vrt/vrtrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtrawrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtsourcedrasterband.cpp
    gdal-2.1.1/frmts/vrt/vrtsources.cpp
    gdal-2.1.1/frmts/vrt/vrtwarped.cpp
    gdal-2.1.1/gnm/gnmgenericnetwork.cpp
    gdal-2.1.1/gnm/gnmgraph.cpp
    gdal-2.1.1/gnm/gnmlayer.cpp
    gdal-2.1.1/gnm/gnmnetwork.cpp
    gdal-2.1.1/gnm/gnmresultlayer.cpp
    gdal-2.1.1/gnm/gnmrule.cpp
    gdal-2.1.1/ogr/gml2ogrgeometry.cpp
    gdal-2.1.1/ogr/ogr2gmlgeometry.cpp
    gdal-2.1.1/ogr/ogr_api.cpp
    gdal-2.1.1/ogr/ograpispy.cpp
    gdal-2.1.1/ogr/ograssemblepolygon.cpp
    gdal-2.1.1/ogr/ogrcircularstring.cpp
    gdal-2.1.1/ogr/ogrcompoundcurve.cpp
    gdal-2.1.1/ogr/ogrct.cpp
    # gdal-2.1.1/ogr/ogrcurvecollection.cpp
    gdal-2.1.1/ogr/ogrcurve.cpp
    gdal-2.1.1/ogr/ogrcurvepolygon.cpp
    gdal-2.1.1/ogr/ogr_expat.cpp
    gdal-2.1.1/ogr/ogrfeature.cpp
    # gdal-2.1.1/ogr/ogrfeaturedefn.cpp
    gdal-2.1.1/ogr/ogrfeaturequery.cpp
    gdal-2.1.1/ogr/ogrfeaturestyle.cpp
    gdal-2.1.1/ogr/ogrfielddefn.cpp
    gdal-2.1.1/ogr/ogr_fromepsg.cpp
    gdal-2.1.1/ogr/ogr_geocoding.cpp
    gdal-2.1.1/ogr/ogrgeomediageometry.cpp
    # gdal-2.1.1/ogr/ogrgeometrycollection.cpp
    # gdal-2.1.1/ogr/ogrgeometry.cpp # `error: ‘wkb25DBitInternalUse’ was not declared in this scope`
    gdal-2.1.1/ogr/ogrgeometryfactory.cpp
    gdal-2.1.1/ogr/ogrgeomfielddefn.cpp
    gdal-2.1.1/ogr/ogrlinearring.cpp
    # gdal-2.1.1/ogr/ogrlinestring.cpp # `error: ‘wkb25DBitInternalUse’ was not declared in this scope`
    gdal-2.1.1/ogr/ogrmulticurve.cpp
    gdal-2.1.1/ogr/ogrmultilinestring.cpp
    gdal-2.1.1/ogr/ogrmultipoint.cpp
    gdal-2.1.1/ogr/ogrmultipolygon.cpp
    gdal-2.1.1/ogr/ogrmultisurface.cpp
    gdal-2.1.1/ogr/ogr_opt.cpp
    gdal-2.1.1/ogr/ogrpgeogeometry.cpp
    # gdal-2.1.1/ogr/ogrpoint.cpp
    # gdal-2.1.1/ogr/ogrpolygon.cpp
    gdal-2.1.1/ogr/ogrspatialreference.cpp
    gdal-2.1.1/ogr/ogr_srs_dict.cpp
    gdal-2.1.1/ogr/ogr_srs_erm.cpp
    gdal-2.1.1/ogr/ogr_srs_esri.cpp
    gdal-2.1.1/ogr/ogr_srsnode.cpp
    gdal-2.1.1/ogr/ogr_srs_ozi.cpp
    gdal-2.1.1/ogr/ogr_srs_panorama.cpp
    gdal-2.1.1/ogr/ogr_srs_pci.cpp
    gdal-2.1.1/ogr/ogr_srs_proj4.cpp
    gdal-2.1.1/ogr/ogr_srs_usgs.cpp
    gdal-2.1.1/ogr/ogr_srs_validate.cpp
    gdal-2.1.1/ogr/ogr_srs_xml.cpp
    gdal-2.1.1/ogr/ogrsurface.cpp
    # gdal-2.1.1/ogr/ogrutils.cpp
    gdal-2.1.1/ogr/swq.cpp
    gdal-2.1.1/ogr/swq_expr_node.cpp
    gdal-2.1.1/ogr/swq_op_general.cpp
    gdal-2.1.1/ogr/swq_op_registrar.cpp
    gdal-2.1.1/ogr/swq_parser.cpp
    gdal-2.1.1/ogr/swq_select.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_attrind.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogreditablelayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogremulatedtransaction.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_gensql.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerdecorator.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerpool.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_miattrind.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexeddatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexedlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrregisterall.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrsfdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrsfdriverregistrar.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrunionlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrwarpedlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogresrijsonreader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsondatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsondriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonreader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonutils.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonwritelayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonwriter.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrtopojsonreader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_apt_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_awy_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_fix_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_geo_utils.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_nav_reader.h
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_reader.h

    # libjson seems to be written in C.
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/arraylist.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/debug.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_c_version.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object_iterator.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_tokener.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_util.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/linkhash.c
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/printbuf.c

    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogrmemdatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogrmemdriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogrmemlayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_apt_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_awy_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogrxplanedatasource.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogrxplanedriver.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_fix_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_geo_utils.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogrxplanelayer.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_nav_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/ogr_xplane_reader.cpp
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/test_geo_utils.cpp
    gdal-2.1.1/port/cpl_atomic_ops.cpp
    gdal-2.1.1/port/cpl_aws.cpp
    gdal-2.1.1/port/cpl_base64.cpp
    gdal-2.1.1/port/cpl_conv.cpp
    gdal-2.1.1/port/cpl_csv.cpp
    gdal-2.1.1/port/cpl_error.cpp
    gdal-2.1.1/port/cpl_findfile.cpp
    gdal-2.1.1/port/cpl_getexecpath.cpp
    gdal-2.1.1/port/cplgetsymbol.cpp
    gdal-2.1.1/port/cpl_google_oauth2.cpp
    gdal-2.1.1/port/cpl_hash_set.cpp
    gdal-2.1.1/port/cpl_http.cpp
    gdal-2.1.1/port/cplkeywordparser.cpp
    gdal-2.1.1/port/cpl_list.cpp
    gdal-2.1.1/port/cpl_minixml.cpp
    gdal-2.1.1/port/cpl_minizip_ioapi.cpp
    gdal-2.1.1/port/cpl_minizip_unzip.cpp
    gdal-2.1.1/port/cpl_minizip_zip.cpp
    gdal-2.1.1/port/cpl_multiproc.cpp
    # gdal-2.1.1/port/cpl_odbc.cpp
    gdal-2.1.1/port/cpl_path.cpp
    gdal-2.1.1/port/cpl_progress.cpp
    gdal-2.1.1/port/cpl_quad_tree.cpp
    gdal-2.1.1/port/cpl_recode.cpp
    gdal-2.1.1/port/cpl_recode_iconv.cpp
    gdal-2.1.1/port/cpl_recode_stub.cpp
    gdal-2.1.1/port/cpl_sha256.cpp
    gdal-2.1.1/port/cpl_spawn.cpp
    gdal-2.1.1/port/cpl_string.cpp
    gdal-2.1.1/port/cplstring.cpp
    gdal-2.1.1/port/cplstringlist.cpp
    gdal-2.1.1/port/cpl_strtod.cpp
    gdal-2.1.1/port/cpl_time.cpp
    gdal-2.1.1/port/cpl_virtualmem.cpp
    gdal-2.1.1/port/cpl_vsi_error.cpp
    gdal-2.1.1/port/cpl_vsil_abstract_archive.cpp
    gdal-2.1.1/port/cpl_vsil_buffered_reader.cpp
    gdal-2.1.1/port/cpl_vsil_cache.cpp
    gdal-2.1.1/port/cpl_vsil.cpp
    gdal-2.1.1/port/cpl_vsil_crypt.cpp
    gdal-2.1.1/port/cpl_vsil_curl.cpp
    gdal-2.1.1/port/cpl_vsil_curl_streaming.cpp
    gdal-2.1.1/port/cpl_vsil_gzip.cpp
    gdal-2.1.1/port/cpl_vsil_simple.cpp
    gdal-2.1.1/port/cpl_vsil_sparsefile.cpp
    gdal-2.1.1/port/cpl_vsil_stdin.cpp
    gdal-2.1.1/port/cpl_vsil_stdout.cpp
    gdal-2.1.1/port/cpl_vsil_subfile.cpp
    gdal-2.1.1/port/cpl_vsil_tar.cpp
    gdal-2.1.1/port/cpl_vsil_unix_stdio_64.cpp
    gdal-2.1.1/port/cpl_vsil_win32.cpp
    gdal-2.1.1/port/cpl_vsi_mem.cpp
    gdal-2.1.1/port/cpl_vsisimple.cpp
    gdal-2.1.1/port/cpl_worker_thread_pool.cpp
    gdal-2.1.1/port/cpl_xml_validate.cpp
    gdal-2.1.1/port/vsipreload.cpp
    gdal-2.1.1/port/xmlreformat.cpp
    gdal-2.1.1/gcore/gdalabstractbandblockcache.cpp
    gdal-2.1.1/gcore/gdalallvalidmaskband.cpp
    gdal-2.1.1/gcore/gdalarraybandblockcache.cpp
    gdal-2.1.1/gcore/gdalclientserver.cpp
    gdal-2.1.1/gcore/gdalcolortable.cpp
    gdal-2.1.1/gcore/gdaldataset.cpp
    gdal-2.1.1/gcore/gdaldefaultasync.cpp
    gdal-2.1.1/gcore/gdaldefaultoverviews.cpp
    gdal-2.1.1/gcore/gdaldllmain.cpp
    gdal-2.1.1/gcore/gdaldriver.cpp
    gdal-2.1.1/gcore/gdaldrivermanager.cpp
    gdal-2.1.1/gcore/gdalexif.cpp
    gdal-2.1.1/gcore/gdalgeorefpamdataset.cpp
    gdal-2.1.1/gcore/gdalgmlcoverage.cpp
    gdal-2.1.1/gcore/gdalhashsetbandblockcache.cpp
    gdal-2.1.1/gcore/gdaljp2abstractdataset.cpp
    gdal-2.1.1/gcore/gdaljp2box.cpp
    gdal-2.1.1/gcore/gdaljp2metadata.cpp
    gdal-2.1.1/gcore/gdaljp2metadatagenerator.cpp
    gdal-2.1.1/gcore/gdaljp2structure.cpp
    gdal-2.1.1/gcore/gdalmajorobject.cpp
    gdal-2.1.1/gcore/gdal_mdreader.cpp
    gdal-2.1.1/gcore/gdal_misc.cpp
    gdal-2.1.1/gcore/gdalmultidomainmetadata.cpp
    gdal-2.1.1/gcore/gdalnodatamaskband.cpp
    gdal-2.1.1/gcore/gdalnodatavaluesmaskband.cpp
    gdal-2.1.1/gcore/gdalopeninfo.cpp
    gdal-2.1.1/gcore/gdaloverviewdataset.cpp
    gdal-2.1.1/gcore/gdalpamdataset.cpp
    gdal-2.1.1/gcore/gdalpamproxydb.cpp
    gdal-2.1.1/gcore/gdalpamrasterband.cpp
    gdal-2.1.1/gcore/gdalproxydataset.cpp
    gdal-2.1.1/gcore/gdalproxypool.cpp
    gdal-2.1.1/gcore/gdalrasterband.cpp
    gdal-2.1.1/gcore/gdalrasterblock.cpp
    gdal-2.1.1/gcore/gdal_rat.cpp
    gdal-2.1.1/gcore/gdalrescaledalphaband.cpp
    gdal-2.1.1/gcore/gdalvirtualmem.cpp
    gdal-2.1.1/gcore/overview.cpp
    gdal-2.1.1/gcore/rasterio.cpp
    )

set(GDAL_211_HEADERS
    gdal-2.1.1/alg/gdal_alg.h
    gdal-2.1.1/alg/gdal_alg_priv.h
    gdal-2.1.1/alg/gdalgrid.h
    gdal-2.1.1/alg/gdalgrid_priv.h
    gdal-2.1.1/alg/gdalpansharpen.h
    gdal-2.1.1/alg/gdal_simplesurf.h
    gdal-2.1.1/alg/gdalwarper.h
    gdal-2.1.1/alg/gdalwarpkernel_opencl.h
    gdal-2.1.1/alg/gvgcpfit.h
    gdal-2.1.1/alg/internal_qhull_headers.h
    gdal-2.1.1/alg/thinplatespline.h

    # in-source build seems to populate `gdal-2.1.1/apps/` with `*.c`,
    # but it has already before that `*.cpp` & `*.h` (I'm not sure about all of them).
    gdal-2.1.1/apps/commonutils.h
    gdal-2.1.1/apps/gdal_utils.h
    gdal-2.1.1/apps/gdal_utils_priv.h

    gdal-2.1.1/frmts/gtiff/gt_citation.h
    gdal-2.1.1/frmts/gtiff/gtiff.h
    gdal-2.1.1/frmts/gtiff/gt_jpeg_copy.h
    gdal-2.1.1/frmts/gtiff/gt_overview.h
    gdal-2.1.1/frmts/gtiff/gt_wkt_srs_for_gdal.h
    gdal-2.1.1/frmts/gtiff/gt_wkt_srs.h
    gdal-2.1.1/frmts/gtiff/gt_wkt_srs_priv.h
    gdal-2.1.1/frmts/gtiff/tif_float.h
    gdal-2.1.1/frmts/gtiff/tifvsi.h

    # libgeotiff seems to be written in C.
    gdal-2.1.1/frmts/gtiff/libgeotiff/cpl_serv.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/gdal_libgeotiff_symbol_rename.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_config.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_keyp.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geokeys.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geonames.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_normalize.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_simpletags.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geotiff.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geotiffio.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geo_tiffp.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/geovalues.h
    gdal-2.1.1/frmts/gtiff/libgeotiff/xtiffio.h

    # libtiff seems to be written in C.
    gdal-2.1.1/frmts/gtiff/libtiff/gdal_libtiff_symbol_rename.h
    gdal-2.1.1/frmts/gtiff/libtiff/t4.h
    gdal-2.1.1/frmts/gtiff/libtiff/tif_config.h
    gdal-2.1.1/frmts/gtiff/libtiff/tif_dir.h
    gdal-2.1.1/frmts/gtiff/libtiff/tif_fax3.h
    gdal-2.1.1/frmts/gtiff/libtiff/tiffconf.h
    gdal-2.1.1/frmts/gtiff/libtiff/tiff.h
    gdal-2.1.1/frmts/gtiff/libtiff/tiffio.h
    gdal-2.1.1/frmts/gtiff/libtiff/tiffiop.h
    gdal-2.1.1/frmts/gtiff/libtiff/tiffvers.h
    gdal-2.1.1/frmts/gtiff/libtiff/tif_predict.h
    gdal-2.1.1/frmts/gtiff/libtiff/uvcode.h

    gdal-2.1.1/frmts/mem/memdataset.h
    gdal-2.1.1/frmts/raw/atlsci_spheroid.h
    gdal-2.1.1/frmts/raw/rawdataset.h
    gdal-2.1.1/frmts/vrt/gdal_vrt.h
    gdal-2.1.1/frmts/vrt/vrtdataset.h
    gdal-2.1.1/gnm/gnm_api.h
    gdal-2.1.1/gnm/gnmgraph.h
    gdal-2.1.1/gnm/gnm.h
    gdal-2.1.1/gnm/gnm_priv.h
    gdal-2.1.1/ogr/ogr_api.h
    gdal-2.1.1/ogr/ograpispy.h
    gdal-2.1.1/ogr/ogr_core.h
    gdal-2.1.1/ogr/ogr_expat.h
    gdal-2.1.1/ogr/ogr_feature.h
    gdal-2.1.1/ogr/ogr_featurestyle.h
    gdal-2.1.1/ogr/ogr_geocoding.h
    gdal-2.1.1/ogr/ogrgeomediageometry.h
    gdal-2.1.1/ogr/ogr_geometry.h
    gdal-2.1.1/ogr/ogr_geos.h
    gdal-2.1.1/ogr/ogrpgeogeometry.h
    gdal-2.1.1/ogr/ogr_p.h
    gdal-2.1.1/ogr/ogr_spatialref.h
    gdal-2.1.1/ogr/ogr_srs_api.h
    gdal-2.1.1/ogr/ogr_srs_esri_names.h
    gdal-2.1.1/ogr/osr_cs_wkt.h
    gdal-2.1.1/ogr/osr_cs_wkt_parser.h
    gdal-2.1.1/ogr/swq.h
    gdal-2.1.1/ogr/ogrsf_frmts/ogr_attrind.h
    gdal-2.1.1/ogr/ogrsf_frmts/ogrsf_frmts.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogreditablelayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogremulatedtransaction.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogr_gensql.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerdecorator.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrlayerpool.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexeddatasource.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrmutexedlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrunionlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/generic/ogrwarpedlayer.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogr_geojson.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonreader.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonutils.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/ogrgeojsonwriter.h

    # libjson seems to be written in C.
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/arraylist.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/bits.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/config.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/debug.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_config.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_c_version.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_inttypes.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object_iterator.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_object_private.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_tokener.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/json_util.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/linkhash.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/printbuf.h
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/symbol_renames.h

    gdal-2.1.1/ogr/ogrsf_frmts/mem/ogr_mem.h
    gdal-2.1.1/port/cpl_atomic_ops.h
    gdal-2.1.1/port/cpl_aws.h
    gdal-2.1.1/port/cpl_config_extras.h
    gdal-2.1.1/port/cpl_config.h
    gdal-2.1.1/port/cpl_conv.h
    gdal-2.1.1/port/cpl_csv.h
    gdal-2.1.1/port/cpl_error.h
    gdal-2.1.1/port/cpl_hash_set.h
    gdal-2.1.1/port/cpl_http.h
    gdal-2.1.1/port/cplkeywordparser.h
    gdal-2.1.1/port/cpl_list.h
    gdal-2.1.1/port/cpl_minixml.h
    gdal-2.1.1/port/cpl_minizip_ioapi.h
    gdal-2.1.1/port/cpl_minizip_unzip.h
    gdal-2.1.1/port/cpl_minizip_zip.h
    gdal-2.1.1/port/cpl_multiproc.h
    # gdal-2.1.1/port/cpl_odbc.h
    gdal-2.1.1/port/cpl_port.h
    gdal-2.1.1/port/cpl_progress.h
    gdal-2.1.1/port/cpl_quad_tree.h
    gdal-2.1.1/port/cpl_sha256.h
    gdal-2.1.1/port/cpl_spawn.h
    gdal-2.1.1/port/cpl_string.h
    gdal-2.1.1/port/cpl_time.h
    gdal-2.1.1/port/cpl_virtualmem.h
    gdal-2.1.1/port/cpl_vsi_error.h
    gdal-2.1.1/port/cpl_vsi.h
    gdal-2.1.1/port/cpl_vsil_curl_priv.h
    gdal-2.1.1/port/cpl_vsi_virtual.h
    gdal-2.1.1/port/cpl_worker_thread_pool.h
    gdal-2.1.1/port/gdal_csv.h
    gdal-2.1.1/frmts/zlib/zlib.h
    gdal-2.1.1/gcore/gdalexif.h
    gdal-2.1.1/gcore/gdal_frmts.h
    gdal-2.1.1/gcore/gdalgeorefpamdataset.h
    gdal-2.1.1/gcore/gdal.h
    gdal-2.1.1/gcore/gdaljp2abstractdataset.h
    gdal-2.1.1/gcore/gdaljp2metadatagenerator.h
    gdal-2.1.1/gcore/gdaljp2metadata.h
    gdal-2.1.1/gcore/gdal_mdreader.h
    gdal-2.1.1/gcore/gdal_pam.h
    gdal-2.1.1/gcore/gdal_priv.h
    gdal-2.1.1/gcore/gdal_proxy.h
    gdal-2.1.1/gcore/gdal_rat.h
    gdal-2.1.1/gcore/gdalsse_priv.h
    gdal-2.1.1/gcore/gdal_version.h
    gdal-2.1.1/gcore/mdreader/reader_digital_globe.h
    )

include_directories(
    gdal-2.1.1/alg/

    # in-source build seems to populate `gdal-2.1.1/apps/` with `*.c`,
    # but it has already before that `*.cpp` & `*.h` (I'm not sure about all of them).
    gdal-2.1.1/apps/

    gdal-2.1.1/frmts/gtiff/

    # libgeotiff seems to be written in C.
    gdal-2.1.1/frmts/gtiff/libgeotiff/

    # libtiff seems to be written in C.
    gdal-2.1.1/frmts/gtiff/libtiff/

    gdal-2.1.1/frmts/mem/
    gdal-2.1.1/frmts/raw/
    gdal-2.1.1/frmts/vrt/
    gdal-2.1.1/gnm/
    gdal-2.1.1/ogr/
    gdal-2.1.1/ogr/ogrsf_frmts/
    gdal-2.1.1/ogr/ogrsf_frmts/generic/
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/
    gdal-2.1.1/ogr/ogrsf_frmts/xplane/

    # libjson seems to be written in C.
    gdal-2.1.1/ogr/ogrsf_frmts/geojson/libjson/

    gdal-2.1.1/port/
    gdal-2.1.1/gcore/
    gdal-2.1.1/gcore/mdreader/
    gdal-2.1.1/ogr/ogrsf_frmts/mem/
    gdal-2.1.1/frmts/zlib/
    )

add_library(GDAL_211 STATIC
    ${GDAL_211_SOURCE}
    ${GDAL_211_HEADERS}
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

