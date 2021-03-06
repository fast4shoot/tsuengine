#include "CGuiMgr.h"
#include "gui/CGuiPanel.h"
#include "gui/CMainMenu.h"
#include "const.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "gui/CCenteredWindow.h"
#include "CBaseEngine.h"
#include "CBgFade.h"

CGuiMgr::CGuiMgr(){}

void CGuiMgr::init(){
  _keyboardReceiver=NULL;
  m_cursor = true;
  m_escape = false;
  m_hud = new CGuiPanel(vec2d(0.,0.),vec2d(engine->getScreenWidth(),engine->getScreenHeight()));
  _basePanel=new CGuiPanel(vec2d(0.,0.),vec2d(engine->getScreenWidth(),engine->getScreenHeight()));
  _basePanel->addChild(m_hud);
  _basePanel->addChild(m_fade = new CBgFade());
  _basePanel->addChild(m_mainMenu = new CMainMenu());

  cursorMat = engine->materials->getPersistentMaterial("system/cursor");

}

void CGuiMgr::update(){
  _basePanel->doRemoval();
  if(m_cursor){
    for(int i=0;i<NUMBUTTONS;i++){
      if(engine->input->buttonPressed((MouseButton)i)){
        _basePanel->handleMouseClick(engine->input->getCursor(),(MouseButton) i,false);
      }
      if(engine->input->buttonDepressed((MouseButton)i)){
        _basePanel->handleMouseClick(engine->input->getCursor(),(MouseButton) i,true);
      }
    }
    _basePanel->handleMouseMove(engine->input->getCursor(),true);
    if(_keyboardReceiver && _keyboardReceiver->isVisible()){
      String input = engine->input->getString();
      if(!input.empty()){
        _keyboardReceiver->onKeyboard(input);
      }
    }
  }
  if(m_escape && engine->input->keyPressed(DIK_ESCAPE)){
    bool visible = !m_mainMenu->getVisible();
    showMainMenu(visible);
    engine->setTimeScale(!visible * 1.f);
  }
}

void CGuiMgr::drawElements(){
  glDisable(GL_TEXTURE_2D);
  _basePanel->doDraw();

  if(m_cursor){
    float x = engine->input->getCursorX();
    float y = engine->input->getCursorY();
    cursorMat->bind();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glColor4f(1.f, 1.f, 1.f, 0.9f);
      glTexCoord2d(0,0);
      glVertex2f(x+0.0, y+24.0);
      glTexCoord2d(1,0);
      glVertex2f(x+24.0, y+24.0);
      glTexCoord2d(1,1);
      glVertex2f(x+24.0, y+0.0);
      glTexCoord2d(0,1);
      glVertex2f(x+0.0, y+0.0);
    glEnd();
    cursorMat->unbind();
    glDisable(GL_TEXTURE_2D);
  }

}

void CGuiMgr::addElement(CGuiPanel* element){
  _basePanel->addChild(element);
}

void CGuiMgr::showMainMenu(bool val){
  m_mainMenu->setVisible(val);
  m_cursor = val;
  if(!engine->map->isBackground()){
    if(val)
      fadeTo(.5, 3.);
    else
      fadeTo(0., .0);
  }
}

void CGuiMgr::fadeTo(double alpha, double time){
  m_fade->fadeTo(alpha, time);
}

void CGuiMgr::stopKeyboardReceiving(CGuiPanel* panel){
  if(isKeyboardReceiver(panel)){
    _keyboardReceiver = NULL;
  }
}
