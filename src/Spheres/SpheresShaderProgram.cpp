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
    program = create_program();
    auto vertexShader = create_shader(GL_VERTEX_SHADER, Spheres_vert);
    attach_shader(program, vertexShader);
    auto fragmentShader = create_shader(GL_FRAGMENT_SHADER, Spheres_frag);
    attach_shader(program, fragmentShader);
    link_program(program);
    use_program(program);

    position_attr = get_vertex_attribute(program, "a_Position");
    x_params = get_uniform<Xyz::Vector2F>(program, "u_XParams");
    y_params = get_uniform<Xyz::Vector2F>(program, "u_YParams");
    z_screen = get_uniform<float>(program, "u_ZScreen");
    radius = get_uniform<float>(program, "u_Radius");
    transform = get_uniform<Xyz::Matrix3F>(program, "u_Transform");
    offset = get_uniform<float>(program, "u_Offset");
}
