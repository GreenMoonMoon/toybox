cmake_minimum_required(VERSION 3.24)
project(toybox LANGUAGES C)

set(CMAKE_C_STANDARD 23)

# Fetch content
include(FetchContent)

FetchContent_Declare( sdl
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(sdl)

# Extern source
include_directories(
        ${sdl_SOURCE_DIR}/include
        extern/cglm/include
        extern/glad/include
        extern/stb-master
        extern/cgltf
        extern/stb)

set(extern_SOURCES extern/glad/src/gl.c)


# TOYBOX
add_executable(toybox)
target_sources(toybox PRIVATE
        main.c
        src/viewport.c
        src/draw.c
        src/mesh.c
        src/material.c
        src/io/file.c
        src/io/image.c
        src/node.c
        src/camera.c
        src/inputs.c
        src/terrain.c
        src/texture.c

        ${extern_SOURCES})
target_include_directories(toybox PRIVATE src)
target_link_libraries(toybox PRIVATE SDL2::SDL2main SDL2::SDL2-static)

add_custom_command(TARGET toybox
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:toybox>/assets/)