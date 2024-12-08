cmake_minimum_required(VERSION 3.14)
project(fps_infinite C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Adding SDL2
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
        GIT_TAG "release-2.28.1"
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2)

# Fetch SDL2_image
FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image.git"
        GIT_TAG "release-2.6.3"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

# START ADDITION
set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
# END ADDITION

FetchContent_MakeAvailable(SDL2_image)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG ${IGG_GLM_TAG}
)

FetchContent_MakeAvailable(glm)

include_directories("${CMAKE_CURRENT_LIST_DIR}/src/")

add_executable(${PROJECT_NAME} src/main.cpp
        src/engine/App.cpp
        src/engine/App.h
        src/engine/Renderer.cpp
        src/engine/Renderer.h
        src/engine/Window.cpp
        src/engine/Window.h
        src/engine/InputMap.cpp
        src/engine/InputMap.h
        src/engine/ResourceLoader.h
        src/engine/ResourceLoader.cpp
        src/engine/MessageTexture.cpp
        src/engine/MessageTexture.h
        src/engine/AppDebug.cpp
        src/engine/AppDebug.h
        src/engine/Event.h
        src/engine/utils/Utils.h
        src/engine/utils/URand.cpp
        src/engine/utils/UColors.cpp
        src/engine/UniqueTexture.cpp
        src/engine/UniqueTexture.h
        src/engine/state_machine/StateMachine.h
        src/engine/state_machine/StateMachine.cpp
        src/engine/game_object/IGameObject.h
        src/engine/game_object/AEntity.h
        src/game/Game.cpp
        src/game/Game.h
        src/game/characters/Player.cpp
        src/game/characters/Player.h
        # src/engine/game_object/EntityScene.cpp
        src/engine/game_object/EntityScene.h
        src/engine/game_object/Entity3D.h
        src/game/characters/ACharacter.h
        src/engine/Camera3D.cpp
        src/engine/Camera3D.h
        src/engine/utils/UMath.cpp)

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static glm)

target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-res-in-the-game-package") # Set the asset path macro in release mode
