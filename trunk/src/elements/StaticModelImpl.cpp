#include "StaticModelImpl.h"

#include "CBaseEngine.h"

StaticModelImpl::StaticModelImpl(const json::mValue& value){
  json::mObject::const_iterator physModel = value.get_obj().find("physModel");
  if(physModel != value.get_obj().end()){
    engine->log("new PhysicsModel(physModel->second);");
    m_physModel = new PhysicsModel(physModel->second);
  }else{
    engine->log("new PhysicsModel();");
    m_physModel = new PhysicsModel();
  }
  const json::mArray& parts = value.get_obj().find("parts")->second.get_array();
  for(json::mArray::const_iterator it=parts.begin(); it!=parts.end(); ++it){
    m_parts.push_back(StaticModelPart(*it));
  }

  m_radius = 0.;
  m_vertexCount = 0;
  m_indexCount = 0;
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    m_radius = std::max(m_radius,(*it).getRadius());
    m_vertexCount += it->getVertexCount();
    m_indexCount += it->getIndexCount();
  }
}

void StaticModelImpl::uploadData(){
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    it->uploadData();
  }
}

void StaticModelImpl::assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset){
  //Model::assignVbos(vbo, vboOffset, indexVbo, indexVboOffset);
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    it->setOffsets(vboOffset, indexVboOffset);
    vboOffset += it->getVertexCount();
    indexVboOffset += it->getIndexCount();
  }
}

void StaticModelImpl::render(){
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    it->draw();
  }
}
