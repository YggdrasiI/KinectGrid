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
#find_package(OtherPackage OPTIONAL)


include_directories(
		${CMAKE_SOURCE_DIR}/include
		${Freenect_INCLUDE_DIR}
	)
link_directories (
	${Freenect_LIBRARY}
	${Onion_LIBRARY}
	${MMTTlinux_BINARY_DIR}/lib/cvblobslib
	) 


#SET(LIBS ${LIBS} ${OpenCV_LIBS} ${Freenect_LIBS})

# CMake soll auch in diesen Verzeichnissen weitersuchen
add_subdirectory(lib)
add_subdirectory(src)

# Es sollen auch einige Dateien installiert werden, z.B. Bilder oder Übersetzungen
#install(FILES img/icon.png DESTINATION img)
