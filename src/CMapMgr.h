#ifndef CMAPMGR_H
#define CMAPMGR_H

#include "typedefs.h"

class CMapMgr{
  public:
    CMapMgr();
    void load(const String& name);
    void unload();
  private:
    String m_mapName;
    bool m_isLoaded;
};

#endif // CMAPMGR_H
