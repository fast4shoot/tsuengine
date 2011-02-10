#ifndef CBASEENGINE_H
#define CBASEENGINE_H

#include <string>
#include <fstream>
#include "glew/glew.h"
#include <ctime>
#include "globals.h"
#include "const.h"
#include "typedefs.h"
#include "datatypes.h"
#include "entities/CBaseEntity.h"
#include "CEntMgr.h"
#include "CInputMgr.h"
#include "CMaterialMgr.h"
#include "CGuiMgr.h"
#include "CFontMgr.h"
#include "CModelMgr.h"
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
    std::ofstream   m_logFile;
    bool            m_ready;


  public:
    CEntMgr*        ents;
    CInputMgr*      input;
    CGuiMgr*        gui;
    CFontMgr*       fonts;
    CMaterialMgr*   materials;
    CModelMgr*      models;


                    CBaseEngine();
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

    bool            isReady();

    void            setConsoleOutput(CText* console);
    void            log(const String& text);
    void            warning(const String& text);

    void            checkGl();

    void            quit();

    Font*           systemFont;
    Material*       testMat;
    Material*       cursorMat;

    int             getScreenHeight();
    int             getScreenWidth();

    Model *testMdl, *testMdl2, *testMdl3;

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

inline bool CBaseEngine::isReady(){
  return m_ready;
}

inline void CBaseEngine::setConsoleOutput(CText* console){
  _consoleOutput=console;
}

inline void CBaseEngine::warning(const String& text){
  log("Warning: "+text);
}

inline int CBaseEngine::getScreenHeight(){
  return g.scrHeight;
}
inline int CBaseEngine::getScreenWidth(){
  return g.scrWidth;
}

extern CBaseEngine* engine;
#endif


