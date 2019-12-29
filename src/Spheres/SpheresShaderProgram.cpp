//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "SpheresShaderProgram.hpp"
#include "Spheres-frag.glsl.hpp"
#include "Spheres-vert.glsl.hpp"

void SpheresShaderProgram::setup()
{
    program = Tungsten::createProgram();
    auto vertexShader = Tungsten::createShader(GL_VERTEX_SHADER,
                                               Spheres_vert);
    Tungsten::attachShader(program, vertexShader);

    auto fragmentShader = Tungsten::createShader(GL_FRAGMENT_SHADER,
                                                 Spheres_frag);
    Tungsten::attachShader(program, fragmentShader);
    Tungsten::linkProgram(program);
    Tungsten::useProgram(program);

    positionAttribute = Tungsten::getVertexAttribute(program, "a_Position");
    aspectRatio = Tungsten::getUniform<float>(program, "u_AspectRatio");
    zScreen = Tungsten::getUniform<float>(program, "u_ZScreen");
    radius = Tungsten::getUniform<float>(program, "u_Radius");
    transform = Tungsten::getUniform<Xyz::Matrix3f>(program, "u_Transform");
    offset = Tungsten::getUniform<float>(program, "u_Offset");
}
