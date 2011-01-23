#include "StaticModel.h"

#include <algorithm>
#include "CBaseEngine.h"


StaticModel::StaticModel(const json::mValue& value){
  json::mArray parts = value.get_obj().find("parts")->second.get_array();
  for(json::mArray::iterator it=parts.begin(); it!=parts.end(); ++it){
    m_parts.push_back(StaticModelPart(*it));
  }

  double radius;
  int vertexCount;
  int indexCount;
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    radius = std::max(radius,(*it).getRadius());
    vertexCount += it->getVertexCount();
    indexCount += it->getIndexCount();
  }
  m_radius = radius;
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
