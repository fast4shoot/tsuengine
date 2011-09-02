#ifndef CGRAPHICSMGR_H
#define CGRAPHICSMGR_H

#include "glew/glew.h"
#include "elements/Program.h"
#include "elements/PointLight.h"
#include <list>

class CGraphicsMgr{
  public:
    void init();
    void draw();
    void initWorldView();
    void initGuiView();
    virtual ~CGraphicsMgr();
    void addLight(PointLight* light);
  private:
    void drawQuad();
    void checkFbo(GLuint fbo = GL_FRAMEBUFFER);
    GLuint m_fbo[2];
    GLuint m_g_textures[6];
    //GLuint m_depthStencilRb;
    int m_width;
    int m_height;
    float m_near;
    float m_far;
    Program* m_g_fill_program;
    Program* m_ambientProgram;
    Program* m_pointLightProgram;
    Program* m_finalProgram;
    Program* m_lightPrePassProgram;
    std::list<PointLight*> m_pointLights;
};

inline void CGraphicsMgr::addLight(PointLight* light){
  m_pointLights.push_back(light);
}

inline void CGraphicsMgr::drawQuad(){
  glBegin(GL_QUADS);
  glTexCoord2f(0., 1.);
  glVertex2f(-1., 1.);
  glTexCoord2f(0., 0.);
  glVertex2f(-1., -1. );

  glTexCoord2f(1., 0.);
  glVertex2f(1., -1.);
  glTexCoord2f(1., 1.);
  glVertex2f(1., 1.);
  glEnd();
}



#endif // CGRAPHICSMGR_H
