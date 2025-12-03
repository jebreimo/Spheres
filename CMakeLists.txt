##****************************************************************************
## Copyright © 2017 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2019-12-29.
##
## This file is distributed under the BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.15)
project(Spheres)

set(CMAKE_CXX_STANDARD 20)

if (EMSCRIPTEN)
    set(YIMAGE_TIFF OFF)
endif ()

include(FetchContent)

FetchContent_Declare(tungsten
    GIT_REPOSITORY "https://github.com/jebreimo/Tungsten.git"
    GIT_TAG v0.7.1)

FetchContent_MakeAvailable(tungsten)

list(APPEND CMAKE_MODULE_PATH ${tungsten_SOURCE_DIR}/tools/cmake)

include(TungstenTargetEmbedShaders)

add_executable(Spheres
    src/Spheres/Spheres.cpp
    src/Spheres/SpheresShaderProgram.cpp
    src/Spheres/SpheresShaderProgram.hpp
    )

target_link_libraries(Spheres
    PRIVATE
        Tungsten::Tungsten
    )

tungsten_target_embed_shaders(Spheres
    FILES
        src/Spheres/Spheres-frag.glsl
        src/Spheres/Spheres-vert.glsl
    )

if (EMSCRIPTEN)
    set(EMSCRIPTEN_TARGET_NAME Spheres)
    configure_file(src/emscripten/index.html.in index.html)
    file(COPY src/emscripten/index.css DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()
