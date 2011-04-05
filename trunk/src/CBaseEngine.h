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
#include "CInputMgr.h"
#include "CMaterialMgr.h"
#include "CGuiMgr.h"
#include "CFontMgr.h"
#include "CModelMgr.h"
#include "CPhysicsMgr.h"
#include "CCameraMgr.h"
#include "CMapMgr.h"
#include "CEntMgr.h"
#include "CNetwork.h"
#include "elements/Material.h"
#include "utils/Thinker.h"


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

    std::ofstream   m_logFile;
    bool            m_ready;
    std::vector<Thinker*> m_thinkers;


  public:

    CInputMgr*      input;
    CCameraMgr*     camera;
    CGuiMgr*        gui;
    CFontMgr*       fonts;
    CMaterialMgr*   materials;
    CPhysicsMgr*    physics;
    CModelMgr*      models;
    CEntMgr*        ents;
    CMapMgr*        map;

    CText*          _consoleOutput;
    CText*          m_tempConsoleOutput;

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
    void            resetGameTime();
    void            setTimeScale(double newTimeScale);
    double          getTimeScale();

    void            think();
    void            initWorldView();
    void            initGuiView();
    void            drawScene();

    void            registerThinker(Thinker* thinker);

    bool            isReady();

    void            setConsoleOutput(CText* console);
    void            log(const String& text);
    void            logAppend(const String& text);
    void            warning(const String& text);
    void            debug(const String& text);

    void            log(const format& text);
    void            logAppend(const format& text);
    void            warning(const format& text);
    void            debug(const format& text);

    void            checkGl();

    void            quit();

    Font*           systemFont;

    int             getScreenHeight();
    int             getScreenWidth();

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

inline void CBaseEngine::setTimeScale(double newTimeScale){
  timeScale = newTimeScale;
}

inline double CBaseEngine::getTimeScale(){
  return timeScale;
}

inline void CBaseEngine::log(const format& text){
  log(text.str());
}

inline void CBaseEngine::logAppend(const format& text){
  logAppend(text.str());
}

inline void CBaseEngine::warning(const format& text){
  warning(text.str());
}

inline void CBaseEngine::debug(const format& text){
  debug(text.str());
}

extern CBaseEngine* engine;
#endif


