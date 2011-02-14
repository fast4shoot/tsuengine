#include "CMaterialMgr.h"

#include <utility>
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "CBaseEngine.h"

CMaterialMgr::CMaterialMgr(){
  ilInit();
  iluInit();
  ilutRenderer(ILUT_OPENGL);
}

Material* CMaterialMgr::getMaterial(const String& name){
  MaterialList::iterator it;
  if((it = matList.find(name)) != matList.end()){
    return it->second;
  }else{
    engine->log("Vytvářím materiál "+name);
    Material* newMat = new Material(name);
    matList.insert(std::make_pair(name, newMat));
    return newMat;
  }
}
