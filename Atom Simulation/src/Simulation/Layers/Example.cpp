#include "Example.h"

Example::Example(GLFWwindow* window, Camera* camera)
    : m_Window(nullptr), m_Camera(nullptr)
{
    m_Window = window;
    m_Camera = camera;

    // 3D Cube
    float positions[] = {
        //     Coordinates      //         Colors     
          -0.5f,  -0.5f,   0.5f,  1.0f,   1.0f,   1.0f,    // lower left near 0
           0.5f,  -0.5f,   0.5f,  1.0f,   0.0f,   0.0f,    // lower right near 1
          -0.5f,  -0.5f,  -0.5f,  0.0f,   1.0f,   0.0f,    // lower left far 2
           0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,   1.0f,    // lower right far 3
          -0.5f,   0.5f,   0.5f,  0.98f,  0.72f,  0.01f,    // upper left near 4
           0.5f,   0.5f,   0.5f,  0.94f,  0.01f,  0.98f,    // upper right near 5
          -0.5f,   0.5f,  -0.5f,  0.01f,  0.98f,  0.98f,    // upper left far 6
           0.5f,   0.5f,  -0.5f,  0.58f,  0.01f,  0.98f     // upper right far 7
    };

    unsigned int indices[] = {
        // bottom square
        0, 1, 2,
        2, 1, 3,
        // near square
        0, 4, 5,
        0, 1, 5,
        // left square
        0, 2, 4,
        2, 4, 6,
        // far square
        2, 6, 3,
        3, 6, 7,
        // right square
        1, 3, 7,
        1, 5, 7,
        // top square
        4, 5, 6,
        5, 6, 7
    };

    m_VB.Init(positions, 8 * 3 * 3 * sizeof(float));

    m_Layout.Push<float>(3);  // Coordinates
    m_Layout.Push<float>(3);  // Colors

    m_VA.AddBuffer(m_VB, m_Layout);

    m_IB.Init(indices, 6 * 2 * 3);

    m_Shader.Init("res/shaders/cube_texture.vert.shader", "res/shaders/cube_texture.frag.shader");
    m_Shader.Bind();

    m_Texture.Init("res/textures/rubiks", "png");
    m_Texture.Bind();

    m_Shader.SetUniform1i("u_Texture", 0);

    AS_LOG("Example layer initialized");
}

Example::~Example() {}

void Example::OnDraw()
{
    m_Camera->Matrix(m_Shader, "u_MVP");

    m_Renderer.Draw(m_VA, m_IB, m_Shader);
}

void Example::OnUpdate()
{
    m_Camera->Inputs(m_Window);
}
