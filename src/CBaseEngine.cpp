#include <cmath>
#include <windows.h>
#include <fstream>

#include "GL/glew.h"

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
#include "CShaderMgr.h"
#include "CGraphicsMgr.h"

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

  std::ifstream conf("config.json");
  json::read(conf, m_config);
  conf.close();


  input = new CInputMgr();
  input->init();

  camera = new CCameraMgr();
  fonts=new CFontMgr();
  systemFont=fonts->getFont(getConfig<String>("font"),14.);
  fonts->getFont(getConfig<String>("font"),55.);
  shaders = new CShaderMgr();
  materials=new CMaterialMgr();
  gui = new CGuiMgr();
  physics = new CPhysicsMgr();

  models = new CModelMgr();
  gui->init();
  ents = new CEntMgr();

  map = new CMapMgr();

  graphics = new CGraphicsMgr();
  graphics -> init();

  m_ready=true;
  log(sformat("TSUEngine verze %d.%d.%d revize %d",AutoVersion::MAJOR,AutoVersion::MINOR,AutoVersion::BUILD,AutoVersion::REVISION));
  log(sformat("OpenGL verze %s, GLSL verze %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION)));
  log("Engine is now ready");
  ents->print();


  //testMat=materials->getMaterial("wall1");


  /*
  testMdl=models->getModel("barrel");
  testMdl->setPosition(vec3d(1., 5., -3.));
  testMdl->setPhysics(P_DYNAMIC);
  */


  map->load(getConfig<String>("bgMap"));

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

  map->update();

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

  m_tempConsoleOutput->setText("");

  input->update();
  gui->update();
  physics->update();

  BOOST_FOREACH(Thinker* thinker, m_thinkers){
    thinker->think();
  }

  ents->doThink();
/*
  testMdl->setRotation(0, getTime()*-1500, 0 );
  testMdl2->setRotation(0, getTime()*1500, 0 );
  testMdl3->setRotation(getTime()*2, 0 , 0 );*/
}

void CBaseEngine::drawScene(){


  graphics->draw();

  SwapBuffers (hDC);
  frameCount++;
}



void CBaseEngine::logAppend(const String& text){
  static bool firstLog=true;
  m_logFile << text;
  m_logFile.flush();
  if(isReady()){
    String console=_consoleOutput->getText();
    console.append(text);
    _consoleOutput->setText(console);
    m_tempConsoleOutput->setText(m_tempConsoleOutput->getText()+text);
  }
}

void CBaseEngine::debug(const String& text){
  //m_tempConsoleOutput->setText(m_tempConsoleOutput->getText()+text+"\n");
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

void CBaseEngine::checkGl(const String& text){
  GLenum err;
  while((err = glGetError())!=GL_NO_ERROR){
    log(sformat("GL error %d: %s (%s)",err,gluErrorString(err),text.c_str()));
  }
}

void CBaseEngine::resetGameTime(){
  time = 0.;
  lastTime = 0.;
  timeDelta = 0.;
}

void CBaseEngine::registerThinker(Thinker* thinker){
  m_thinkers.push_back(thinker);
}

