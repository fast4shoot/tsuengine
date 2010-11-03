#ifndef CBASEENGINE_H
#define CBASEENGINE_H

#include <string>
#include <gl/gl.h>
#include <ctime>
#include "globals.h"
#include "const.h"
#include "datatypes.h"
#include "CBaseEntity.h"
#include "CEntMgr.h"
#include "CInputMgr.h"
#include "CGuiMgr.h"
#include "CFontMgr.h"

class CBaseEngine{
  private:
    rgba            drawColor;
    vec3d           drawPos;


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
    std::wstring    _log;


  public:
    CEntMgr*        ents;
    CInputMgr*      input;
    CGuiMgr*        gui;
    CFontMgr*       fonts;


    void            init();
    void            destroy();
    void            setDrawPos(double x, double y, double z);
    void            setDrawPos(vec3d pos);
    void            setDrawColor(float r, float g, float b, float a);
    void            setDrawColor(rgba col);
    void            drawModel(int wmId);
    double          getTime() const;
    double          getLastTime() const;
    double          getTimeDelta() const;
    double          getRealTime() const;
    double          getLastRealTime() const;
    double          getRealTimeDelta() const;
    unsigned long long int getFrameCount() const;
    double          getFPS() const;
    void            createEntity(std::string name);


    void            think();
    void            initWorldView();
    void            initGuiView();
    void            drawScene();

    void            log(const std::wstring& text);

    void            quit();

    Font*           systemFont;

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

inline void CBaseEngine::log(const std::wstring& text){
  _log=text;
}

extern CBaseEngine* engine;
#endif
