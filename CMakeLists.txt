cmake_minimum_required(VERSION 3.0)
project(dig_straight_down C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

include_directories("${CMAKE_CURRENT_LIST_DIR}/src/")
# -DCMAKE_CXX_FLAGS="-I /src/"

add_executable(${PROJECT_NAME} src/main.cpp
        src/engine/Application.cpp
        src/engine/Application.h
        src/engine/Renderer.cpp
        src/engine/Renderer.h
        src/engine/Window.cpp
        src/engine/Window.h
        src/game/Miner.cpp
        src/game/Miner.h
        src/game/Tunnel.cpp
        src/game/Tunnel.h
        src/game/Game.cpp
        src/game/Game.h
        src/game/Material.cpp
        src/game/Material.h
        src/engine/IGameObject.h
        src/engine/InputMap.cpp
        src/engine/InputMap.h)

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)

target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-res-in-the-game-package") # Set the asset path macro in release mode
