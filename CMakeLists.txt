# Der Projektname
project(MMTTlinux)

# Minimal benötigte CMake-Version wenn z.B. bestimmte CMake-Kommandos benutzt werden
cmake_minimum_required(VERSION 2.6)

# Benötigte oder optionale Pakete. Hier können z.B. Qt4 oder Boost stehen
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



set(EXTRA_C_FLAGS_DEBUG "-g")

include_directories(
		${CMAKE_SOURCE_DIR}/include
		${Freenect_INCLUDE_DIR}
	)
link_directories (
	${Freenect_LIBRARY}
	${Onion_LIBRARY}
	${MMTTlinux_BINARY_DIR}/lib/cvblobslib
	${Boost_LIBRARY_DIRS}
	) 


#SET(LIBS ${LIBS} ${OpenCV_LIBS} ${Freenect_LIBS})

# CMake soll auch in diesen Verzeichnissen weitersuchen
add_subdirectory(lib)
add_subdirectory(src)

# Es sollen auch einige Dateien installiert werden, z.B. Bilder oder Übersetzungen
#install(FILES ${CMAKE_SOURCE_DIR}/html/jquery* html/mmtt_script.js DESTINATION html)

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


#add_dependencies(main copy_files "html/*.js" "${CMAKE_CURRENT_BINARY_DIR}/html" )
