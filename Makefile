install: dependencies onion blobdetection
	@test -d "build" || mkdir "build"
	cd build && cmake .. && make
	@echo "\n\tKinectGrid compiled. To start it, i.e. use\n\n" \
		"\t\tcd bulid; bin/main [--no-kinect] or" \
		"\t\tcd bulid; bin/main --help or"

run:
	cd build && bin/main

run_no_kinect:
	cd build && bin/main --no-kinect

dependencies: 
	@echo "\tInstall dependencies on Ubuntu 16.04\n\n" \
		"\tThis make target will not be shown again\n" \
		"\tuntil you delete .skip_deps_install\n\n" \
		"\tSee DEPENDENCIES to install them on other distributions manually.\n\n"
	@test -f .skip_deps_install || make .skip_deps_install

.skip_deps_install:
	@touch .skip_deps_install
	sudo apt-get install \
		libfreenect-dev \
		liblo-dev libboost-regex-dev libboost-system-dev \
		libpng-dev libjpeg-turbo8-dev \
		libopencv-core-dev libopencv-imgproc-dev libopencv-highgui-dev


onion: lib/onion/lib/libonion.so


lib/onion/lib/libonion.so:
	echo "Clone and build Onion library"
	cd 3rdparty && \
		( test -d onion || git clone https://github.com/davidmoreno/onion.git)
	cd 3rdparty/onion && \
		( test -d build || mkdir build )
	cd 3rdparty/onion/build && \
		cmake -DCMAKE_INSTALL_PREFIX=../../../lib/onion -DONION_EXAMPLES=0 -DONION_USE_SSL=0 -DONION_USE_SQLITE3=0 -DONION_USE_SYSTEMD=0 -DONION_USE_PAM=0 -DONION_USE_PNG=1 .. && \
		make && \
		make install

blobdetection: lib/blobdetection/lib/libthreshtree.so

lib/blobdetection/lib/libthreshtree.so:
	echo "Clone and build blobdetection library"
	cd 3rdparty && \
		( test -d blobdetection || git clone https://github.com/YggdrasiI/blobdetection.git)
	cd 3rdparty/blobdetection && \
		( test -d build || mkdir build )
	cd 3rdparty/blobdetection/build && \
		cmake -DCMAKE_INSTALL_PREFIX=../../../lib/blobdetection -DWITH_EXAMPLES=0 .. && \
		make && \
		make install

# Omit remove of .skip_deps_install on Ctrl-c signal
.PRECIOUS: .skip_deps_install

