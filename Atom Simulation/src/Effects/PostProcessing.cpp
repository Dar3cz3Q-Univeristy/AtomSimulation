#include "PostProcessing.h"

PostProcessing::PostProcessing()
    : m_Gamma(2.2f)
{
    float verticies[] = {
        // Coords  // Texture //
         1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

         1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };

    unsigned int indicies[] = {
        0, 1, 2,
        3, 4, 5
    };

    m_VB.Init(verticies, sizeof(verticies));

    m_Layout.Push<float>(2); // Coords
    m_Layout.Push<float>(2); // Texture

    m_VA.AddBuffer(m_VB, m_Layout);

    m_IB.Init(indicies, sizeof(indicies));

    m_FB.Bind();

    m_Texture.Init();

    m_RB.Bind();
    m_RB.Init();

    m_Shader.Init("res/shaders/post_processing.vert.shader", "res/shaders/post_processing.frag.shader");
    m_Shader.Bind();

    m_Shader.SetUniform1i("u_ScreenTexture", 0);
    m_Shader.SetUniform1f("u_Gamma", m_Gamma);
}

PostProcessing::~PostProcessing() {}

void PostProcessing::Bind() const
{
    m_FB.Bind();
    GLCall(glEnable(GL_DEPTH_TEST));
}

void PostProcessing::Unbind() const
{
    m_FB.Unbind();
    GLCall(glDisable(GL_DEPTH_TEST));
}

void PostProcessing::Draw() const
{
    m_FB.Draw();
    Unbind();
    m_Texture.Bind();
    m_Renderer.Draw(m_VA, m_IB, m_Shader);
}
