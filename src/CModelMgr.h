#ifndef CMODELMGR_H
#define CMODELMGR_H

#include "glew/glew.h"
#include "elements/StaticModel.h"


class CModelMgr{
  typedef std::map<String,StaticModel*> StaticModelList;
  public:
    CModelMgr();
    StaticModelList staticModels;
  protected:

    GLuint staticVbo;
    GLuint staticIndexVbo;
    GLuint dynamicVbo;
    GLuint dynamicIndexVbo;
};

#endif // CMODELMGR_H