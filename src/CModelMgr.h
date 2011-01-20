#ifndef CMODELMGR_H
#define CMODELMGR_H

#include "datatypes.h"
#include "glew/glew.h"
#include "elements/StaticModel.h"
#include "elements/ModelHandle.h"

class CModelMgr{
  typedef std::map<String,StaticModel*> StaticModelList;
  typedef std::vector<ModelHandle*> ModelHandleList;
  typedef std::map<String,ModelType> ModelTypeMap;
  public:
    CModelMgr();
    ModelHandle*  getModel(String name);

  protected:
    StaticModelList staticModels;
    ModelHandleList ModelHandle;
    ModelTypeMap modelTypeMap;
    GLuint staticVbo;
    GLuint staticIndexVbo;
    GLuint dynamicVbo;
    GLuint dynamicIndexVbo;

    StaticModel* loadStaticModel(const String& name, const json::mValue& data);

};

#endif // CMODELMGR_H
