#ifndef CMODELMGR_H
#define CMODELMGR_H

#include "datatypes.h"
#include "glew/glew.h"
#include "elements/Model.h"
#include "elements/StaticModel.h"

class CModelMgr{
  typedef std::map<String,StaticModel*> StaticModelList;
  typedef std::vector<Model*> ModelHandleList;
  typedef std::map<String,ModelType> ModelTypeMap;
  public:
    CModelMgr();
    Model*  getModel(String name);
    void uploadData();
    void draw();

  protected:
    StaticModelList staticModels;
    ModelHandleList modelHandles;
    ModelTypeMap modelTypeMap;
    GLuint staticVbo;
    GLuint staticIndexVbo;
    GLuint dynamicVbo;
    GLuint dynamicIndexVbo;

    StaticModel* loadStaticModel(const String& name, const json::mValue& data);

};

#endif // CMODELMGR_H
