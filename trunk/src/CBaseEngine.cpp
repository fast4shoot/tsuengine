#include <cmath>
#include <windows.h>
#include <fstream>

#include "glew/glew.h"

#include "CBaseEngine.h"
#include "entities/CBaseEntity.h"
#include "exceptions.h"
#include "macros.h"
#include "CInputMgr.h"
#include "utils/math.h"
#include "const.h"
#include "Font.h"
#include "utils/stringUtils.h"
#include "gui/CText.h"
#include "version.h"
#include "json/json.h"
#include "vec3d.h"

#include "elements/StaticModel.h"

CBaseEngine* engine;

CBaseEngine::CBaseEngine(){
  m_ready = false;
  timeScale=1.0f;
  time=0.0;
  realTime=0.0;
  frameCount=0;
}

void CBaseEngine::init(){
  lastClock=clock();

  m_logFile.open("tsuengine.log");

  glewInit();

  input = new CInputMgr();
  input->init();
  fonts=new CFontMgr();
  systemFont=fonts->getFont("ARIALUNI.TTF",14.);
  fonts->getFont("ARIALUNI.TTF",55.);
  materials=new CMaterialMgr();
  gui = new CGuiMgr();
  physics = new CPhysicsMgr();
  models = new CModelMgr();
  gui->init();
  ents = new CEntMgr();
  map = new CMapMgr();
  m_ready=true;
  log(sformat("TSUEngine verze %d.%d.%d revize %d",AutoVersion::MAJOR,AutoVersion::MINOR,AutoVersion::BUILD,AutoVersion::REVISION));
  log(sformat("OpenGL verze %s",glGetString(GL_VERSION)));
  ents->print();


  //testMat=materials->getMaterial("wall1");
  cursorMat=materials->getPersistentMaterial("system/cursor");

  /*
  testMdl=models->getModel("barrel");
  testMdl->setPosition(vec3d(1., 5., -3.));
  testMdl->setPhysics(P_DYNAMIC);
  */


  map->load("test");
  models->uploadData();

}

void CBaseEngine::destroy(){
  delete map;
  delete ents;
  delete models;
  delete gui;
  delete materials;
  delete fonts;
  delete input;
}

void CBaseEngine::think(){
  realTimeDelta=(double)((clock()-lastClock)/(double)CLOCKS_PER_SEC);

  lastClock=clock();

  lastRealTime=realTime;
  realTime+=realTimeDelta;

  lastTime=time;
  timeDelta=realTimeDelta*timeScale;
  time+=timeDelta;


  static double timeBefore;
  static unsigned long long int frameBefore;
  if((getRealTime()-timeBefore) > 0.05){
    fps=(double)(getFrameCount()-frameBefore)/(getRealTime()-timeBefore);
    timeBefore=getRealTime();
    frameBefore=getFrameCount();
  }


  input->update();
  gui->update();
  physics->update();
  ents->doThink();


  if(input->keyPressed(DIK_ESCAPE)){
    quit();
  }

  if(input->keyPressed(DIK_Q)){
    map->unload();
  }

/*
  testMdl->setRotation(0, getTime()*-1500, 0 );
  testMdl2->setRotation(0, getTime()*1500, 0 );
  testMdl3->setRotation(getTime()*2, 0 , 0 );*/
}

void CBaseEngine::drawScene(){
  frameCount++;

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


  initWorldView();

  gluLookAt(0, 0.50, 0, 0, 0.20, -3.00 , 0, 1, 0);

  glTranslatef(0.,0.,-10.00);
  glRotatef(getTime(),0,1,0);
  glColor4f(1.,1.,1.,1.);

  models->draw();


  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  /*
   * GUI drawing
   */

  initGuiView();

  gui->drawElements();

  glPushMatrix();
  glTranslatef(input->getX(),input-> getY(),0.0f);
  cursorMat->bind();
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
    glColor4f(1.f, 1.f, 1.f, 0.9f);
    glTexCoord2d(0,0);
    glVertex2f(0.0,24.0);
    glTexCoord2d(1,0);
    glVertex2f(24.0,24.0);
    glTexCoord2d(1,1);
    glVertex2f(24.0,0.0);
    glTexCoord2d(0,1);
    glVertex2f(0.0,0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  SwapBuffers (hDC);
}

void CBaseEngine::initWorldView(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f,(GLfloat)getScreenWidth()/(GLfloat)getScreenHeight(),0.1f,100000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void CBaseEngine::initGuiView(){
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (0, getScreenWidth(), getScreenHeight(), 0);
  glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
  glLoadIdentity();
  //glTranslatef(0.,SCREENHEIGHT/*+0.375*/,0.0);
  //glScalef(1.0,-1.0,1.0);
}

void CBaseEngine::logAppend(const String& text){
  static bool firstLog=true;
  m_logFile << text << std::endl;
  if(isReady()){
    String console=_consoleOutput->getText();

    console.append(text);
    _consoleOutput->setText(console);
  }
}

void CBaseEngine::log(const String& text){
  static bool firstLog=true;
  if(firstLog){
    logAppend(text);
    firstLog=false;
  }else{
    logAppend("\n"+text);
  }
}

void CBaseEngine::checkGl(){
  GLenum err;
  while((err = glGetError())!=GL_NO_ERROR){
    log(sformat("GL error %d: %s",err,gluErrorString(err)));
  }
}
