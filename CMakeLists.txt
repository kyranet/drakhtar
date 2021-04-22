cmake_minimum_required(VERSION 3.8)

project(drakhtar)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

add_subdirectory(deps)
add_subdirectory(assets)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wconversion -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_WARNING_LEVEL 4)

    # Replace the default /W flag to /W4 for higher verbosity.
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif ()
endif ()

# Print the compiler flags for debugging purposes.
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")

# Set the cmake module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${drakhtar_SOURCE_DIR}/cmake/")

# Find all SDL2 libraries.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(drakhtar ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${DEPENDENCY_INCLUDES})

# Add all .cpp source files to the drakhtar executable.
file(GLOB_RECURSE drakhtar_SOURCES "Drakhtar/*.cpp")
add_executable(drakhtar ${drakhtar_SOURCES})
target_include_directories(drakhtar
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/deps/drakhtar-telemetry/include>)

# Copy all assets.
include_directories(Drakhtar)

add_custom_command(
    TARGET drakhtar POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Assets>
    $<TARGET_FILE_DIR:drakhtar>
)

if (MSVC)
    add_custom_command(
        TARGET drakhtar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Dependencies>/dll
        $<TARGET_FILE_DIR:drakhtar>
    )
endif ()

# Link the libraries and install them.
target_link_libraries(drakhtar ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
install(TARGETS drakhtar
    CONFIGURATIONS Debug
    RUNTIME DESTINATION ${drakhtar_SOURCE_DIR}/bin/debug)
install(TARGETS drakhtar
    CONFIGURATIONS Release
    RUNTIME DESTINATION ${drakhtar_SOURCE_DIR}/bin/release)
