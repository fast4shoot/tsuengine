#include "CModelMgr.h"

#include "glew/glew.h"

CModelMgr::CModelMgr(){
  modelTypeMap["static"]=STATIC;
  modelTypeMap["dynamic"]=DYNAMIC;
  GLuint buff[4];
  glGenBuffers(4, buff);
  staticVbo = buff[0];
  staticIndexVbo = buff[1];
  dynamicVbo = buff[2];
  dynamicIndexVbo = buff[3];
}

ModelHandle* CModelMgr::getModel(String name){
  std::ifstream file(("models/"+model+".json").c_str());
  if(file.good()){
    json::mValue value;
    json::read(file, value);
    ModelTypeMap::iterator it = modelTypeMap.find(value.find("type")->second.get_str());
    if(it != modelTypeMap.end()){
      ModelType mt = it->second;
      ModelBase* mb;
      if(mt=STATIC){
        mb = loadStaticModel(name,value);
      }

      ModelHandle* mh = new ModelHandle(mb,mt);

    }else{
      engine->log("Wrong model type "+(value.find("type")->second.get_str())+" in model "+name);
    }
  }else{
    engine->log("Can't open file for model "+name);
  }

  return null;

}

StaticModel* CModelMgr::loadStaticModel(const String& name, const json::mValue& data){
   StaticModelList::iterator
   StaticModel* model = new StaticModel(value);
}
