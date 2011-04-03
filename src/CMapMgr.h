#ifndef CMAPMGR_H
#define CMAPMGR_H

#include "typedefs.h"
#include <stdexcept>

class CMapMgr{
  public:
    CMapMgr();
    void load(const String& name);
    void update();
    void unload();
    void reload();
    void setMapAsBackground(bool val);
    void setMapTime(double time);
    double getMapTime();
    bool isBackground();
    String getMapName();
  private:
    String m_mapName;
    bool m_isLoaded;
    bool m_shouldLoad;
    String m_newMapName;

    bool m_background;
    bool m_menuOpen;

    double m_mapTime;
    double m_offsetMapTime;
};

inline bool CMapMgr::isBackground(){
  return m_background;
}

inline void CMapMgr::setMapAsBackground(bool val){
  m_background = val;
}

inline void CMapMgr::reload(){
  load(m_mapName);
}

inline void CMapMgr::setMapTime(double time){
  m_mapTime = time;
  m_offsetMapTime = time + 5.;
}

inline String CMapMgr::getMapName(){
  return m_mapName;
}

#endif // CMAPMGR_H
