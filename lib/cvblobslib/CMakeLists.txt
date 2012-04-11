# Wenn diese Bibliothek zusätzliche includes benötigt, müssen diese
# natürlich eingefügt werden.

# Hier wird definiert, welche Quellcodedateien zur Bibliothek dazugehören.
# Bei großen Projekten ist eine logische Unterteilung sinnvoll.
set(cvblobslib_SRCS
		Blob.cpp
		BlobExtraction.cpp
		BlobResult.cpp
)

# Es wird festgelegt, dass es sich um eine gemeinsam genutzt Bibliothek
# handelt. Um eine statische Bibliothek zu bekommen, wird
# SHARED durch STATIC ersetzt.
add_library (cvblobslib SHARED ${cvblobslib_SRCS})

# Wenn nötig können auch Bibliotheken gegen andere gelinkt werden.
target_link_libraries(cvblobslib
	${OpenCV_LIBS} ${LIBFREENECT_LIBS}
)

install(TARGETS cvblobslib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)
