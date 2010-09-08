#ifndef CENTLIST_H
#define CENTLIST_H

#include "CBaseEntity.h"
#include "datatypes.h"
#include "const.h"

class CEntMgr{
  public:
                  CEntMgr();
    int           getEntCount();
    CBaseEntity*  getEntById(int id);
    int           getEntCountByTargetName(std::string targetname);
    void          findEntsByTargetName(std::string targetname);
    void          findEntsInSphere(vec3d pos, double radius);
    CBaseEntity*  getNextEntFromLastSearch();
  private:
    CBaseEntity*  entityTable[ENT_MAX];
    CBaseEntity*  searchTable[ENT_MAX];
    int           entCount;
    int           lastSearchCount;
};

#endif
