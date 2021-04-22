all: build

mkdir_build:
	rm -rf build
	mkdir -p build

build: mkdir_build
	cmake -B build
	cd build
	make -j -C build

debug: mkdir_build
	cmake -DCMAKE_BUILD_TYPE=Debug -B build
	cd build
	make -j -C build

run:
	cd build/src; ./drakhtar


.PHONY: mkdir_build
