#if !defined(__GeoWindow_HEAD_FILE__)
#define __GeoWindow_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "mesh.h"

struct UIPoint
{
  UIPoint()
  {
    m_x = 0.0f;
    m_y = 0.0f;
  }

  UIPoint(const double x, const double y)
  {
    m_x = x;
    m_y = y;
  }

  double m_x;
  double m_y;
};

class GeoWindow
{
public:
  GeoWindow(const std::string &title);
  virtual ~GeoWindow();

public:
  bool CreateWindow();
  void ShowWindow();

public:
  void OnKeyCallback(int key, int scancode, int action, int mods);
  void OnMouseButtonCallback(int button, int action, int mods);
  void OnLButtonDown(double xpos, double ypos);
  void OnLButtonUp(double xpos, double ypos);
  void OnRButtonDown(double xpos, double ypos);
  void OnRButtonUp(double xpos, double ypos);
  void OnMButtonDown(double xpos, double ypos);
  void OnMButtonUp(double xpos, double ypos);
  void OnMouseMove(double xpos, double ypos);

  void OnClose();
  void OnPaint();
  void OnFrameBufferSize(int width, int height);
  void OnScroll(double xoffset, double yoffset);

protected:
  void SetCallback();

private:
  GeoWindow();

protected:
  GLFWwindow *m_window;
  unsigned int m_height;
  unsigned int m_width;
  std::string m_title;
  bool m_mouseRBtnDown;
  bool m_mouseLBtnDown;
  UIPoint m_lastPt;
  GeoMesh *m_mesh;
};

#endif // __GeoWindow_HEAD_FILE__