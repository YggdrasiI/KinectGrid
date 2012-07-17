add_subdirectory(cJSON)

if(MYBLOB)
	message(STATUS "Use libmyblob for blob detection.")
	add_subdirectory(myblob)
else(MYBLOB)
	message(STATUS "Use cvblobslib for blob detection.")
	add_subdirectory(cvblobslib)
endif(MYBLOB)
