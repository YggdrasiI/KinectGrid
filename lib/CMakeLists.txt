add_subdirectory(cJSON)

if(MYBLOB)
	add_subdirectory(blobtree)
else(MYBLOB)
	add_subdirectory(cvblobslib)
endif(MYBLOB)
