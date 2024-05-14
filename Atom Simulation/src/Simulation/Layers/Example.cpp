#include "Example.h"

Example::Example(GLFWwindow* window, Camera* camera)
    : m_Window(nullptr), m_Camera(nullptr)
{
    m_Window = window;
    m_Camera = camera;

    Vertex verticies[] = 
    {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f)),       // lower left near 0
        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),        // lower right near 1
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),      // lower left far 2
        Vertex(glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f)),      // lower right far 3
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.98f, 0.72f, 0.01f), glm::vec3(0.0f), glm::vec2(0.0f)),     // upper left near 4
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.94f, 0.01f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f)),      // upper right near 5
        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.01f, 0.98f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f)),    // upper left far 6
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.58f, 0.01f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f))      // upper right far 7
    };

    unsigned int indices[] = 
    {
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

    m_VB.Init(verticies, sizeof(verticies));

    m_VA.LinkAttribute(m_VB, 0, 3, GL_FLOAT, sizeof(Vertex));   // Position
    m_VA.LinkAttribute(m_VB, 1, 3, GL_FLOAT, sizeof(Vertex));   // Normal

    m_IB.Init(indices, sizeof(indices));

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
