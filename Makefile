all: build

mkdir_build:
	rm -rf build
	mkdir -p build

build: mkdir_build
	cd build; cmake -j -- ..
	make -C build

build_ninja: mkdir_build
	cd build; cmake -GNinja -j -- ..
	ninja -C build

debug: mkdir_build
	cd build; cmake -DCMAKE_BUILD_TYPE=Debug -j -- ..
	make -C build

debug_ninja: mkdir_build
	cd build; cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -j -- ..
	ninja -C build

run:
	cd build; ./Drakhtar


.PHONY: mkdir_build
