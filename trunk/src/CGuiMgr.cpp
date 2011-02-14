#include "CGuiMgr.h"
#include "gui/CGuiPanel.h"
#include "gui/CMainMenu.h"
#include "const.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "gui/CCenteredWindow.h"

CGuiMgr::CGuiMgr(){}

void CGuiMgr::init(){
  _keyboardReceiver=NULL;
  _basePanel=new CGuiPanel(vec2d(0.,0.),vec2d(engine->getScreenWidth(),engine->getScreenHeight()));

  _basePanel->addChild(new CMainMenu());


}

void CGuiMgr::update(){
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
    }else{
    }
  }
}

void CGuiMgr::drawElements(){
  glDisable(GL_TEXTURE_2D);
  _basePanel->draw();
  _basePanel->drawChildren();
}
