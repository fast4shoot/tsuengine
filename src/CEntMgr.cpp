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
}

CBaseEntity* CEntMgr::create(const String& classname){
  DescriptorMap::iterator it = m_descriptors.find(classname);
  if(it == m_descriptors.end()){
    engine->warning(sformat("Can't create entity %s: entity not found", classname.c_str()));
    return NULL;
  }
  CBaseEntity* ent = (*it).second->create();
  m_entities.push_back(ent);
  return ent;
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
