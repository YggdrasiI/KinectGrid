project(KinectGrid)
cmake_minimum_required(VERSION 2.6)
# Clipping require modified libfreenect
OPTION(LIBFREENECT_OPT_CLIPPING "Enable clipping option. Require modified libfreenect driver." OFF)

set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -g")
set(EXTRA_C_FLAGS_DEBUG "${EXTRA_C_FLAGS_DEBUG} ")

## required and optional packages
#set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules ${CMAKE_SOURCE_DIR})
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(OpenCV REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(Freenect REQUIRED)
find_package(Onion REQUIRED)

set(Boost_USE_STATIC_LIBS        OFF)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#set(Boost_DEBUG TRUE)
find_package(Boost COMPONENTS signals REQUIRED)

#find_package(OtherPackage OPTIONAL)

## end required and optional packages

## set env variables
if(LIBFREENECT_OPT_CLIPPING)
	message(STATUS "Optional clipping is on.")
	add_definitions(-DLIBFREENECT_OPT_CLIPPING)
	#set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -DLIBFREENECT_OPT_CLIPPING")
else(LIBFREENECT_OPT_CLIPPING)
	message(STATUS "Optional clipping is off.")
endif()
## end set env variables

## add include dirs and lib dirs of above packages
include_directories(
		${CMAKE_SOURCE_DIR}/include
		${Freenect_INCLUDE_DIR}
	)
link_directories (
	${Freenect_LIBRARY}
	${Onion_LIBRARY}
	${${CMAKE_PROJECT_NAME}_BINARY_DIR}/lib/cvblobslib
	${Boost_LIBRARY_DIRS}
	) 
## end add include dis and lib dirs of above packages



#SET(LIBS ${LIBS} ${OpenCV_LIBS} ${Freenect_LIBS})

# CMake soll auch in diesen Verzeichnissen weitersuchen
add_subdirectory(lib)
add_subdirectory(src)

## Copy html folder to build directory.
file(COPY html/ DESTINATION html PATTERN kinectgrid_settings.js EXCLUDE )

macro(copy_files GLOBPAT DESTINATION)
  file(GLOB COPY_FILES
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLOBPAT})
  add_custom_target(copy ALL
    COMMENT "Copying files: ${GLOBPAT}")

  foreach(FILENAME ${COPY_FILES})
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}")
    set(DST "${DESTINATION}/${FILENAME}")

    add_custom_command(
      TARGET copy
      COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST}
      )
  endforeach(FILENAME)
endmacro(copy_files)
## end TODO

#add_dependencies(main copy_files "html/*.js" "${CMAKE_CURRENT_BINARY_DIR}/html" )
