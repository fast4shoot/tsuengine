#include "CEntMgr.h"
#include "CBaseEntity.h"
#include "const.h"

CEntMgr::CEntMgr(){
  entCount=0;
  lastSearchCount=0;                   
}

int CEntMgr::getEntCount(){
  return entCount;   
}

CBaseEntity* CEntMgr::getEntById(int id){
  return entityTable[id];             
}

int CEntMgr::getEntCountByTargetName(std::string targetname){
  int count=0;
  for(int i=0;i<ENT_MAX;i++){
    if(getEntById(i)->params.getStringParam("targetname") == targetname)count++;
  }
  return count;
}

void CEntMgr::findEntsByTargetName(std::string targetname){
  lastSearchCount=0;
  CBaseEntity* ent;
  for(int i=0;i<ENT_MAX;i++){
    ent=getEntById(i);
    if(ent->params.getStringParam("targetname") == targetname){
      searchTable[lastSearchCount]=ent;
      lastSearchCount++;
    }
  }           
}

void CEntMgr::findEntsInSphere(vec3d pos, double radius){
     
}

CBaseEntity* CEntMgr::getNextEntFromLastSearch(){
  return NULL;
}
