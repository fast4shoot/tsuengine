#include "CCenteredWindow.h"

#include "const.h"

CCenteredWindow::CCenteredWindow(const vec2d& size, const std::wstring& label):
  CWindow((vec2d(SCREENWIDTH,SCREENHEIGHT)-size)/2, size, label)
{}
