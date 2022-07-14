//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "Tungsten/Tungsten.hpp"

class SpheresShaderProgram
{
public:
    void setup();

    Tungsten::ProgramHandle program;
    Tungsten::Uniform<Xyz::Vector2F> x_params;
    Tungsten::Uniform<Xyz::Vector2F> y_params;
    Tungsten::Uniform<float> z_screen;
    Tungsten::Uniform<float> radius;
    Tungsten::Uniform<Xyz::Matrix3F> transform;
    Tungsten::Uniform<float> offset;
    GLuint position_attr;
};
