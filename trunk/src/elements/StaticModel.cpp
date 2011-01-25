#include "StaticModel.h"

#include <algorithm>
#include "CBaseEngine.h"


StaticModel::StaticModel(const json::mValue& value){
  json::mArray parts = value.get_obj().find("parts")->second.get_array();
  for(json::mArray::iterator it=parts.begin(); it!=parts.end(); ++it){
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

void StaticModel::uploadData(){
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    it->uploadData();
  }
}

void StaticModel::assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset){
  ModelBase::assignVbos(vbo, vboOffset, indexVbo, indexVboOffset);
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    it->setOffsets(vboOffset, indexVboOffset);
    vboOffset += it->getVertexCount();
    indexVboOffset += it->getIndexCount();
  }
}

void StaticModel::draw(){
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    it->draw();
  }
}
