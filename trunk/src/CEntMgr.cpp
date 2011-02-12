#include "CEntMgr.h"
#include "entities/CBaseEntity.h"
#include "const.h"

#include <map>

#include "CBaseEngine.h"
#include "DescriptorList.h"

CEntMgr::CEntMgr(){
  std::vector<CBaseEntityDescriptor*>& l = DescriptorList::instance()->descriptors;
  for(std::vector<CBaseEntityDescriptor*>::iterator it = l.begin(); it != l.end(); ++it){
    (*it)->doRegister(*it);
    m_descriptors[(*it)->getClassname()] = (*it);
  }
}

void CEntMgr::print(){
  engine->log("Zaregistrovane entity: ");
  for(DescriptorMap::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it){
    engine->log((*it).second->getClassname());
  }
  CBaseEntity* cbe = m_descriptors["CBaseEntity"]->create();
  cbe->fireInput("print",NULL);
  cbe = m_descriptors["CLogicEntity"]->create();
  cbe->fireInput("print",NULL);
  cbe->setValue("random",123);
  cbe->fireInput("test",NULL);
}
/*
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
*/
