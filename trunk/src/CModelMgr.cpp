#include "CModelMgr.h"

#include <fstream>
#include "CBaseEngine.h"
#include "glew/glew.h"

CModelMgr::CModelMgr(){
  modelTypeMap["static"]=STATIC;
  modelTypeMap["dynamic"]=DYNAMIC;
  GLuint buff[4];
  glGenBuffersARB(4, buff);
  staticVbo = buff[0];
  staticIndexVbo = buff[1];
  dynamicVbo = buff[2];
  dynamicIndexVbo = buff[3];
  engine->log("CModelMgr()");
  engine->checkGl();
}

Model* CModelMgr::getModel(String name){
  std::ifstream file(("models/"+name+".json").c_str());
  if(file.good()){
    json::mValue value;
    json::read(file, value);
    engine->log("Odhaduji typ modelu...");
    ModelTypeMap::iterator it = modelTypeMap.find(value.get_obj().find("type")->second.get_str());
    if(it != modelTypeMap.end()){
      ModelType mt = it->second;
      ModelBase* mb;
      if(mt==STATIC){
        mb = loadStaticModel(name,value);
      }
      Model* mh = new Model(mb,mt);
      modelHandles.push_back(mh);
      return mh;

    }else{
      engine->log("Wrong model type "+(value.get_obj().find("type")->second.get_str())+" in model "+name);
    }
    file.close();
  }else{
    engine->log("Can't open file for model "+name);
  }


  return NULL;

}

StaticModel* CModelMgr::loadStaticModel(const String& name, const json::mValue& data){
  StaticModel* model;
  if(staticModels.find(name) == staticModels.end()){
    engine->log("Vytvářím model...");
    model = new StaticModel(data);
    staticModels[name] = model;
  }else{
    engine->log("Znovu využívám model...");
    model = staticModels[name];
  }
  return model;
}

void CModelMgr::uploadData(){
  int staticVertexCount=0;
  int staticIndexCount=0;
  int dynamicVertexCount=0;
  int dynamicIndexCount=0;
  for(ModelHandleList::iterator it = modelHandles.begin(); it != modelHandles.end(); ++it){
    if((*it)->getType() == STATIC){
      (*it)->getModelRepresentation()->assignVbos(staticVbo, staticVertexCount, staticIndexVbo, staticIndexCount);
      staticVertexCount += (*it)->getModelRepresentation()->getVertexCount();
      staticIndexCount += (*it)->getModelRepresentation()->getIndexCount();
    }
  }

  engine->log("uploadData()");
  engine->checkGl();

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, staticVbo);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, staticIndexVbo);
  engine->log(sformat("Vertex count: %d, index count: %d", staticVertexCount, staticIndexCount));
  engine->log(sformat("Buffer sizes: %d, %d", sizeof(StaticVertexData)*staticVertexCount, sizeof(unsigned int)*staticIndexCount));

  glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(StaticVertexData)*staticVertexCount, NULL, GL_STATIC_DRAW);
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(unsigned int)*staticIndexCount, NULL, GL_STATIC_DRAW);

  engine->log("uploadData()");
  engine->checkGl();

  for(ModelHandleList::iterator it = modelHandles.begin(); it != modelHandles.end(); it++){
    (*it)->getModelRepresentation()->uploadData();
  }

  engine->log("uploadData()");
  engine->checkGl();
}


void CModelMgr::draw(){
  // bind VBOs for vertex array and index array
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, staticVbo);         // for vertex coordinates
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, staticIndexVbo); // for indices

  // do same as vertex array except pointer
  glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_INDEX_ARRAY);

  glVertexPointer(3, GL_FLOAT, sizeof(StaticVertexData), BUFFER_OFFSET(0));               // last param is offset, not ptr
  glNormalPointer(GL_FLOAT, sizeof(StaticVertexData), BUFFER_OFFSET(12));
  glClientActiveTextureARB(GL_TEXTURE0);
  glTexCoordPointer(2, GL_FLOAT, sizeof(StaticVertexData), BUFFER_OFFSET(24));

  glEnable(GL_TEXTURE_2D);

  for(ModelHandleList::iterator it = modelHandles.begin(); it != modelHandles.end(); it++){
    if((*it)->getType()==STATIC){
      (*it)->getModelRepresentation()->draw();
    }
  }

  glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_INDEX_ARRAY);

  // bind with 0, so, switch back to normal pointer operation
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

}
