#include "window.h"
#include "log.h"
#include <assert.h>

#if !defined(DEFAULT_WINDOW_HEIGHT)
#define DEFAULT_WINDOW_HEIGHT 480
#endif // DEFAULT_WINDOW_HEIGHT

#if !defined(DEFAULT_WINDOW_WIDTH)
#define DEFAULT_WINDOW_WIDTH 640
#endif // DEFAULT_WINDOW_WIDTH

static void glfw_error_callback(int error, const char *description)
{
    Log::GetInstance()->OutputConsole(error, description, Level_Error);
}

static void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnKeyCallback(key, scancode, action, mods);
}

static void glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnMouseMove(xpos, ypos);
}

static void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnMouseButtonCallback(button, action, mods);
}

static void glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnScroll(xoffset, yoffset);
}

static void glfw_cursor_enter_callback(GLFWwindow *window, int entered)
{
    if (entered)
    {
        // The cursor entered the client area of the window
    }
    else
    {
        // The cursor left the client area of the window
    }
}

static void glfw_drop_callback(GLFWwindow *window, int count, const char **paths)
{
}

static void glfw_window_refresh_callback(GLFWwindow *window)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnPaint();
}

static void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnFrameBufferSize(width, height);
}

GeoWindow::GeoWindow(const std::string &title)
    : m_window(nullptr), m_title(title)
{
    m_width = DEFAULT_WINDOW_WIDTH;
    m_height = DEFAULT_WINDOW_HEIGHT;
}

GeoWindow::~GeoWindow()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

bool GeoWindow::CreateWindow()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        return false;
    }

    SetCallback();

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::GetInstance()->OutputConsole("Unable to initialize glad");
        return false;
    }

    glfwSwapInterval(1);

    return true;
}

void GeoWindow::ShowWindow()
{
    assert(m_window);

    glViewport(0, 0, m_width, m_height);

    while (!glfwWindowShouldClose(m_window))
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void GeoWindow::OnKeyCallback(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        OnClose();
    }
}

void GeoWindow::OnMouseButtonCallback(int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        OnLButtonDown(xpos, ypos);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        OnLButtonUp(xpos, ypos);
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        OnRButtonDown(xpos, ypos);
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        OnRButtonUp(xpos, ypos);
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        OnMButtonDown(xpos, ypos);
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        OnMButtonUp(xpos, ypos);
    }
}

void GeoWindow::OnLButtonDown(double xpos, double ypos)
{
}

void GeoWindow::OnLButtonUp(double xpos, double ypos)
{
}

void GeoWindow::OnRButtonDown(double xpos, double ypos)
{
}

void GeoWindow::OnRButtonUp(double xpos, double ypos)
{
}

void GeoWindow::OnMButtonDown(double xpos, double ypos)
{
}

void GeoWindow::OnMButtonUp(double xpos, double ypos)
{
}

void GeoWindow::OnMouseMove(double xpos, double ypos)
{
}

void GeoWindow::OnClose()
{

    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void GeoWindow::OnPaint()
{
}

void GeoWindow::OnFrameBufferSize(int width, int height)
{
    m_height = height;
    m_width = width;

    glViewport(0, 0, m_width, m_height);
}

void GeoWindow::OnScroll(double xoffset, double yoffset)
{
}

void GeoWindow::SetCallback()
{
    assert(m_window);

    glfwSetWindowUserPointer(m_window, (void *)this);

    glfwSetKeyCallback(m_window, glfw_key_callback);
    glfwSetCursorPosCallback(m_window, glfw_cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, glfw_mouse_button_callback);
    glfwSetScrollCallback(m_window, glfw_scroll_callback);
    glfwSetCursorEnterCallback(m_window, glfw_cursor_enter_callback);
    glfwSetDropCallback(m_window, glfw_drop_callback);

    glfwSetWindowRefreshCallback(m_window, glfw_window_refresh_callback);
    glfwSetFramebufferSizeCallback(m_window, glfw_framebuffer_size_callback);
}