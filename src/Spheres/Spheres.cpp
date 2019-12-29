//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <chrono>
#include <Tungsten/Shapes.hpp>
#include "SpheresShaderProgram.hpp"

double getTime()
{
    using namespace std::chrono;
    duration<double> time = steady_clock::now().time_since_epoch();
    return time.count();
}

class SpheresApp : public Tungsten::SdlApplication
{
public:
    void setup() override
    {
        setSwapInterval(1);
        m_VertexArray = Tungsten::generateVertexArray();
        Tungsten::bindVertexArray(m_VertexArray);

        m_Buffers = Tungsten::generateBuffers(2);
        Tungsten::ArrayBufferBuilder builder(3);
        Tungsten::addRectangle(builder, Xyz::Rectangle<float>({-1, -1}, {2, 2}));
        setBuffers(m_Buffers[0], m_Buffers[1], builder);
        m_ElementCount = builder.elementCount();

        m_Program.setup();
        Tungsten::defineVertexAttributePointer(m_Program.positionAttribute, 3,
                                               GL_FLOAT, false, 0, 0);
        Tungsten::enableVertexAttribute(m_Program.positionAttribute);
    }

    void draw() override
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_Program.aspectRatio.set(aspectRatio());
        m_Program.radius.set(0.5f + 0.49f * std::sin(SDL_GetTicks() / 5000.0f));
        m_Program.zScreen.set(5.0);
        m_Program.transform.set(Xyz::rotate3(SDL_GetTicks() / 3000.0f)
                                * Xyz::translate3(std::sin(SDL_GetTicks() / 1900.0f), 0.0f));

        m_Program.offset.set(sin(SDL_GetTicks() / 400.0f));

        auto time = getTime();
        Tungsten::drawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_SHORT);
    }
private:
    std::vector<Tungsten::BufferHandle> m_Buffers;
    Tungsten::VertexArrayHandle m_VertexArray;
    SpheresShaderProgram m_Program;
    GLsizei m_ElementCount = 0;
};

int main()
{
    SpheresApp app;
    try
    {
        app.run();
    }
    catch (Tungsten::GlError& ex)
    {
        std::cout << ex.what() << "\n";
        return 1;
    }
    return 0;
}