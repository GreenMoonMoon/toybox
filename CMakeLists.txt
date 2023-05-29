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
        extern/cgltf)

set(extern_SOURCES extern/glad/src/gl.c)


# SUPER MARIO
add_executable(toybox)
target_sources(toybox PRIVATE
        main.c
        src/viewport.c
        src/io/file.c
        src/io/glsl.c
        src/io/gltf.c
        src/io/gpu.c
        src/scene/inputs.c
        src/scene/render.c
        src/types/mesh.c
        src/types/model.c
        src/camera.c
        src/types/scene.c
        src/types/shader.c
        src/types/simple_string.c
        src/types/node.c
        ${extern_SOURCES})
target_include_directories(toybox PRIVATE src)
target_link_libraries(toybox PRIVATE SDL2 SDL2main)