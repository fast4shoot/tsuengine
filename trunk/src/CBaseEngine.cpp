#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "CBaseEngine.h"
#include "CBaseEntity.h"
#include "exceptions.h"
#include "macros.h"
#include "CInputMgr.h"
#include "utils/math.h"
#include "const.h"
#include "Font.h"
#include "utils/stringUtils.h"
#include "gui/CText.h"
#include "version.h"
#include "libs/json/json.h"

CBaseEngine* engine;

void CBaseEngine::init(){
  lastClock=clock();
  timeScale=1.0f;
  time=0.0;
  realTime=0.0;
  frameCount=0;

  input = new CInputMgr();
  input->init();
  fonts=new CFontMgr();
  systemFont=fonts->getFont("ARIALUNI.TTF",14.);
  fonts->getFont("ARIALUNI.TTF",55.);
  materials=new CMaterialMgr();
  gui = new CGuiMgr();
  gui->init();
  log(sformat("TSUEngine verze %d.%d.%d revize %d",AutoVersion::MAJOR,AutoVersion::MINOR,AutoVersion::BUILD,AutoVersion::REVISION));
  json_spirit::mValue value;
  json_spirit::read( "{\"rofl\": [1337.2, 2, 3]}", value );

  //log(sformat("přečteno %d",value.get_obj().find("rofl")->second.get_int()));
  vec3d rofl;
  rofl.fromJson(value.get_obj().find("rofl")->second);
  double x = rofl.x;
  log(sformat("přečten vektor: %f, %f, %f",x, rofl.y, rofl.z));

  testMat=materials->getMaterial("wall1");
  cursorMat=materials->getMaterial("system/cursor");
}

/*int CBaseTransmission() {
  if (car->getRadiciPaka().pushed()) {
    car.setGear(car->getRadiciPaka().getValue());
  }

  return 5;
}*/

void CBaseEngine::destroy(){

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

  /*
  for(i=0;i<ENT_MAX;i++){
    //TODO: finish and use CEntMgr
    if(entityTable[i]){
      entityTable[i]->think();
    }
  }*/


  if(input->keyPressed(DIK_ESCAPE)){
    quit();
  }
}

void CBaseEngine::drawScene(){
  frameCount++;

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


  initWorldView();

  gluLookAt(0,0,10,100,0,0,0,0,1);

  glTranslatef(50.,0.,0.);
  glRotatef(getTime()*90,0,0,1);
  glColor4f(1.,1.,1.,1.);

  glEnable(GL_TEXTURE_2D);
  testMat->bind();
  glBegin(GL_QUADS);
    glColor3f(1.,1.,1.);
    glNormal3i(0,0,1);
    glTexCoord2d(0,0);
    glVertex3f(0.,-20.,-20.);
    glTexCoord2d(0,1);
    glVertex3f(0.,20.,-20.);
    glTexCoord2d(1,1);
    glVertex3f(-40.,20.,-20.);
    glTexCoord2d(1,0);
    glVertex3f(-40.,-20.,-20.);

    glNormal3i(-1,0,0);
    glTexCoord2d(0,0);
    glVertex3f(0.,-20.,-20.);
    glTexCoord2d(0,1);
    glVertex3f(0.,-20.,20.);
    glTexCoord2d(1,1);
    glVertex3f(0.,20.,20.);
    glTexCoord2d(1,0);
    glVertex3f(0.,20.,-20.);

    glNormal3i(0,-1,0);
    glTexCoord2d(1,0);
    glVertex3f(0.,-20.,-20.);
    glTexCoord2d(0,0);
    glVertex3f(-40.,-20.,-20.);
    glTexCoord2d(0,1);
    glVertex3f(-40.,-20.,20.);
    glTexCoord2d(1,1);
    glVertex3f(0.,-20.,20.);
  glEnd();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
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
  gluPerspective(70.0f,(GLfloat)SCREENWIDTH/(GLfloat)SCREENHEIGHT,0.1f,100000.0f);
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
  gluOrtho2D (0, SCREENWIDTH, SCREENHEIGHT, 0);
  glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
  glLoadIdentity();
  //glTranslatef(0.,SCREENHEIGHT/*+0.375*/,0.0);
  //glScalef(1.0,-1.0,1.0);
}

void CBaseEngine::log(const String& text){
  static bool firstLog=true;
  String console=_consoleOutput->getText();
  if(!firstLog){
    console.append("\n");
  }
  firstLog=false;
  console.append(text);
  _consoleOutput->setText(console);
}



