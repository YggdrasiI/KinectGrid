all: test

CFLAGS=-fPIC -g -Wall `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
INCLUDE = -I/usr/local/include/libfreenect -Icvblobslib
FREE_LIBS = -L/usr/local/lib -lfreenect
#TESTFLAGS= -march=armv7-a -mtune=cortex-a8 -mfpu=neon -O3

SOURCEFILES = \
	src/main.cpp \
	cvblobslib/BlobResult.cpp

test:  $(SOURCEFILES)
	$(CXX) $(INCLUDE) $(CFLAGS) $(TESTFLAGS) $(SOURCEFILES) -o $@  $(LIBS) $(FREE_LIBS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(TESTFLAGS) $< -o $@

clean:
	rm -rf *.o test

