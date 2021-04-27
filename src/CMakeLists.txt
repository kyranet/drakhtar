# Find all SDL2 libraries.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(drakhtar ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${DEPENDENCY_INCLUDES})

# Add all .cpp source files to the drakhtar executable.
set(DRAKHTAR_SOURCES
	"main.cpp"
	"Controllers/AIController.cpp"
	"Controllers/PlayerController.cpp"
	"Controllers/UnitsController.cpp"
	"Controllers/Handlers/PlayerHandler.cpp"
	"EventListeners/ButtonListener.cpp"
	"EventListeners/DialogSceneOnClick.cpp"
	"EventListeners/EventListener.cpp"
	"EventListeners/ListenerOnClick.cpp"
	"EventListeners/ListenerOnHover.cpp"
	"EventListeners/SkillButtonListener.cpp"
	"EventListeners/StatBoxListener.cpp"
	"EventListeners/StoreListener.cpp"
	"GameObjects/Battalion.cpp"
	"GameObjects/Board.cpp"
	"GameObjects/Box.cpp"
	"GameObjects/Button.cpp"
	"GameObjects/ButtonText.cpp"
	"GameObjects/CreditText.cpp"
	"GameObjects/Dialog.cpp"
	"GameObjects/DialogScene.cpp"
	"GameObjects/GameObject.cpp"
	"GameObjects/GameOverPanel.cpp"
	"GameObjects/HealthBar.cpp"
	"GameObjects/OptionsMenu.cpp"
	"GameObjects/Pause.cpp"
	"GameObjects/RecruitmentStat.cpp"
	"GameObjects/Skill.cpp"
	"GameObjects/SkillButton.cpp"
	"GameObjects/SkillDescriptionBox.cpp"
	"GameObjects/Text.cpp"
	"GameObjects/TurnBar.cpp"
	"GameObjects/TutorialBox.cpp"
	"GameObjects/TutorialText.cpp"
	"GameObjects/Unit.cpp"
	"GameObjects/UnitDescriptionBox.cpp"
	"GameObjects/Base/Sequence.cpp"
	"GameObjects/Commanders/Abeizhul.cpp"
	"GameObjects/Commanders/Commander.cpp"
	"GameObjects/Commanders/Dreilay.cpp"
	"GameObjects/Commanders/RedValar.cpp"
	"GameObjects/Commanders/Sheissah.cpp"
	"GameObjects/Commanders/Thassa.cpp"
	"GameObjects/Commanders/Valar.cpp"
	"GameObjects/Commanders/Zamdran.cpp"
	"Managers/AudioManager.cpp"
	"Managers/FontManager.cpp"
	"Managers/GameManager.cpp"
	"Managers/Input.cpp"
	"Managers/SDLAudioManager.cpp"
	"Managers/State.cpp"
	"Managers/TextureManager.cpp"
	"Managers/TweenManager.cpp"
	"Scenes/CreditsScene.cpp"
	"Scenes/GameScene.cpp"
	"Scenes/MenuScene.cpp"
	"Scenes/RecruitScene.cpp"
	"Scenes/Scene.cpp"
	"Scenes/TransitionScene.cpp"
	"Structures/Font.cpp"
	"Structures/Game.cpp"
	"Structures/SceneMachine.cpp"
	"Structures/Team.cpp"
	"Structures/Texture.cpp"
	"Structures/Tween.cpp"
	"Structures/UnitFactory.cpp"
	"third_party/AStar.cpp"
	"Utils/TimePool.cpp")

add_executable(drakhtar ${DRAKHTAR_SOURCES})
target_compile_features(drakhtar PUBLIC cxx_std_17)
target_include_directories(drakhtar
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/deps/drakhtar-telemetry/include>
	$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>/src)

# Link the libraries and install them.
target_link_libraries(drakhtar ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} telemetry)

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

if (MSVC)
	target_compile_options(drakhtar
		PRIVATE
		/W4
	)
	get_target_property(opts drakhtar COMPILE_OPTIONS)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(drakhtar
		PRIVATE
		-pedantic
		-pedantic-errors
		-Wall
		-Wextra
		-Wno-float-equal
		-Wno-padded
		-luuid
	)
else ()
	target_compile_options(drakhtar
		PRIVATE
		-pedantic
		-pedantic-errors
		-Wall
		-Wextra
		-Wconversion
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-float-equal
		-Wno-padded
		-Wno-reserved-id-macro
		-luuid
	)
endif ()
