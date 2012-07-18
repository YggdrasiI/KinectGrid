add_subdirectory(cJSON)

if(MYBLOB)
	add_subdirectory(myblob)
else(MYBLOB)
	add_subdirectory(cvblobslib)
endif(MYBLOB)
