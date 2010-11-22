#ifndef CINPUTMGR_H
#define CINPUTMGR_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "datatypes.h"
#include "macros.h"
#include "typedefs.h"
class CInputMgr{
  public:
                    CInputMgr();
                    ~CInputMgr();
    void            init();
    void            update();
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

    const float     getX() const;
    const float     getY() const;
    const vec2d     getCursor() const;
    const vec2d     getCursorDelta() const;

    void            characterInput(String character);

    DIMOUSESTATE2   MouseState[2];
    char            keyBuffer[2][256];
    double          keyTimeBuffer[2][256];
    double          keyRealTimeBuffer[2][256];
  private:
    LPDIRECTINPUT8  DIObject;
    LPDIRECTINPUTDEVICE8 DIKeyboardDevice;

    LPDIRECTINPUTDEVICE8 DIMouseDevice;

    bool            bInverted;           //inverted y axis (NEW)
    int             iCurrBuffer;
    float           fSensitivity;        //mouse sensitivity (NEW)
    vec2d           cursor;
    vec2d           cursorDelta;
    int             iAxes,              //number of axes (NEW)
                    iButtons;           //number of buttons (NEW)
    String          _inputString[2];
};

inline const float CInputMgr::getX() const{
  return cursor.x;
}

inline const float CInputMgr::getY() const{
  return cursor.y;
}

inline const vec2d CInputMgr::getCursor() const{
  return cursor;
}

inline const vec2d CInputMgr::getCursorDelta() const{
  return cursorDelta;
}



#endif
