# myblob library settings

include_directories( ${CMAKE_SOURCE_DIR}/lib/myblob )
link_directories( ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/lib/myblob )

set(myblob_SRCS myblob.c)
add_library (myblob SHARED ${myblob_SRCS})

#target_link_libraries(myblob OTHERLIBS)

install(TARGETS myblob 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)
