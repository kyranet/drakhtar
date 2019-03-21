cmake_minimum_required(VERSION 3.10)

project(drakhtar)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${drakhtar_SOURCE_DIR}/cmake/")
set(BIN_DIR ${drakhtar_SOURCE_DIR}/bin)

if(NOT BUILD_LOCAL)
  set(BUILD_LOCAL 1 CACHE PATH "Assign this to 1 to use a local /deps/ folder.")
endif()

if(BUILD_LOCAL EQUAL 1)
  file(GLOB SDL2_DIR "${drakhtar_SOURCE_DIR}/deps/SDL2-*")
  file(GLOB SDL2_IMAGE_DIR "${drakhtar_SOURCE_DIR}/deps/SDL2_image-*")
  file(GLOB SDL2_TTF_DIR "${drakhtar_SOURCE_DIR}/deps/SDL2_ttf-*")
  file(GLOB SDL2_MIXER_DIR "${drakhtar_SOURCE_DIR}/deps/SDL2_mixer-*")

  message("SDL2_DIR = ${SDL2_DIR}")
  message("SDL2_IMAGE_DIR = ${SDL2_IMAGE_DIR}")
  message("SDL2_TTF_DIR = ${SDL2_TTF_DIR}")
  message("SDL2_MIXER_DIR = ${SDL2_MIXER_DIR}")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

file(COPY audio DESTINATION .)
file(COPY fonts DESTINATION .)
file(COPY images DESTINATION .)
file(COPY dialog DESTINATION .)

include_directories(Drakhtar)

file(GLOB_RECURSE drakhtar_SOURCES "Drakhtar/*.cpp")
add_executable(drakhtar ${drakhtar_SOURCES})

file(GLOB_RECURSE DEPENDENCY_DLLS
  "${SDL2_TTF_DIR}/*.dll"
  "${SDL2_MIXER_DIR}/*.dll"
  "${SDL2_IMAGE_DIR}/*.dll"
  "${SDL2_DIR}/*.dll"
)
file(COPY ${DEPENDENCY_DLLS} DESTINATION "${BIN_DIR}")

target_link_libraries(drakhtar ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

install(TARGETS drakhtar RUNTIME DESTINATION ${BIN_DIR})
