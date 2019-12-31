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
    using namespace Tungsten;
    program = createProgram();
    auto vertexShader = createShader(GL_VERTEX_SHADER, Spheres_vert);
    attachShader(program, vertexShader);
    auto fragmentShader = createShader(GL_FRAGMENT_SHADER, Spheres_frag);
    attachShader(program, fragmentShader);
    linkProgram(program);
    useProgram(program);

    positionAttribute = getVertexAttribute(program, "a_Position");
    xParams = getUniform<Xyz::Vector2f>(program, "u_XParams");
    yParams = getUniform<Xyz::Vector2f>(program, "u_YParams");
    zScreen = getUniform<float>(program, "u_ZScreen");
    radius = getUniform<float>(program, "u_Radius");
    transform = getUniform<Xyz::Matrix3f>(program, "u_Transform");
    offset = getUniform<float>(program, "u_Offset");
}
