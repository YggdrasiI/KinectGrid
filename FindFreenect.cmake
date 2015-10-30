# Search libfreenect header and libary
find_path(Freenect_INCLUDE_DIR
	NAMES
		libfreenect.h
	PATHS
		/usr/include/libfreenect
		/usr/local/include/libfreenect
		/opt/local/include/libfreenect
		#PATH_SUFFIXES
		#libfreenect
)

find_path(Freenect_LIBRARY_PATH
	NAMES
		libfreenect.so
	PATHS
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/opt/local/lib
)

if(Freenect_INCLUDE_DIR AND Freenect_LIBRARY_PATH)
	set(Freenect_FOUND TRUE)
	set(Freenect_LIBS freenect)
else(Freenect_INCLUDE_DIR AND Freenect_LIBRARY_PATH)
	set(Freenect_FOUND FALSE)
endif(Freenect_INCLUDE_DIR AND Freenect_LIBRARY_PATH)

if(Freenect_FOUND)
	message(STATUS " Lib: freenect")
	message(STATUS " - Includes: ${Freenect_INCLUDE_DIR}")
	message(STATUS " - Link: ${Freenect_LIBS}")
	message(STATUS " - Library path: ${Freenect_LIBRARY_PATH}")
else(Freenect_FOUND)
	message(FATAL_ERROR "Could not find libfreenect")
endif(Freenect_FOUND)


