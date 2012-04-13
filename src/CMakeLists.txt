# Zusätzliche include-Verzeichnisse
include_directories(
	${CMAKE_SOURCE_DIR}/lib/cvblobslib
	)

# Hier wird definiert, welche Quellcodedateien zur Programmdatei dazugehören.
# Bei großen Projekten ist eine logische Unterteilung sinnvoll.
set(json_SRCS
	cJSON.c
	JsonConfig.cpp	
	SettingKinect.cpp
	SettingMMTT.cpp
	)


set(main_SRCS
	main.cpp
	Tracker.cpp
	MyFreenectDevice.cpp
	ImageAnalysis.cpp
	${json_SRCS}
	)

## http server
#add_custom_target(server)
set(server_SRCS
	OnionServer.cpp
	index_html.c
#	mmtt_script_js.c
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

# Die auführbare Datei. Anstatt der Variablen können
# auch noch zusätzliche Dateien angegeben werden
add_executable (main ${main_SRCS} )

# Die ausführbare Datei wird gegen diese Bibliotheken gelinkt.
target_link_libraries(main cvblobslib server ${OpenCV_LIBS} ${Freenect_LIBS} ${Onion_LIBS})
#add_dependencies(main server)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#debug flag will be ignored?!
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})

# Das Programm soll in den folgenden Unterordnern
# installiert werden.
install(TARGETS main 
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	)
