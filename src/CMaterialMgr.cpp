#include "CMaterialMgr.h"

#include <utility>
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include <boost/foreach.hpp>

#include "CBaseEngine.h"

CMaterialMgr::CMaterialMgr(){
  ilInit();
  iluInit();
  ilutRenderer(ILUT_OPENGL);
}

Material* CMaterialMgr::getPersistentMaterial(const String& name){
  Material* mat = getMaterial(name);
  mat->setPersistent(true);
  return mat;
}

Material* CMaterialMgr::getMaterial(const String& name){
  MaterialList::iterator it;
  if((it = matList.find(name)) != matList.end()){
    return it->second;
  }else{
    engine->log("Vytvářím materiál "+name);
    Material* newMat = new Material(name);
    matList.insert(std::make_pair(name, newMat));
    engine->logAppend("...hotovo");
    return newMat;
  }
}

void CMaterialMgr::removeAll(){
  MaterialList persistent;
  for(MaterialList::iterator it = matList.begin(); it != matList.end(); ++it){
    if(!it->second->isPersistent()){
      delete it->second;
    }else{
      persistent[it->first] = it->second;
    }
  }

  matList.clear();

  matList = MaterialList(persistent);
}
