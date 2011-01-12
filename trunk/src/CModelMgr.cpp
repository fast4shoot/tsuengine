#include "CModelMgr.h"

#include "glew/glew.h"

CModelMgr::CModelMgr(){
  GLuint buff[4];
  glGenBuffers(4, buff);
  staticVbo = buff[0];
  staticIndexVbo = buff[1];
  dynamicVbo = buff[2];
  dynamicIndexVbo = buff[3];
}

ModelHandle* CModelMgr::getModel(String name){
  /*
    std::ifstream file(("models/"+model+".json").c_str());
  if(file.good()){
    json::mValue value;
    json::read(file, value);
  */

/*
  MaterialList::iterator it;
  if((it = matList.find(name)) != matList.end()){
    return it->second;
  }else{
    engine->log("Vytvářím materiál "+name);
    Material* newMat = new Material(name);
    matList.insert(std::make_pair(name, newMat));
    return newMat;
  }
  */
//}
