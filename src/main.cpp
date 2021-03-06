#define UNICODE
#include <windows.h>
#include "GL/glew.h"
#include <iostream>
#include <cmath>
#include <string>
#include <exception>
#include <iterator>

#include "utf8/utf8.h"

#include "const.h"
#include "datatypes.h"
#include "globals.h"
#include "CBaseEngine.h"
#include "macros.h"
#include "exceptions.h"



/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
  appInstance = hInstance;
  WNDCLASS wc;
  HWND hWnd;

  HGLRC hRC;
  MSG msg;
  BOOL bQuit = FALSE;
  g.scrWidth = 900;
  g.scrHeight = 500;
  // register window class
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = L"TSUEWindow";
  RegisterClass(&wc);

  // create main window
  hWnd = CreateWindow (
    L"TSUEWindow", L"TSU Engine window",
    WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
    0, 0, g.scrWidth+6, g.scrHeight+27,
    //10,10, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);

  appWindow=hWnd;
  ShowWindow(hWnd, SW_SHOWMAXIMIZED);

  try{

    // enable OpenGL for the window
    EnableOpenGL (hWnd, &hDC, &hRC);

    if(glewInit() != GLEW_OK){
      throw std::runtime_error("glewInit() failed");
    }

    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //create and start the engine
    SwapBuffers (hDC);

    engine=new CBaseEngine();
    engine->init();

    // program main loop

    while (!bQuit)
    {
      if(GetActiveWindow() == hWnd) SetCursorPos(g.scrWidth/2, g.scrHeight/2);
      // check for messages
      if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)){
        // handle or dispatch messages
        switch(msg.message){
          case WM_QUIT:
            bQuit = TRUE;
          break;

          default:
            TranslateMessage (&msg);
            DispatchMessage (&msg);
          }
        }else{
          engine->think();
          engine->drawScene();
          if(GetActiveWindow() != hWnd && engine->getFPS()>100.0) Sleep(35);
          /*if(engine->getFPS()>200.0)Sleep(1);*/
        }
    }
  }catch(const std::exception& e){
    std::string result;
    result="An exception occured: \n";
    result+=e.what();
    MessageBoxA(hWnd,result.c_str(),"Exception",MB_OK | MB_ICONEXCLAMATION);
  }catch(...){
    MessageBoxA(hWnd,"An exception occured.","Exception",MB_OK | MB_ICONEXCLAMATION);
  }
  engine->destroy();
  delete engine;
  // shutdown OpenGL
  DisableOpenGL (hWnd, hDC, hRC);

  // destroy the window explicitly
  DestroyWindow (hWnd);

  return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
  switch (message){
    case WM_ACTIVATE:
			return 0;								// Return To The Message Loop

    case WM_CREATE:
      return 0;

    case WM_DESTROY:
      return 0;

    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;

    case WM_SIZE:
      g.scrWidth = LOWORD(lParam);
      g.scrHeight = HIWORD(lParam);
      return 0;

    case WM_SYSCOMMAND:
      switch (wParam){
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
        case SC_KEYMENU:
          return 0;
      }
      return 1;

    case WM_CHAR:{
      //TODO: convert Windows UTF-16 to UTF-8 for CInputMGr (needs to handle surrogate pairs too!)
      String result;
      utf8::utf16to8(&wParam, &wParam+1, std::back_inserter(result));
      engine->input->characterInput(result);
      return false;
    }




    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
