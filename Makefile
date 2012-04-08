all: main

PROGRAM = bin/main 
CFLAGS = -fPIC -g -Wall `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
INCLUDE = -I/usr/local/include/libfreenect -Icvblobslib -I./include
FREE_LIBS = -L/usr/local/lib -lfreenect
#TESTFLAGS= -march=armv7-a -mtune=cortex-a8 -mfpu=neon -O3

SOURCEFILES = \
	src/main.cpp \
	src/tracker.cpp

main: $(SOURCEFILES)
	$(CXX) $(INCLUDE) $(CFLAGS) $(TESTFLAGS) $(SOURCEFILES) cvblobslib/*.cpp -o $(PROGRAM)  $(LIBS) $(FREE_LIBS)


clean:
	rm -rf *.o main

