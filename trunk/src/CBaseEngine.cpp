#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "CBaseEngine.h"
#include "CBaseEntity.h"
#include "exceptions.h"
#include "macros.h"
#include "CInputMgr.h"
#include "GLFT_Font.hpp"
#include "utils.h"
#include "const.h"

#include "WhiteBox.h"

void CBaseEngine::init(){
  drawPos.x=drawPos.y=0.0f;  //this is old, remainder from sparta engine
  lastClock=clock();
  timeScale=1.0f;
  time=0.0;
  realTime=0.0;
  frameCount=0;
  input = new CInputMgr();
  input->init();
  gui = new CGuiMgr();
  gui->init();



  //fnt.open("gunplay.ttf", 16);
  fnt.open("arial.TTF",14);


}

void CBaseEngine::destroy(){
  delete input;
}

void CBaseEngine::setDrawPos(double x, double y, double z){
  drawPos.set(x,y,z);
}

void CBaseEngine::setDrawPos(vec3d pos){
  drawPos=pos;
}

void CBaseEngine::setDrawColor(float r, float g, float b, float a){
  drawColor.set(r,g,b,a);
}

void CBaseEngine::setDrawColor(rgba col){
  drawColor=col;
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
    //TODO: make it use CEntMgr
    if(entityTable[i]){
      entityTable[i]->think();
    }
  }*/

  /*
  if(input->keyPressed(DIK_ESCAPE)){
    PostQuitMessage(0);
  }*/
}

void CBaseEngine::drawModel(int wmId){
  glPushMatrix();

  glPopMatrix();
}

void CBaseEngine::drawScene(){
  frameCount++;

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);


  //world drawing settings
  initWorldView();

  gluLookAt(0,0,10,100,0,0,0,0,1);
  glTranslatef(50.,0.,0.);


  /*
   * GUI drawing
   */

  initGuiView();

  gui->drawElements();

  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  fnt.drawText(2, 2,"realTime: %.1lf\nFPS: %.10lf\nFrame: %llu",getRealTime(),fps,getFrameCount());
  fnt.drawText(208+64*8,32,"L: %d, R: %d, M: %d, X: %.1f, Y: %.1f",input->buttonDown(LMB),input->buttonDown(RMB),input->buttonDown(MMB),input->getX(),input->getY());

  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(input->getX(),input-> getY(),0.0f);


  glBegin(GL_QUADS);
    glColor4f(1.0f, 0.0f, 0.0f,0.8f);
    glVertex2f(0.0,24.0);
    glVertex2f(12.0,24.0);
    glVertex2f(12.0,0.0);
    glVertex2f(0.0,0.0);
  glEnd();
  glPopMatrix();

  SwapBuffers (hDC);
}

void CBaseEngine::initWorldView(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0f,(GLfloat)SCREENWIDTH/(GLfloat)SCREENHEIGHT,0.1f,100000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void CBaseEngine::initGuiView(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (0, SCREENWIDTH, 0, SCREENHEIGHT);
  glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
  glLoadIdentity();
  glTranslatef(0.,SCREENHEIGHT/*+0.375*/,0.0);
  glScalef(1.0,-1.0,1.0);
}

double CBaseEngine::getTime(){
  return time;
}

double CBaseEngine::getLastTime(){
  return lastTime;
}

double CBaseEngine::getTimeDelta(){
  return timeDelta;
}

double CBaseEngine::getRealTime(){
  return realTime;
}

double CBaseEngine::getLastRealTime(){
  return lastRealTime;
}

double CBaseEngine::getRealTimeDelta(){
  return realTimeDelta;
}

unsigned long long int CBaseEngine::getFrameCount(){
  return frameCount;
}

double CBaseEngine::getFPS(){
  return fps;
}

void CBaseEngine::createEntity(std::string name){}
