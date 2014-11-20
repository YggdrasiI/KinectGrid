add_subdirectory(cJSON)

if(MYBLOB)
	add_subdirectory(blobdetection)
else(MYBLOB)
	add_subdirectory(cvblobslib)
endif(MYBLOB)
