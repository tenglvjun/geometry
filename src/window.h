#if !defined(__GeoWindow_HEAD_FILE__)
#define __GeoWindow_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "mesh.h"
#include "vector.h"
#include "canvas.h"

class GeoWindow
{
public:
  GeoWindow(const std::string &title);
  virtual ~GeoWindow();

public:
  bool CreateGeoWindow();
  void ShowGeoWindow();

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
  void OnWindowSize(int width, int height);
  void OnScroll(double xoffset, double yoffset);

protected:
  void SetCallback();
  void WindowSizeChange();

private:
  GeoWindow();

protected:
  GLFWwindow *m_window;
  int m_height;
  int m_width;
  std::string m_title;
  bool m_mouseRBtnDown;
  bool m_mouseLBtnDown;
  GeoVector3D m_lastPt;
  GeoVector3D m_origin;
};

#endif // __GeoWindow_HEAD_FILE__