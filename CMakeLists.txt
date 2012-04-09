# Der Projektname
project(MMTTlinux)

# Minimal benötigte CMake-Version wenn z.B. bestimmte CMake-Kommandos benutzt werden
cmake_minimum_required(VERSION 2.6)

# Benötigte oder optionale Pakete. Hier können z.B. Qt4 oder Boost stehen
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(OpenCV REQUIRED)
find_package(Freenect REQUIRED)
#find_package(OtherPackage OPTIONAL)


include_directories(
		${CMAKE_SOURCE_DIR}/include
		${FREENECT_INCLUDE_DIR}
	)
link_directories (
	${FREENECT_LIBRARY}
	${MMTTlinux_BINARY_DIR}/lib/cvblobslib
	) 


#SET(LIBS ${LIBS} ${OpenCV_LIBS} ${FREENECT_LIBS})

# CMake soll auch in diesen Verzeichnissen weitersuchen
add_subdirectory(lib/cvblobslib)
add_subdirectory(src)

# Es sollen auch einige Dateien installiert werden, z.B. Bilder oder Übersetzungen
#install(FILES img/icon.png DESTINATION img)
