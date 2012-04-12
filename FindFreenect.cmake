# Search libfreenect header and libary
find_path(Freenect_INCLUDE_DIR
	NAMES
		libfreenect.h
	PATHS
		/usr/include/libfreenect
		/usr/local/include/libfreenect
		/opt/local/include/libfreenect
	PATH_SUFFIXES
		libfreenect
)

find_library(Freenect_LIBRARY
	NAMES
		freenect
	PATHS
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/opt/local/lib
)

if(Freenect_INCLUDE_DIR AND Freenect_LIBRARY)
	set(Freenect_FOUND TRUE)
	set(Freenect_LIBS freenect)
else(Freenect_INCLUDE_DIR AND Freenect_LIBRARY)
	set(Freenect_FOUND FALSE)
endif(Freenect_INCLUDE_DIR AND Freenect_LIBRARY)

if(Freenect_FOUND)
	message(STATUS " Lib: ${Freenect_LIBS}")
	message(STATUS " - Includes: ${Freenect_INCLUDE_DIR}")
	message(STATUS " - Libraries: ${Freenect_LIBRARY}")
else(Freenect_FOUND)
	message(FATAL_ERROR "Could not find libfreenect")
endif(Freenect_FOUND)


