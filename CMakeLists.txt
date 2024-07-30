cmake_minimum_required(VERSION 3.14)
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

#[[
# Fetch FreeType
FetchContent_Declare(
        freetype
        GIT_REPOSITORY "https://github.com/aseprite/freetype2.git"
        GIT_TAG "VER-2-10-0"
)

FetchContent_MakeAvailable(freetype)

# Set FreeType variables for SDL2_ttf
set(FREETYPE_LIBRARY freetype)
set(FREETYPE_INCLUDE_DIRS ${freetype_SOURCE_DIR}/include)
FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
    FetchContent_Populate(freetype)
    add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()
]]#

# Find the FreeType package
find_package(Freetype CONFIG REQUIRED)

# Fetch SDL2_ttf
FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
        GIT_TAG "release-2.22.0"
)

FetchContent_MakeAvailable(SDL2_ttf)

include_directories("${CMAKE_CURRENT_LIST_DIR}/src/")
# -DCMAKE_CXX_FLAGS="-I /src/"
# include_directories(${freetype_SOURCE_DIR}/include)

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
        src/engine/InputMap.h
        src/engine/ResourceLoader.h
        src/engine/ResourceLoader.cpp
        src/engine/MessageTexture.cpp
        src/engine/MessageTexture.h
        src/engine/AppDebug.cpp
        src/engine/AppDebug.h
        src/engine/Event.cpp
        src/engine/Event.h)

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static Freetype::Freetype SDL2_ttf::SDL2_ttf-static)

target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-res-in-the-game-package") # Set the asset path macro in release mode
