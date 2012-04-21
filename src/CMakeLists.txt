## extra include directories
include_directories(
	${CMAKE_SOURCE_DIR}/lib/cvblobslib
	${CMAKE_SOURCE_DIR}/lib/TUIO
	${CMAKE_SOURCE_DIR}/lib/oscpack
	${Boost_INCLUDE_DIR}
	)
## end extra include directories

## json files
set(json_SRCS
	cJSON.c
	JsonConfig.cpp	
	SettingKinect.cpp
	SettingMMTT.cpp
	)
## end json files

## http server
#add_custom_target(server)
set(server_SRCS
	OnionServer.cpp
	index_html.c
	mmtt_settings_js.c
	)

# create sourcefile from html template
add_custom_command(
	OUTPUT index_html.c
	COMMAND ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/index.html
	${CMAKE_CURRENT_BINARY_DIR}/index_html.c
	DEPENDS ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/index.html
	)
add_custom_command(
	OUTPUT mmtt_script_js.c
	COMMAND ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/mmtt_script.js
	${CMAKE_CURRENT_BINARY_DIR}/mmtt_script_js.c
	DEPENDS ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/mmtt_script.js
	)
add_custom_command(
	OUTPUT mmtt_settings_js.c
	COMMAND ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/mmtt_settings.js
	${CMAKE_CURRENT_BINARY_DIR}/mmtt_settings_js.c
	DEPENDS ${OTEMPLATE} ${CMAKE_SOURCE_DIR}/html/mmtt_settings.js
	)

add_library (server SHARED ${server_SRCS})
#add_dependencies(server index_html.c mmtt_script_js.c)
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
	../lib/TUIO/TuioServer.cpp
	../lib/TUIO/TuioTime.cpp
	${osc_SRCS}
	)

## For oscpack
# should be either OSC_HOST_BIG_ENDIAN or OSC_HOST_LITTLE_ENDIAN
# Apple: OSC_HOST_BIG_ENDIAN
# Win32: OSC_HOST_LITTLE_ENDIAN
# i386 LinuX: OSC_HOST_LITTLE_ENDIAN
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -DOSC_HOST_LITTLE_ENDIAN")

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

# Die auführbare Datei. Anstatt der Variablen können
# auch noch zusätzliche Dateien angegeben werden
add_executable (main ${main_SRCS} )

# Die ausführbare Datei wird gegen diese Bibliotheken gelinkt.
target_link_libraries(main cvblobslib server tuio ${OpenCV_LIBS} ${Freenect_LIBS} ${Onion_LIBS} ${Boost_LIBRARIES})
#add_dependencies(main server)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#g++ flags 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS}")

# Das Programm soll in den folgenden Unterordnern
# installiert werden.
install(TARGETS main 
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	)
## end main executable
