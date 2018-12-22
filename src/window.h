#if !defined(__GeoWindow_HEAD_FILE__)
#define __GeoWindow_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

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
};

#endif // __GeoWindow_HEAD_FILE__