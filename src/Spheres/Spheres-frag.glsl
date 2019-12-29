//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#version 100

uniform highp float u_AspectRatio;
uniform highp float u_ZScreen;
uniform highp float u_Radius;
uniform highp mat3 u_Transform;
uniform highp float u_Offset;

highp vec2 calculateSphereIntersections(highp vec3 vector,
                                        highp float radius)
{
    highp float r2 = radius * radius;
    highp float diff2 = vector.x * vector.x + vector.y * vector.y;
    if (diff2 > r2)
        return vec2(0, 0);

    highp float v2 = dot(vector, vector);
    highp float vz2 = vector.z * vector.z;
    highp float c = sqrt(vz2 * vz2 - v2 * (vz2 - r2));
    return vec2((vz2 - c) / v2, (vz2 + c) / v2);
}

void main()
{
    highp vec3 xy = u_Transform * vec3(gl_PointCoord.x * u_AspectRatio,
                                       gl_PointCoord.y,
                                       1.0);

    highp float cellSize = 3.0 * u_Radius;
    highp float column = floor(0.5 + xy.x / cellSize);
    highp float row = floor(0.5 + xy.y / cellSize);
    highp float x = column * cellSize;
    highp float y = row * cellSize;

    highp float angle = column * 1.1 + row * 0.4;
    highp float xOffset = cos(angle) * u_Offset * u_Radius * 0.5;
    highp float yOffset = sin(angle) * u_Offset * u_Radius * 0.5;
    highp vec3 sphere = vec3(x + xOffset, y + yOffset, u_ZScreen);
    highp vec3 v = vec3(xy.x - sphere.x, xy.y - sphere.y, u_ZScreen);

    highp vec2 t = calculateSphereIntersections(v, u_Radius);
    if (t[0] == 0.0)
        discard;

    highp vec3 normal = t[0] * v;
    normal.z -= u_ZScreen;
    normal /= u_Radius;
    highp float light = dot(normal, vec3(0.577350269, 0.577350269, -0.577350269));
    highp float rg = mix(0.0, 1.0, light);
    highp float b = mix(0.5, 1.0, light);
    gl_FragColor = vec4(rg, rg, b, 1.0);
}
