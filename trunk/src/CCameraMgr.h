#ifndef CCAMERAMGR_H
#define CCAMERAMGR_H

#include <stack>
#include "utils/CameraTransform.h"

class CCameraMgr{
  public:
    void addTransform(CameraTransform* transform);
    void doTransform();
    void removeAll();
  protected:
    typedef std::stack<CameraTransform*> TransformStack;
    TransformStack m_transforms;

};

#endif // CCAMERAMGR_H
