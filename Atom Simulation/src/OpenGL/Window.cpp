#include "Window.h"

// Include layers
#include "Layers/Example.h"
#include "Layers/Atom.h"

float Window::s_LastFrameTime = 0.0f;
float Window::s_DeltaTime = 0.0f;
float Window::s_SumDeltaTime = 0.0f;

Window::Window(int width, int height, const std::string& title) 
    : m_Window(nullptr), m_Width(width), m_Height(height), m_Title(title), m_Minimized(false), m_Running(false), m_Counter(0), m_PostProcessing(nullptr)
{
    Init();

    m_Camera = Camera(m_Width, m_Height, glm::vec3(0.0f, 0.0f, 4.0f));

    //
    // Push layers on stack
    //

    PushLayer(new Atom(m_Window, &m_Camera));

    // TODO: Should do it other way than alocating it on heap
    m_AntiAliasing = new AntiAliasing(8);
    m_PostProcessing = new PostProcessing();
}

Window::~Window()
{
    if (m_PostProcessing)
        delete m_PostProcessing;

    if (m_AntiAliasing)
        delete m_AntiAliasing;

    glfwTerminate();
}

void Window::Run()
{
    m_Running = true;

    while (m_Running) 
    {
        float time = static_cast<float>(glfwGetTime());
        s_DeltaTime = time - s_LastFrameTime;
        s_SumDeltaTime += s_DeltaTime;
        s_LastFrameTime = time;

        if (!m_Minimized) 
        {
            m_AntiAliasing->Bind();

            m_Renderer.Clear();
            m_Camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

            for (Layer* layer : m_LayerStack) 
            {
                layer->OnDraw();
                layer->OnUpdate();
            }

            m_AntiAliasing->Read();
            m_PostProcessing->Draw();
        }

        Update();
        Events();
    } 
}

void Window::Init()
{
    // Initializing window
    int status = glfwInit();

    AS_ASSERT(status);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

    AS_ASSERT(m_Window);

    glfwMakeContextCurrent(m_Window);

    glfwSwapInterval(1); // Set VSync

    gladLoadGL();

    // Resize event callback
    glfwSetFramebufferSizeCallback(m_Window, WindowResizeCallBack);

    glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));
    //GLCall(glEnable(GL_BLEND));
    //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    AS_LOG("Window initialized");
    AS_LOG(glGetString(GL_VERSION));
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();

    Statistics();
}

void Window::Events()
{
    if (glfwWindowShouldClose(m_Window)) 
    {
        m_Running = false;
        return;
    }

    glfwGetWindowSize(m_Window, &m_Width, &m_Height);

    if (m_Width == 0 || m_Height == 0) 
    {
        m_Minimized = true;
        return;
    }

    m_Camera.UpdateWidth(m_Width);
    m_Camera.UpdateHeight(m_Height);

    m_Minimized = false;
}

void Window::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Window::Statistics()
{
    m_Counter++;

    if (s_SumDeltaTime >= 1.0f) 
    {
        // float fps = m_Counter;
        // float ms = (s_DeltaTime / m_Counter) * 1000.0f;

        std::string newTitle = m_Title + ": " + to_string_with_precision(m_Counter, 0) + " FPS";
        glfwSetWindowTitle(m_Window, newTitle.c_str());

        m_Counter = 0;
        s_SumDeltaTime = 0;
    }
}

void WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

