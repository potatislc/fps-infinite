cmake_minimum_required(VERSION 3.14)
project(fps_infinite C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

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

# Add all .cpp and .h files in the src directory recursively
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# Add the executable with the collected source files
if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})
else ()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif ()

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static glm)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PROFILE_DEBUG)
else ()
    target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="./res/")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PROFILE_RELEASE)

    # Copy the res directory to the output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/res
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
    )
endif ()
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-res-in-the-game-package") # Set the asset path macro in release mode
