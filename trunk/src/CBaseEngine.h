#ifndef CBASEENGINE_H
#define CBASEENGINE_H

#include <string>
#include <gl/gl.h>
#include <ctime>
#include "globals.h"
#include "const.h"
#include "typedefs.h"
#include "datatypes.h"
#include "CBaseEntity.h"
#include "CEntMgr.h"
#include "CInputMgr.h"
#include "CMaterialMgr.h"
#include "CGuiMgr.h"
#include "CFontMgr.h"
#include "elements/Material.h"


class CText;

class CBaseEngine{
  private:

    //time vars
    clock_t         lastClock;
    double          time;
    double          lastTime;
    double          timeDelta;
    double          realTime;
    double          lastRealTime;
    double          realTimeDelta;
    double          timeScale;
    unsigned long long int    frameCount;
    double          fps;
    CText*          _consoleOutput;


  public:
    CEntMgr*        ents;
    CInputMgr*      input;
    CGuiMgr*        gui;
    CFontMgr*       fonts;
    CMaterialMgr*   materials;


    void            init();
    void            destroy();
    double          getTime() const;
    double          getLastTime() const;
    double          getTimeDelta() const;
    double          getRealTime() const;
    double          getLastRealTime() const;
    double          getRealTimeDelta() const;
    unsigned long long int getFrameCount() const;
    double          getFPS() const;


    void            think();
    void            initWorldView();
    void            initGuiView();
    void            drawScene();

    void            setConsoleOutput(CText* console);
    void            log(const String& text);

    void            quit();

    Font*           systemFont;
    Material*       testMat;
    Material*       cursorMat;


};

inline double CBaseEngine::getTime() const{
  return time;
}

inline double CBaseEngine::getLastTime() const{
  return lastTime;
}

inline double CBaseEngine::getTimeDelta() const{
  return timeDelta;
}

inline double CBaseEngine::getRealTime() const{
  return realTime;
}

inline double CBaseEngine::getLastRealTime() const{
  return lastRealTime;
}

inline double CBaseEngine::getRealTimeDelta() const{
  return realTimeDelta;
}

inline unsigned long long int CBaseEngine::getFrameCount() const{
  return frameCount;
}

inline double CBaseEngine::getFPS() const{
  return fps;
}

inline void CBaseEngine::quit(){
  PostQuitMessage(0);
}

inline void CBaseEngine::setConsoleOutput(CText* console){
  _consoleOutput=console;
}



extern CBaseEngine* engine;
#endif


