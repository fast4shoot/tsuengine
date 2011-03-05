#ifndef CMAPMGR_H
#define CMAPMGR_H

#include "typedefs.h"

class CMapMgr{
  public:
    CMapMgr();
    void loadMap(const String& name);
    void update(){}
  private:
    String m_mapName;
    bool m_isLoaded;
};

#endif // CMAPMGR_H
