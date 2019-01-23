#include "window.h"
#include "log.h"
#include <assert.h>
#include "mesh.h"
#include "arcball.h"
#include "camera.h"
#include "tools.h"
#include "light.h"
#include "setting.h"

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

static void glfw_window_size_callback(GLFWwindow *window, int width, int height)
{
    GeoWindow *win = static_cast<GeoWindow *>(glfwGetWindowUserPointer(window));
    assert(win);

    win->OnWindowSize(width, height);
}

GeoWindow::GeoWindow(const std::string &title)
    : m_window(nullptr), m_title(title), m_mouseLBtnDown(false), m_mouseRBtnDown(false), m_mesh(nullptr), m_canvas(nullptr)
{
    WindowConfig &config = GeoSetting::GetInstance()->WindowConfig();

    m_width = config.m_width;
    m_height = config.m_height;
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
    SAFE_DELETE(m_canvas);

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

void GeoWindow::ShowGeoWindow()
{
    assert(m_window);

    GeoCamera::GetInstance()->ResetCamera(GeoVector3D(0.0f, 0.0f, 5.0f), GeoVector3D(0.0f, 0.0f, 0.0f), GeoVector3D(0.0f, 1.0f, 0.0f));

    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    WindowSizeChange();

    std::vector<GeoVertex> vertices;
    std::vector<unsigned int> indices;

    float data[] = {
        // positions          // normals

        -0.3f,
        -0.3f,
        -0.3f,
        0.0f,
        0.0f,
        -1.0f,
        0.3f,
        -0.3f,
        -0.3f,
        0.0f,
        0.0f,
        -1.0f,
        0.3f,
        0.3f,
        -0.3f,
        0.0f,
        0.0f,
        -1.0f,
        0.3f,
        0.3f,
        -0.3f,
        0.0f,
        0.0f,
        -1.0f,
        -0.3f,
        0.3f,
        -0.3f,
        0.0f,
        0.0f,
        -1.0f,
        -0.3f,
        -0.3f,
        -0.3f,
        0.0f,
        0.0f,
        -1.0f,

        -0.3f,
        -0.3f,
        0.3f,
        0.0f,
        0.0f,
        1.0f,
        0.3f,
        -0.3f,
        0.3f,
        0.0f,
        0.0f,
        1.0f,
        0.3f,
        0.3f,
        0.3f,
        0.0f,
        0.0f,
        1.0f,
        0.3f,
        0.3f,
        0.3f,
        0.0f,
        0.0f,
        1.0f,
        -0.3f,
        0.3f,
        0.3f,
        0.0f,
        0.0f,
        1.0f,
        -0.3f,
        -0.3f,
        0.3f,
        0.0f,
        0.0f,
        1.0f,

        -0.3f,
        0.3f,
        0.3f,
        -1.0f,
        0.0f,
        0.0f,
        -0.3f,
        0.3f,
        -0.3f,
        -1.0f,
        0.0f,
        0.0f,
        -0.3f,
        -0.3f,
        -0.3f,
        -1.0f,
        0.0f,
        0.0f,
        -0.3f,
        -0.3f,
        -0.3f,
        -1.0f,
        0.0f,
        0.0f,
        -0.3f,
        -0.3f,
        0.3f,
        -1.0f,
        0.0f,
        0.0f,
        -0.3f,
        0.3f,
        0.3f,
        -1.0f,
        0.0f,
        0.0f,

        0.3f,
        0.3f,
        0.3f,
        1.0f,
        0.0f,
        0.0f,
        0.3f,
        0.3f,
        -0.3f,
        1.0f,
        0.0f,
        0.0f,
        0.3f,
        -0.3f,
        -0.3f,
        1.0f,
        0.0f,
        0.0f,
        0.3f,
        -0.3f,
        -0.3f,
        1.0f,
        0.0f,
        0.0f,
        0.3f,
        -0.3f,
        0.3f,
        1.0f,
        0.0f,
        0.0f,
        0.3f,
        0.3f,
        0.3f,
        1.0f,
        0.0f,
        0.0f,

        -0.3f,
        -0.3f,
        -0.3f,
        0.0f,
        -1.0f,
        0.0f,
        0.3f,
        -0.3f,
        -0.3f,
        0.0f,
        -1.0f,
        0.0f,
        0.3f,
        -0.3f,
        0.3f,
        0.0f,
        -1.0f,
        0.0f,
        0.3f,
        -0.3f,
        0.3f,
        0.0f,
        -1.0f,
        0.0f,
        -0.3f,
        -0.3f,
        0.3f,
        0.0f,
        -1.0f,
        0.0f,
        -0.3f,
        -0.3f,
        -0.3f,
        0.0f,
        -1.0f,
        0.0f,

        -0.3f,
        0.3f,
        -0.3f,
        0.0f,
        1.0f,
        0.0f,
        0.3f,
        0.3f,
        -0.3f,
        0.0f,
        1.0f,
        0.0f,
        0.3f,
        0.3f,
        0.3f,
        0.0f,
        1.0f,
        0.0f,
        0.3f,
        0.3f,
        0.3f,
        0.0f,
        1.0f,
        0.0f,
        -0.3f,
        0.3f,
        0.3f,
        0.0f,
        1.0f,
        0.0f,
        -0.3f,
        0.3f,
        -0.3f,
        0.0f,
        1.0f,
        0.0f,
    };

    for (unsigned int i = 0; i < 36; i++)
    {
        GeoVertex vertex;

        GeoVector3D pos, normal;

        pos[0] = data[i * 6];
        pos[1] = data[i * 6 + 1];
        pos[2] = data[i * 6 + 2];

        normal[0] = data[i * 6 + 3];
        normal[1] = data[i * 6 + 4];
        normal[2] = data[i * 6 + 5];

        vertex.Position(pos);
        vertex.Normal(normal);

        vertices.push_back(vertex);
        indices.push_back(i);
    }

    m_mesh = new GeoMesh(vertices, indices);

    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_canvas->Active();

        m_mesh->Draw();

        m_canvas->Deactive();

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

    m_lastPt[0] = ((2.0f * xpos) / (double)m_width) - 1.0f;
    m_lastPt[1] = 1.0f - ((2.0 * ypos) / (double)m_height);
    m_lastPt[2] = 0.0f;
}

void GeoWindow::OnLButtonUp(double xpos, double ypos)
{
    m_mouseLBtnDown = false;
}

void GeoWindow::OnRButtonDown(double xpos, double ypos)
{
    m_mouseRBtnDown = true;

    m_lastPt[0] = ((2.0f * xpos) / (double)m_width) - 1.0f;
    m_lastPt[1] = 1.0f - ((2.0 * ypos) / (double)m_height);
    m_lastPt[2] = 0.0f;
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
    GeoVector3D lastPt = m_lastPt;

    GeoVector3D pos;
    pos[0] = ((2.0f * xpos) / (double)m_width) - 1.0f;
    pos[1] = 1.0f - ((2.0 * ypos) / (double)m_height);
    pos[2] = 0.0f;

    if (m_mouseRBtnDown)
    {
        GeoMatrix project = GeoCamera::GetInstance()->GetProjectionMatrix();
        GeoMatrix view = GeoCamera::GetInstance()->GetViewMatrix();
        GeoMatrix model = m_mesh->GetModelMatrix();

        GeoMatrix pvm = project * view * model;

        GeoMatrix pvm_inverse(4, 4);

        pvm.Inverse(pvm_inverse);

        GeoVector4D v2 = GeoVector4D(pos, 1.0f) * pvm_inverse;
        GeoVector4D v1 = GeoVector4D(lastPt, 1.0f) * pvm_inverse;

        m_mesh->Translate(v2 - v1);
    }

    if (m_mouseLBtnDown)
    {
        GeoArcBall ball;

        lastPt = ball.ProjectToBall(lastPt);
        pos = ball.ProjectToBall(pos);

        if (lastPt == pos)
        {
            return;
        }

        GeoMatrix rotate = ball.GetRotateMatrix(lastPt, pos);

        GeoMatrix project = GeoCamera::GetInstance()->GetProjectionMatrix();
        GeoMatrix view = GeoCamera::GetInstance()->GetViewMatrix();
        GeoMatrix model = m_mesh->GetModelMatrix();

        GeoBBox &box = m_mesh->GetBBox();
        GeoVector4D center = GeoVector4D(box.GetCenter(), 1.0f);

        GeoVector4D c1 = project * view * model * center;
        m_mesh->Rotate(rotate);

        model = m_mesh->GetModelMatrix();
        GeoVector4D c2 = project * view * model * center;
        m_mesh->Translate(c1 - c2);
    }

    m_lastPt = pos;
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

    WindowSizeChange();
}

void GeoWindow::OnWindowSize(int width, int height)
{
    glfwGetFramebufferSize(m_window, (int *)&m_width, (int *)&m_height);

    WindowSizeChange();
}

void GeoWindow::OnScroll(double xoffset, double yoffset)
{

    if (GeoCamera::GetInstance()->GetProjectType() == PT_Ortho)
    {
        m_mesh->Scale(yoffset < 0 ? 0.9f : 1.1f);
    }
    else
    {
        GeoCamera::GetInstance()->Scale(yoffset < 0 ? false : true);
    }
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
    glfwSetWindowSizeCallback(m_window, glfw_window_size_callback);
}

void GeoWindow::WindowSizeChange()
{
    m_origin[0] = m_width / 2;
    m_origin[1] = m_height / 2;

    glViewport(0, 0, m_width, m_height);

    double x, y, minimum;
    minimum = Tools::GetInstance()->Minimum(m_width, m_height);
    x = m_width / minimum;
    y = m_height / minimum;
    GeoFrustum frustum(-x, x, -y, y, 2.0f, 10.f);
    GeoCamera::GetInstance()->SetFrustum(frustum, PT_Ortho);

    SAFE_DELETE(m_canvas);
    m_canvas = new GeoCanvas(m_width, m_height);
}