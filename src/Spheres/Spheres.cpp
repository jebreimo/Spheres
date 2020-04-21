//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Tungsten/Shapes.hpp>
#include <Tungsten/SdlApplication.hpp>
#include "SpheresShaderProgram.hpp"

class Spheres : public Tungsten::EventLoop
{
public:
    void onStartup(Tungsten::SdlApplication& app) final
    {
        app.setSwapInterval(1);
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

    void onDraw(Tungsten::SdlApplication& app) final
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto[w, h] = app.windowSize();
        auto aspect = 1 / float(h);
        m_Program.xParams.set({2 * aspect, -1 * float(w) * aspect});
        m_Program.yParams.set({2 * aspect, -1});
        m_Program.radius.set(0.5f + 0.49f * std::sin(SDL_GetTicks() / 5000.0f));
        m_Program.zScreen.set(5.0);
        m_Program.transform.set(Xyz::rotate3(SDL_GetTicks() / 3000.0f)
                                * Xyz::translate3(std::sin(SDL_GetTicks() / 1900.0f), 0.0f));

        m_Program.offset.set(sin(SDL_GetTicks() / 400.0f));

        Tungsten::drawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_SHORT);
    }
private:
    std::vector<Tungsten::BufferHandle> m_Buffers;
    Tungsten::VertexArrayHandle m_VertexArray;
    SpheresShaderProgram m_Program;
    GLsizei m_ElementCount = 0;
};

int main(int argc, char* argv[])
{
    Tungsten::SdlApplication app("Spheres", std::make_unique<Spheres>());
    try
    {
        app.parseCommandLineOptions(argc, argv);
        app.run();
    }
    catch (Tungsten::TungstenException& ex)
    {
        std::cout << ex.what() << "\n";
        return 1;
    }
    return 0;
}
