#include "CCenteredWindow.h"

#include "const.h"
#include "CBaseEngine.h"

CCenteredWindow::CCenteredWindow(const vec2d& size, const String& label):
  CWindow((vec2d(engine->getScreenWidth(), engine->getScreenHeight())-size)/2, size, label)
{}
