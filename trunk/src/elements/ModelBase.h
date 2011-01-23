#ifndef MODELBASE_H
#define MODELBASE_H

#include "glew/glew.h"

class ModelBase{
  public:
    virtual ~ModelBase(){};
    virtual void draw()=0;
    virtual void assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset);
    virtual int getVertexCount() const=0;
    virtual int getIndexCount() const=0;
    virtual void uploadData()=0;
  protected:
    GLuint m_vbo;
    int m_vboOffset;
    GLuint m_indexVbo;
    int m_indexVboOffset;

};

inline void ModelBase::assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset){
  m_vbo = vbo;
  m_vboOffset = vboOffset;
  m_indexVbo = indexVbo;
  m_indexVboOffset = indexVboOffset;
}

#endif // MODELBASE_H
