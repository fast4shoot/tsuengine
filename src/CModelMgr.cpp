#include "CModelMgr.h"

#include <fstream>
#include "CBaseEngine.h"
#include "glew/glew.h"

CModelMgr::CModelMgr(){
  modelTypeMap["static"]=M_STATIC;
  modelTypeMap["dynamic"]=M_DYNAMIC;
  m_buffersGenerated = false;
  engine->log("CModelMgr()");
  engine->checkGl();
}

Model* CModelMgr::getModel(const String& name){
  generateBuffers();

  if(staticModels.find(name) != staticModels.end()){
    Model* mdl = new StaticModel(staticModels[name]);
    modelHandles.push_back(mdl);
    return mdl;
  }

  engine->log("Vytvářím model "+name);
  std::ifstream file(("models/"+name+".json").c_str());
  if(file.good()){
    json::mValue value;
    json::read(file, value);
    ModelTypeMap::iterator it = modelTypeMap.find(value.get_obj().find("type")->second.get_str());
    if(it != modelTypeMap.end()){

      ModelType mt = it->second;
      Model* mdl;
      if(mt==M_STATIC){
        mdl = new StaticModel(loadStaticModel(name,value));
      }
      modelHandles.push_back(mdl);
      engine->log(sformat("...model finished (%p)",mdl));
      return mdl;

    }else{
      engine->warning("Wrong model type "+(value.get_obj().find("type")->second.get_str())+" in model "+name);
    }
    file.close();
  }else{
    engine->warning("Can't open file for model "+name);
  }


  return NULL;

}

StaticModelImpl* CModelMgr::loadStaticModel(const String& name, const json::mValue& data){
  StaticModelImpl* model;
  if(staticModels.find(name) == staticModels.end()){
    model = new StaticModelImpl(data);
    staticModels[name] = model;
  }else{
    model = staticModels[name];
  }
  return model;
}

void CModelMgr::uploadData(){
  engine->log("Uploading model data to GPU");
  int staticVertexCount=0;
  int staticIndexCount=0;
  int dynamicVertexCount=0;
  int dynamicIndexCount=0;
  for(StaticModelList::iterator it = staticModels.begin(); it != staticModels.end(); ++it){
    it->second->assignVbos(staticVbo, staticVertexCount, staticIndexVbo, staticIndexCount);
    staticVertexCount += it->second->getVertexCount();
    staticIndexCount += it->second->getIndexCount();
  }

  //engine->log("uploadData()");
  engine->checkGl();

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, staticVbo);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, staticIndexVbo);
  //engine->log(sformat("Vertex count: %d, index count: %d", staticVertexCount, staticIndexCount));
  //engine->log(sformat("Buffer sizes: %d, %d", sizeof(StaticVertexData)*staticVertexCount, sizeof(unsigned int)*staticIndexCount));

  glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(StaticVertexData)*staticVertexCount, NULL, GL_STATIC_DRAW);
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(unsigned int)*staticIndexCount, NULL, GL_STATIC_DRAW);

  //engine->log("uploadData()");
  engine->checkGl();

  for(StaticModelList::iterator it = staticModels.begin(); it != staticModels.end(); it++){
    it->second->uploadData();
  }

  //engine->log("uploadData()");
  engine->checkGl();
  engine->logAppend("...finished");
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
    if((*it)->getType() == M_STATIC){
      (*it)->draw();
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

void CModelMgr::removeAll(){
  for(ModelHandleList::iterator it = modelHandles.begin(); it != modelHandles.end(); ++it){
    delete (*it);
  }
  modelHandles.clear();

  for(StaticModelList::iterator it = staticModels.begin(); it != staticModels.end(); ++it){
    delete it->second;
  }
  staticModels.clear();

  deleteBuffers();
}

void CModelMgr::generateBuffers(){
  if(m_buffersGenerated) return;

  glGenBuffersARB(4, m_buffers);
  staticVbo = m_buffers[0];
  staticIndexVbo = m_buffers[1];
  dynamicVbo = m_buffers[2];
  dynamicIndexVbo = m_buffers[3];
}

void CModelMgr::deleteBuffers(){
  if(m_buffersGenerated){
    glDeleteBuffersARB(4, m_buffers);
  }
}
