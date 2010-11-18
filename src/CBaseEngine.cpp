#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "CBaseEngine.h"
#include "CBaseEntity.h"
#include "exceptions.h"
#include "macros.h"
#include "CInputMgr.h"
#include "utils.h"
#include "const.h"
#include "Font.h"
#include "utils/stringUtils.h"
#include "gui/CText.h"
#include "version.h"
#include "json_spirit/json_spirit.h"

CBaseEngine* engine;

void CBaseEngine::init(){
  drawPos.x=drawPos.y=0.0f;  //this is old, remainder from sparta engine
  lastClock=clock();
  timeScale=1.0f;
  time=0.0;
  realTime=0.0;
  frameCount=0;

  input = new CInputMgr();
  input->init();
  fonts=new CFontMgr();
  systemFont=fonts->getFont(L"ARIALUNI.TTF",14.);
  fonts->getFont(L"ARIALUNI.TTF",55.);
  gui = new CGuiMgr();
  gui->init();
  log(swformat(L"TSUEngine verze %d.%d.%d revize %d",AutoVersion::MAJOR,AutoVersion::MINOR,AutoVersion::BUILD,AutoVersion::REVISION));
  json_spirit::wmValue value;
  json_spirit::read( L"{\"rofl\": 42}", value );

  log(swformat(L"přečteno %d",value.get_obj().find(L"rofl")->second.get_int()));
}

/*int CBaseTransmission() {
  if (car->getRadiciPaka().pushed()) {
    car.setGear(car->getRadiciPaka().getValue());
  }

  return 5;
}*/

void CBaseEngine::destroy(){
  delete gui;
  delete fonts;
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


  if(input->keyPressed(DIK_ESCAPE)){
    quit();
  }
}

void CBaseEngine::drawModel(int wmId){
  glPushMatrix();

  glPopMatrix();
}

void CBaseEngine::drawScene(){
  frameCount++;

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


  //world drawing settings
  initWorldView();

  gluLookAt(0,0,10,100,0,0,0,0,1);

  glTranslatef(50.,0.,0.);
  glRotatef(getTime()*90,0,0,1);
  glColor4f(1.,1.,1.,1.);

  glBegin(GL_QUADS);
    glColor3f(0.,0.,1.);
    glNormal3i(0,0,1);
    glVertex3f(0.,-10.,0.);
    glVertex3f(-20.,-10.,0.);
    glVertex3f(-20.,10.,0.);
    glVertex3f(0.,10.,0.);

    glColor3f(1.,.5,1.);
    glNormal3i(-1,0,0);
    glVertex3f(0.,-10.,0.);
    glVertex3f(0.,-10.,10.);
    glVertex3f(0.,10.,10.);
    glVertex3f(0.,10.,0.);

    glColor3f(1.,1.,0.);
    glNormal3i(0,-1,0);
    glVertex3f(0.,-10.,0.);
    glVertex3f(0.,-10.,10.);
    glVertex3f(-20.,-10.,10.);
    glVertex3f(-20.,-10.,0.);
  glEnd();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  /*
   * GUI drawing
   */

  initGuiView();

  gui->drawElements();

  glColor3f(1.0f, 1.0f, 1.0f);
  systemFont->render(swformat(L"realTime: %.1lf | FPS: %.1lf | Frame: %llu",getRealTime(),fps,getFrameCount()),14.);
  glPushMatrix();
  glTranslatef(0.,16., 0.);
  //systemFont->render(_log,14.);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(input->getX(),input-> getY(),0.0f);
  glBegin(GL_QUADS);
    glColor4f(1.0f, 0.0f, 0.0f,0.5f);
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
  gluPerspective(65.0f,(GLfloat)SCREENWIDTH/(GLfloat)SCREENHEIGHT,0.1f,1000000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
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



void CBaseEngine::createEntity(std::string name){}

void CBaseEngine::log(const std::wstring& text){
  static bool firstLog=true;
  String console=_consoleOutput->getText();
  if(!firstLog){
    console.append(L"\n");
  }
  firstLog=false;
  console.append(text);
  _consoleOutput->setText(console);
}



