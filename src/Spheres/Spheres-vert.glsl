//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#version 100

attribute highp vec3 a_Position;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
}
