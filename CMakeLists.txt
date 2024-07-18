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

add_executable(${PROJECT_NAME} src/main.cpp
        src/game.cpp
        src/game.h
        src/renderer.cpp
        src/renderer.h
        src/window.cpp
        src/window.h
        src/miner.cpp
        src/miner.h
        src/rock.cpp
        src/rock.h
        src/scene.cpp
        src/scene.h)

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-res-in-the-game-package") # Set the asset path macro in release mode
