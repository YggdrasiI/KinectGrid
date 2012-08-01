# blobtree library settings

include_directories( ${CMAKE_SOURCE_DIR}/lib/blobtree )
link_directories( ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/lib/blobtree )

set(blobtree_SRCS blobtree.c)
add_library (blobtree SHARED ${blobtree_SRCS})

#target_link_libraries(blobtree OTHERLIBS)

install(TARGETS blobtree 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)
