#ifndef CMAPMGR_H
#define CMAPMGR_H

#include "typedefs.h"

class CMapMgr{
  public:
    CMapMgr();
    void load(const String& name);
    void update();
    void unload();
    void setMapAsBackground(bool val);
    bool isBackground();
  private:
    String m_mapName;
    bool m_isLoaded;
    bool m_shouldLoad;
    String m_newMapName;

    bool m_background;
    bool m_menuOpen;
};

inline bool CMapMgr::isBackground(){
  return m_background;
}

#endif // CMAPMGR_H