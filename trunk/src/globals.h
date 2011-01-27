#ifndef GLOBALS_H
#define GLOBALS_H

#include <windows.h>

#include "datatypes.h"


extern HDC hDC;
extern HINSTANCE appInstance;
extern HWND      appWindow;

struct globals{
  int scrHeight;
  int scrWidth;
};

extern globals g;

#endif
