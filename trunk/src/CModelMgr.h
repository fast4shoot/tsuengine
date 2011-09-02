#ifndef CMODELMGR_H
#define CMODELMGR_H

#include "typedefs.h"
#include "datatypes.h"
#include "glew/glew.h"
#include <map>
#include <vector>
#include "json/json.h"

class Model;
class StaticModel;
class StaticModelImpl;

class CModelMgr{
  typedef std::map<String,StaticModelImpl*> StaticModelList;
  typedef std::vector<Model*> ModelHandleList;
  typedef std::map<String,ModelType> ModelTypeMap;
  public:
    CModelMgr();
    Model*  getModel(const String& name);
    void uploadData();
    void draw();

    void removeAll();

  protected:
    void generateBuffers();
    void deleteBuffers();
    bool m_buffersGenerated;

    StaticModelList staticModels;
    ModelHandleList modelHandles;
    ModelTypeMap modelTypeMap;

    GLuint m_buffers[4];

    GLuint staticVbo;
    GLuint staticIndexVbo;
    GLuint dynamicVbo;
    GLuint dynamicIndexVbo;

    StaticModelImpl* loadStaticModel(const String& name, const json::mValue& data);

};

#endif // CMODELMGR_H
