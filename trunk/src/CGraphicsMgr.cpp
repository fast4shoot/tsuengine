#include "CGraphicsMgr.h"
#include "CBaseEngine.h"
#include "CShaderMgr.h"
#include <boost/foreach.hpp>
#include "macros.h"

void CGraphicsMgr::init(){
  //TODO: calculate these from screen size
  m_height = 1024;
  m_width = 1024;
  m_near = 0.1;
  m_far = 1000.;

  /*
    first texture is diffuse color
    second contains normals in rgb and minimum light level in a
    third contains specular color
    fourth contains composed lights in the lighting pass
    fifth contains the depth and stencil buffers (24 + 8 bits)
  */
  glGenTextures(5, m_g_textures);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[4]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, m_g_textures[5]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  for(int i = 0; i < 4; i++){
    glBindTexture(GL_TEXTURE_2D, m_g_textures[i]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  }
  /*
    current hardware doesn't allow FBOs with separate depth and stecil, so we create a separate buffer for the G-Buffer filling pass,
    then copy the buffer to a texture, so we can access it in a shader
  */
  /*glGenRenderbuffers(1, &m_depthStencilRb);
  glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRb);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, m_width, m_height);*/

  glGenFramebuffers(2, m_fbo);

  m_g_fill_program = engine->shaders->getProgram("g_buffer_fill");

  m_ambientProgram = engine->shaders->getProgram("ambient_light");

  m_lightPrePassProgram = engine->shaders->getProgram("light_prepass");

  m_pointLightProgram = engine->shaders->getProgram("point_light");
  m_pointLightProgram -> findUniform("depthMap");
  m_pointLightProgram -> findUniform("normalMap");
  m_pointLightProgram -> findUniform("specularMap");
  m_pointLightProgram -> findUniform("ProjectionA");
  m_pointLightProgram -> findUniform("ProjectionB");
  m_pointLightProgram -> findUniform("lightPositionIn");
  m_pointLightProgram -> findUniform("lightSize");

  m_finalProgram = engine->shaders->getProgram("final_composition");
  m_finalProgram -> findUniform("diffuseMap");
  m_finalProgram -> findUniform("lightMap");


  addLight(new PointLight(vec3d(4., 1., 2.4), rgb(5.f, .1f, .1f), 2.5f ));
  addLight(new PointLight(vec3d(3., 1., 2.4), rgb(.1f, .1f, 5.f), 2.5f ));
  addLight(new PointLight(vec3d(2., 1., 2.4), rgb(.1f, 5.f, .1f), 2.5f ));
  addLight(new PointLight(vec3d(1.2, 1., 6.2), rgb(1.5f, 1.5f, 1.5f), 2.f ));


  engine->checkGl("End of graphics initialization");
  engine->log("Renderer successfully initiated");




  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

CGraphicsMgr::~CGraphicsMgr()
{
  //dtor
}

void CGraphicsMgr::draw(){

  engine->checkGl("CGraphicsMgr::draw()");

  /*{
    vec3d pozice = (*(m_pointLights.begin()++))->getPosition();
    pozice.y += sin(engine->getTime()*0.5);
  }*/

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo[0]);

  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_g_textures[0], 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_g_textures[1], 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_g_textures[2], 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_g_textures[4], 0);

  {
    GLenum mrt[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, mrt);
  }

  m_g_fill_program->use();

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glViewport(0, 0, m_width, m_height);
  initWorldView();
  glColor4f(1.,1.,1.,1.);
  engine->models->draw();

  m_g_fill_program->unuse();

  engine->checkGl("Starting GBuffer rendering");


  /*glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[0]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[1]);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[2]);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[3]);
  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[4]);*/
  //glActiveTexture(GL_TEXTURE0);

  //initWorldView();
  //glDisable(GL_DEPTH_TEST);
  //glDepthMask(GL_FALSE);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo[0]);

  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_g_textures[3], 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 0, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, 0, 0);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_g_textures[5], 0);

  glDrawBuffer(GL_COLOR_ATTACHMENT0);


  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo[1]);

  glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_g_textures[4], 0);
  glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_g_textures[0], 0);


  glDepthMask(GL_TRUE);
  glClearDepth(1.);
  glClear(GL_DEPTH_BUFFER_BIT);


  glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
  //engine->checkGl("glColorMask");

  glBlendFunc(GL_ONE, GL_ONE);
  //engine->checkGl("glBlendFunc");
  checkFbo(GL_READ_FRAMEBUFFER);
  checkFbo(GL_DRAW_FRAMEBUFFER);
  engine->checkGl("before blit");
  glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
  engine->checkGl("glBlitFramebuffer");

  glClearColor(0., 0., 0., 0.);
  //engine->checkGl("glClearColor");
  glClear(GL_COLOR_BUFFER_BIT);
  //engine->checkGl("glClear");



  glDepthMask(GL_FALSE);




  checkFbo();

  //glDisable(GL_DEPTH_TEST);
  //glDisable(GL_CULL_FACE);
  m_ambientProgram -> use();
  glColor4f(.1, .1, .1, .0);
  drawQuad();
  m_ambientProgram -> unuse();

  //glDepthFunc(GL_LEQUAL);

  glCullFace(GL_BACK);
  glEnable(GL_STENCIL_TEST);

  glColor4f(1., .5, .1, .0);

  checkFbo();

  glActiveTexture(GL_TEXTURE5);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[4]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[1]);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[2]);
  glActiveTexture(GL_TEXTURE0);

  BOOST_FOREACH(PointLight* light, m_pointLights){
    glPushMatrix();
    light -> transform();

    m_lightPrePassProgram -> use();
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
    glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);

    light -> drawVolume();
    engine->checkGl("midLight");
    glPopMatrix();
    m_pointLightProgram -> use();
    glDisable(GL_DEPTH_TEST);
    //m_pointLightProgram -> setUniformf("size", light -> getSize());
    //m_pointLightProgram -> setUniformi("scrSize", m_width, m_height);
    m_pointLightProgram -> setUniformi("depthMap", 5);
    m_pointLightProgram -> setUniformi("normalMap", 1);
    m_pointLightProgram -> setUniformi("specularMap", 2);
    m_pointLightProgram -> setUniformf("ProjectionA", m_far / (m_far - m_near));
    m_pointLightProgram -> setUniformf("ProjectionB", (-m_far * m_near) / (m_far - m_near));
    m_pointLightProgram -> setUniformf("lightPositionIn", light->getPosition().x, light->getPosition().y, light->getPosition().z);
    m_pointLightProgram -> setUniformf("lightSize", light->getSize());

    glColor4f(light->getColor().r, light->getColor().g, light->getColor().b, .0);
    glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
    glStencilOpSeparate(GL_FRONT_AND_BACK, GL_REPLACE, GL_REPLACE, GL_REPLACE);
    //light -> drawVolume();
    drawQuad();

  }
  engine->checkGl("afterLight");

  glDisable(GL_STENCIL_TEST);
  glDepthMask(GL_TRUE);

  m_pointLightProgram -> unuse();

  glCullFace(GL_BACK);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBlendFunc(GL_ONE, GL_ZERO);

  glViewport(0, 0, engine->getScreenWidth(), engine->getScreenHeight());
  engine->checkGl("glViewport");

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[0]);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, m_g_textures[3]);
  glActiveTexture(GL_TEXTURE0);

  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glColor4f(1., 1., 1., 1.);
  m_finalProgram -> use();
  m_finalProgram -> setUniformi("diffuseMap",0);
  //m_finalProgram -> setUniformi("normalMap",1);
  m_finalProgram -> setUniformi("lightMap",3);
  drawQuad();
  m_finalProgram -> unuse();

  engine->checkGl("World render ended");
  initGuiView();
  engine->checkGl("Starting gui rendering");
  engine->gui->drawElements();
  engine->checkGl("Rendering ended");

}

void CGraphicsMgr::initWorldView(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f,(GLfloat)engine->getScreenWidth()/(GLfloat)engine->getScreenHeight(), m_near, m_far);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  engine->camera->doTransform();
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthFunc(GL_LEQUAL);
}

void CGraphicsMgr::initGuiView(){
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (0, engine->getScreenWidth(), engine->getScreenHeight(), 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glCullFace(GL_BACK);
  glDisable(GL_TEXTURE_2D);
  //glTranslatef(0.,SCREENHEIGHT/*+0.375*/,0.0);
  //glScalef(1.0,-1.0,1.0);
}

void CGraphicsMgr::checkFbo(GLuint fbo){
  GLuint err = glCheckFramebufferStatus(fbo);
  if(err != GL_FRAMEBUFFER_COMPLETE){
    engine->log(format("FBO is fucked: %d") % err);
  }
}
