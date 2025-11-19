//****************************************************************************
// Copyright © 2019 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2019-07-16.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Tungsten/SdlApplication.hpp>
#include "SpheresShaderProgram.hpp"

class Spheres : public Tungsten::EventLoop
{
public:
    explicit Spheres(Tungsten::SdlApplication& app)
        : EventLoop(app),
          m_buffers()
    {
        m_vertex_array = Tungsten::generate_vertex_array();
        Tungsten::bind_vertex_array(m_vertex_array);

        constexpr float vertex_buffer[] = {
            -1, -1, 0,
            1, -1, 0,
            -1, 1, 0,
            1, 1, 0
        };
        constexpr short index_buffer[] = {
            0, 1, 2,
            1, 3, 2
        };

        Tungsten::generate_buffers(m_buffers);
        Tungsten::bind_buffer(GL_ARRAY_BUFFER, m_buffers[0]);
        Tungsten::set_buffer_data(GL_ARRAY_BUFFER, sizeof(vertex_buffer),
                                  vertex_buffer, GL_STATIC_DRAW);
        Tungsten::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[1]);
        Tungsten::set_buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer),
                                  index_buffer, GL_STATIC_DRAW);

        m_program.setup();
        Tungsten::define_vertex_attribute_pointer(m_program.position_attr, 3,
                                                  GL_FLOAT, 0, 0);
        Tungsten::enable_vertex_attribute(m_program.position_attr);
    }

    void on_draw() final
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto [w, h] = application().window_size();
        const auto aspect = 1 / static_cast<float>(h);
        const auto ticks = float(SDL_GetTicks());
        m_program.x_params.set({2 * aspect, -1 * float(w) * aspect});
        m_program.y_params.set({2 * aspect, -1});
        m_program.radius.set(0.49f * std::sin(ticks / 5000.0f) + 0.5f);
        m_program.z_screen.set(5.0);
        m_program.transform.set(Xyz::affine::rotate2(ticks / 3000.0f)
                                * Xyz::affine::translate2(std::sin(ticks / 1900.0f), 0.0f));

        m_program.offset.set(sin(ticks / 400.0f));

        Tungsten::draw_triangle_elements_16(0, 6);
        redraw();
    }

private:
    Tungsten::BufferHandle m_buffers[2];
    Tungsten::VertexArrayHandle m_vertex_array;
    SpheresShaderProgram m_program;
};

int main(int argc, char* argv[])
{
    Tungsten::SdlApplication app("Spheres");
    try
    {
        app.parse_command_line_options(argc, argv);
        app.run<Spheres>();
    }
    catch (Tungsten::TungstenException& ex)
    {
        std::cout << ex.what() << "\n";
        return 1;
    }
    return 0;
}
