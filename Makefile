all: main

PROGRAM = bin/main 
CFLAGS = -fPIC -g `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
INCLUDE = -I/usr/local/include/libfreenect -I3rdparty/cvblobslib -I3rdparty/cJSON -I./include
FREE_LIBS = -L/usr/local/lib -lfreenect
#TESTFLAGS= -march=armv7-a -mtune=cortex-a8 -mfpu=neon -O3

SOURCEFILES = \
	src/main.cpp \
	src/tracker.cpp \
	3rdparty/cJSON/cJSON.c

main: $(SOURCEFILES)
	$(CXX) $(INCLUDE) $(CFLAGS) $(TESTFLAGS) $(SOURCEFILES) 3rdparty/cvblobslib/*.cpp -o $(PROGRAM)  $(LIBS) $(FREE_LIBS)


clean:
	rm -rf *.o main

