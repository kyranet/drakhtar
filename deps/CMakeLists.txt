set(SUPPORTED_LANGUAGES
	"en"
	"en-US"
	"es"
	"es-ES")

foreach(language ${SUPPORTED_LANGUAGES})
	# Convert the string to uppercase (en-US -> EN-US, es-ES -> ES-ES):
	string(TOUPPER ${language} __DIRECTORY__)

	# Replace "-" with "_" (EN-US -> EN_US, ES-ES -> ES_ES):
	string(REPLACE "-" "_" __DIRECTORY__ ${__DIRECTORY__})

	# Define the option:
	set(I18N_LANGUAGE_${__DIRECTORY__} ON)
endforeach()


add_subdirectory(drakhtar-i18n)
add_subdirectory(drakhtar-telemetry)

# Workaround for MSVC development libraries in the University's laboratories, where access to
# C:\ or C:\MinGW are forbidden. This serves to let anybody compile under restricted access.
# If the generator is MSVC, try to link the libraries.
if (MSVC)
	file(GLOB SDL2_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2-*")
	file(GLOB SDL2_IMAGE_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2_image-*")
	file(GLOB SDL2_MIXER_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2_mixer-*")
	file(GLOB SDL2_TTF_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2_ttf-*")
	file(GLOB SDL2_NET_DIR "${CMAKE_SOURCE_DIR}/deps/SDL2_net-*")

	set(ENV{SDL2DIR} ${SDL2_DIR})
	set(ENV{SDL2IMAGEDIR} ${SDL2_IMAGE_DIR})
	set(ENV{SDL2MIXERDIR} ${SDL2_MIXER_DIR})
	set(ENV{SDL2NETDIR} ${SDL2_NET_DIR})
	set(ENV{SDL2TTFDIR} ${SDL2_TTF_DIR})

	file(GLOB_RECURSE DEPENDENCY_DLLS
		"${SDL2_TTF_DIR}/lib/x64/*.dll"
		"${SDL2_IMAGE_DIR}/lib/x64/*.dll"
		"${SDL2_MIXER_DIR}/lib/x64/*.dll"
		"${SDL2_NET_DIR}/lib/x64/*.dll"
		"${SDL2_DIR}/lib/x64/*.dll"
		)

	foreach (dll ${DEPENDENCY_DLLS})
		get_filename_component(dll_fn ${dll} NAME)
		configure_file(${dll} dll/${dll_fn} COPYONLY)
	endforeach ()

	set_target_properties(i18n PROPERTIES RUNTIME_OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/src)

	set_target_properties(telemetry PROPERTIES RUNTIME_OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/src)
endif ()

add_executable(Dependencies IMPORTED GLOBAL)
set_target_properties(Dependencies PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/DO_NOT_USE)
