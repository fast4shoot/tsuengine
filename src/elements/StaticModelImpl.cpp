#include "StaticModelImpl.h"

#include "CBaseEngine.h"
#include <boost/foreach.hpp>

StaticModelImpl::StaticModelImpl(const json::mValue& value){
  json::mObject::const_iterator physModel = value.get_obj().find("physModel");
  if(physModel != value.get_obj().end()){
    m_physModel = new PhysicsModel(physModel->second);
  }else{
    m_physModel = new PhysicsModel();
  }
  const json::mArray& parts = value.get_obj().find("parts")->second.get_array();
  for(json::mArray::const_iterator it=parts.begin(); it!=parts.end(); ++it){
    m_parts.push_back(new StaticModelPart(*it));
  }

  m_radius = 0.;
  m_vertexCount = 0;
  m_indexCount = 0;
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    m_radius = std::max(m_radius,(*it)->getRadius());
    m_vertexCount += (*it)->getVertexCount();
    m_indexCount += (*it)->getIndexCount();
  }
}

StaticModelImpl::~StaticModelImpl(){
  engine->log("deleting m_physModel");
  delete m_physModel;
  engine->log("deleting m_parts");
  BOOST_FOREACH(StaticModelPart* part, m_parts){
    delete part;
  }
  m_parts.clear();
}

void StaticModelImpl::uploadData(){
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    (*it)->uploadData();
  }
}

void StaticModelImpl::assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset){
  //Model::assignVbos(vbo, vboOffset, indexVbo, indexVboOffset);
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    (*it)->setOffsets(vboOffset, indexVboOffset);
    vboOffset += (*it)->getVertexCount();
    indexVboOffset += (*it)->getIndexCount();
  }
}

void StaticModelImpl::render(){
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    (*it)->draw();
  }
}
