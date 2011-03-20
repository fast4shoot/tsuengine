#include "CCameraMgr.h"

void CCameraMgr::addTransform(CameraTransform* transform){
  m_transforms.push(transform);
}

void CCameraMgr::doTransform(){
  if(m_transforms.empty()) return;
  while(!m_transforms.top()->isActive()){
    m_transforms.pop();
  }
  m_transforms.top()->doTransform();
}

void CCameraMgr::removeAll(){
  while(!m_transforms.empty()){
    m_transforms.pop();
  }
}
