#ifndef CINPUTMGR_H
#define CINPUTMGR_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "datatypes.h"
#include "macros.h"
#include "typedefs.h"
#include "vec2d.h"

class CInputMgr{
  public:
                    CInputMgr();
                    ~CInputMgr();
    void            init();
    void            update();

    void            setEnabled(bool enabled);

    bool            keyDown(int key);
    bool            keyStillDown(int key);
    bool            keyPressed(int key);
    bool            keyDepressed(int key);
    float           keyTimed(int key);
    float           keyTimedDelta(int key);
    float           keyRealTimed(int key);
    float           keyRealTimedDelta(int key);

    String          getString();

    bool            buttonDown(MouseButton button) const;
    bool            buttonPressed(MouseButton button) const;
    bool            buttonDepressed(MouseButton button) const;

    vec2d           getMouseDelta();
    float           getX() const;
    float           getY() const;
    float           getCursorX() const;
    float           getCursorY() const;
    vec2d           getCursor() const;
    vec2d           getCursorDelta() const;

    void            characterInput(String character);

    DIMOUSESTATE2   MouseState[2];
    char            keyBuffer[2][256];
    double          keyTimeBuffer[2][256];
    double          keyRealTimeBuffer[2][256];
  private:
    bool            m_enabled;
    LPDIRECTINPUT8  DIObject;
    LPDIRECTINPUTDEVICE8 DIKeyboardDevice;

    LPDIRECTINPUTDEVICE8 DIMouseDevice;

    bool            bInverted;           //inverted y axis (NEW)
    int             iCurrBuffer;
    float           fSensitivity;        //mouse sensitivity (NEW)
    vec2d           mouse;
    vec2d           mouseDelta;
    vec2d           cursor;
    vec2d           cursorDelta;
    int             iAxes,              //number of axes (NEW)
                    iButtons;           //number of buttons (NEW)
    String          _inputString[2];
};

inline float CInputMgr::getX() const{
  if(m_enabled)
  return mouse.x;
  return 0.;
}

inline float CInputMgr::getY() const{
  if(m_enabled)
  return mouse.y;
}

inline float CInputMgr::getCursorX() const{
  return cursor.x;
}

inline float CInputMgr::getCursorY() const{
  return cursor.y;
}

inline vec2d CInputMgr::getCursor() const{
  return cursor;
}

inline vec2d CInputMgr::getCursorDelta() const{
  return cursorDelta;
}

inline vec2d CInputMgr::getMouseDelta(){
  if(m_enabled)
  return mouseDelta;
  return vec2d();
}

inline void CInputMgr::setEnabled(bool enabled){
  m_enabled = enabled;
}
#endif
