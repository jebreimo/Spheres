##****************************************************************************
## Copyright © 2017 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2019-12-29.
##
## This file is distributed under the BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.15)
project(Spheres)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

if (DEFINED LOCAL_SOURCE_PACKAGE_DIR OR DEFINED ENV{LOCAL_SOURCE_PACKAGE_DIR})
    if (NOT LOCAL_SOURCE_PACKAGE_DIR)
        set(LOCAL_SOURCE_PACKAGE_DIR $ENV{LOCAL_SOURCE_PACKAGE_DIR})
    endif ()
endif ()

if (DEFINED LOCAL_SOURCE_PACKAGE_DIR)
    FetchContent_Declare(tungsten
        URL "file://${LOCAL_SOURCE_PACKAGE_DIR}/Tungsten-0.2.69.69.tar.gz")
else ()
    FetchContent_Declare(tungsten
        GIT_REPOSITORY "https://github.com/jebreimo/Tungsten.git"
        GIT_TAG v0.2.69)
endif ()

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
endif ()
