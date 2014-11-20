## extra include directories
include_directories(
	${CMAKE_SOURCE_DIR}/lib/cvblobslib
	${CMAKE_SOURCE_DIR}/lib/blobdetection
	${CMAKE_SOURCE_DIR}/lib/TUIO
	${CMAKE_SOURCE_DIR}/lib/oscpack
	${CMAKE_SOURCE_DIR}/lib/onion/include
	${Boost_INCLUDE_DIR}
	)
## end extra include directories

## json files
set(json_SRCS
	cJSON.c
	JsonConfig.cpp	
	SettingKinect.cpp
	)
## end json files

## http server
#add_custom_target(server)
set(server_SRCS
	OnionServer.cpp
	index_html.c
	#kinect_settings_js.c
	)

# create sourcefile from html template
add_custom_command(
	OUTPUT index_html.c
	COMMAND ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/index.html
	${CMAKE_CURRENT_BINARY_DIR}/index_html.c
	DEPENDS ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/index.html
	)
#add_custom_command(
#	OUTPUT json_settings_editor_js.c
#	COMMAND ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/json_settings_editor.js
#	${CMAKE_CURRENT_BINARY_DIR}/json_settings_editor_js.c
#	DEPENDS ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/json_settings_editor.js
#	)
#add_custom_command(
#	OUTPUT kinect_settings_js.c
#	COMMAND ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/kinect_settings.js
#	${CMAKE_CURRENT_BINARY_DIR}/kinect_settings_js.c
#	DEPENDS ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/kinect_settings.js
#	)

add_library (server SHARED ${server_SRCS})
## end http server

## Tuio server
set(osc_SRCS
 ../lib/oscpack/osc/OscTypes.cpp 
 ../lib/oscpack/osc/OscOutboundPacketStream.cpp
 ../lib/oscpack/osc/OscReceivedElements.cpp
 ../lib/oscpack/osc/OscPrintReceivedElements.cpp
 ../lib/oscpack/ip/posix/NetworkingUtils.cpp
 ../lib/oscpack/ip/posix/UdpSocket.cpp
)
set(tuio_SRCS
	MyTuioServer.cpp
	MyTuioServer25D.cpp
	../lib/TUIO/TuioServer.cpp
	../lib/TUIO/TuioServer25D.cpp
	../lib/TUIO/TuioTime.cpp
	${osc_SRCS}
	)

## For oscpack
# should be either OSC_HOST_BIG_ENDIAN or OSC_HOST_LITTLE_ENDIAN
# Apple: OSC_HOST_BIG_ENDIAN
# Win32: OSC_HOST_LITTLE_ENDIAN
# i386 Linux: OSC_HOST_LITTLE_ENDIAN
#set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -DOSC_HOST_LITTLE_ENDIAN")
add_definitions(-DOSC_HOST_LITTLE_ENDIAN)

add_library (tuio SHARED ${tuio_SRCS})
## end tuio server

## main executable
set(main_SRCS
	main.cpp
	Tracker.cpp
	MyFreenectDevice.cpp
	ImageAnalysis.cpp
	${json_SRCS}
	)

if(MYBLOB)
	set(main_SRCS ${main_SRCS} Tracker2.cpp)
else(MYBLOB)
	set(main_SRCS ${main_SRCS} TrackerCvBlobsLib.cpp)
endif(MYBLOB)
	
# Die auführbare Datei. Anstatt der Variablen können
# auch noch zusätzliche Dateien angegeben werden
add_executable (main ${main_SRCS} )

# Die ausführbare Datei wird gegen diese Bibliotheken gelinkt.
target_link_libraries(main server tuio ${OpenCV_LIBS} ${Freenect_LIBS} ${Onion_LIBS} ${Boost_LIBRARIES})
#add_dependencies(main server)
if(MYBLOB)
	target_link_libraries(main threshtree)
else(MYBLOB)
	target_link_libraries(main cvblobslib)
endif(MYBLOB)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#g++ flags 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${EXTRA_CXX_FLAGS_DEBUG}")

# Das Programm soll in den folgenden Unterordnern
# installiert werden.
install(TARGETS main 
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	)
## end main executable
