#include "window.h"
#include "log.h"
#include <assert.h>
#include "mesh.h"
#include "arcball.h"
#include "camera.h"
#include "tools.h"

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
    : m_window(nullptr), m_title(title), m_mouseLBtnDown(false), m_mouseRBtnDown(false), m_mesh(nullptr)
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

    m_mouseLBtnDown = false;
    m_mouseRBtnDown = false;

    SAFE_DELETE(m_mesh);

    glfwTerminate();
}

bool GeoWindow::CreateGeoWindow()
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

    m_origin[0] = m_width / 2;
    m_origin[1] = m_height / 2;

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);

    GeoCamera::GetInstance()->ResetCamera(GeoVector3D(0.0f, 0.0f, 5.0f), GeoVector3D(0.0f, 0.0f, 0.0f), GeoVector3D(0.0f, 1.0f, 0.0f));
    GeoCamera::GetInstance()->SetFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, -10.f);

    return true;
}

void GeoWindow::ShowGeoWindow()
{
    assert(m_window);

    std::vector<GeoVertex> vertices;
    std::vector<unsigned int> indices;

    GeoVertex v1, v2, v3;
    v1.GetPos()[0] = -0.5f;
    v1.GetPos()[1] = -0.5f;
    v1.GetPos()[2] = 0.0f;
    v1.GetColor()[0] = 1.0f;

    v2.GetPos()[0] = 0.5f;
    v2.GetPos()[1] = -0.5f;
    v2.GetPos()[2] = 0.0f;
    v2.GetColor()[1] = 1.0f;

    v3.GetPos()[0] = 0.0f;
    v3.GetPos()[1] = 0.5f;
    v3.GetPos()[2] = 0.0f;
    v3.GetColor()[2] = 1.0f;

    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    GeoVector3D pos(0.0f, 0.0f, 0.0f);
    m_mesh = new GeoMesh(vertices, indices, pos);

    int a = sizeof(GeoVertex);

    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_mesh->Draw();

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
    m_mouseLBtnDown = true;

    m_lastPt = GeoVector3D(xpos, ypos, 0.0f) - m_origin;
    m_lastPt[1] = -m_lastPt[1];
}

void GeoWindow::OnLButtonUp(double xpos, double ypos)
{
    m_mouseLBtnDown = false;
}

void GeoWindow::OnRButtonDown(double xpos, double ypos)
{
    m_mouseRBtnDown = true;

    m_lastPt = GeoVector3D(xpos, ypos, 0.0f) - m_origin;
    m_lastPt[1] = -m_lastPt[1];
}

void GeoWindow::OnRButtonUp(double xpos, double ypos)
{
    m_mouseRBtnDown = false;
}

void GeoWindow::OnMButtonDown(double xpos, double ypos)
{
}

void GeoWindow::OnMButtonUp(double xpos, double ypos)
{
}

void GeoWindow::OnMouseMove(double xpos, double ypos)
{
    if (m_mouseRBtnDown)
    {
        GeoVector3D pos = GeoVector3D(xpos, ypos, 0.0f) - m_origin;
        pos[1] = -pos[1];

        GeoVector3D trans = pos - m_lastPt;

        trans[0] /= ((double)m_width / 2);
        trans[1] /= ((double)m_height / 2);

        GeoCamera::GetInstance()->Move(trans);

        m_lastPt = pos;
    }

    if (m_mouseLBtnDown)
    {
        GeoVector3D ptNow = GeoVector3D(xpos, ypos, 0.0f) - m_origin;
        ptNow[1] = -ptNow[1];

        if (ptNow == m_lastPt) {
            return;
        }
        

        GeoVector3D lastPt = m_lastPt;
        lastPt[0] /= ((double)m_width / 2);
        lastPt[1] /= ((double)m_height / 2);

        GeoVector3D pos = ptNow;
        pos[0] /= ((double)m_width / 2);
        pos[1] /= ((double)m_height / 2);

        GeoArcBall ball;
        lastPt = ball.ProjectToBall(lastPt);
        pos = ball.ProjectToBall(pos);

        GeoMatrix rotate = ball.GetRotateMatrix(lastPt, pos);

        GeoCamera::GetInstance()->Rotate(rotate);

        m_lastPt = ptNow;
    }
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

    m_origin[0] = m_width / 2;
    m_origin[1] = m_height / 2;

    glViewport(0, 0, m_width, m_height);
}

void GeoWindow::OnScroll(double xoffset, double yoffset)
{
    GeoCamera::GetInstance()->Scale(Tools::GetInstance()->IsZero(1.0f + yoffset));
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