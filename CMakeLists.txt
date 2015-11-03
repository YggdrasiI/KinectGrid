project(KinectGrid)
cmake_minimum_required(VERSION 2.6)
# Clipping require modified libfreenect
OPTION(LIBFREENECT_OPT_CLIPPING "Enable clipping option. Require modified libfreenect driver." OFF)
OPTION(MYBLOB "Use own lib for blob detection" ON)
OPTION(CENTER_ADJUSTMENT "Extended search of maximal depth of blob and better midpoint detection." ON)
OPTION(WEB_DISPLAY_USES_JPEG "Encode images as JPEG instead of PNG (faster encoding)." ON)

#set(PG_FLAGS "-O2 -pg -g -fno-omit-frame-pointer -DNDEBUG -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls ")

set(EXTRA_C_FLAGS "${PG_FLAGS}")
set(EXTRA_C_FLAGS_DEBUG "")
set(EXTRA_CXX_FLAGS "-std=c++0x ${PG_FLAGS}")
set(EXTRA_CXX_FLAGS_DEBUG "-std=c++0x ")

## required and optional packages
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_MODULE_PATH})
find_package(Freenect REQUIRED)
find_package(Onion REQUIRED)

#set(OpenCV_DIR "/usr/include/opencv")
#find_package(OpenCV REQUIRED)
set(OpenCV_INCLUDE_DIR "/usr/include/opencv")
set(OpenCV_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu")
set(OpenCV_LIBS "opencv_core -lopencv_highgui -lopencv_imgproc") # Available in 2.4.3: calib3d contrib core features2d flann gpu highgui imgproc legacy ml objdetect video

set(Boost_USE_STATIC_LIBS        OFF)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#set(Boost_DEBUG TRUE)
find_package(Boost COMPONENTS regex system REQUIRED)
#find_package(Boost COMPONENTS signals2 REQUIRED)# not required, it is just a header.

## end required and optional packages

## set env variable for libfreenect
if(LIBFREENECT_OPT_CLIPPING)
	message(STATUS "Optional clipping is on.")
	add_definitions(-DLIBFREENECT_OPT_CLIPPING)
else(LIBFREENECT_OPT_CLIPPING)
	message(STATUS "Optional clipping is off.")
endif()

if(MYBLOB)
	message(STATUS "Use libblobtree for blob detection.")
	# Use add_definition on top level
	# to propagate it to all subdirs.
	add_definitions(-DMYBLOB)
	# Enable barycenter option for blobdetection lib.
	add_definitions(-DBLOB_BARYCENTER)
else(MYBLOB)
	message(STATUS "Use cvblobslib for blob detection.")
endif(MYBLOB)
## end set env variables

if(CENTER_ADJUSTMENT)
	add_definitions(-DCENTER_ADJUSTMENT)
endif(CENTER_ADJUSTMENT)

## add include dirs and lib dirs of above packages
include_directories(
		${CMAKE_SOURCE_DIR}/include
		${Freenect_INCLUDE_DIR}
		/usr/include/libusb-1.0
		${Boost_INCLUDE_DIR}
		${OpenCV_INCLUDE_DIR}
	)
link_directories (
	${Freenect_LIBRARY_PATH}
	${OpenCV_LIBRARY_PATH}
	${Onion_LIBRARY_PATH}
	${${CMAKE_PROJECT_NAME}_BINARY_DIR}/lib/cvblobslib
	${Boost_LIBRARY_DIRS}
	) 
## end add include dis and lib dirs of above packages

# CMake soll auch in diesen Verzeichnissen weitersuchen
add_subdirectory(lib)
add_subdirectory(src)

## Copy html folder to build directory.

file(GLOB WEBSERVER_FILES
	  "html/*.*"
		)
file(COPY ${WEBSERVER_FILES}
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/html"
	)
