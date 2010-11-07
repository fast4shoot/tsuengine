#include "CGuiMgr.h"
#include "CGuiPanel.h"
#include "CMainMenu.h"
#include "const.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "CCenteredWindow.h"

CGuiMgr::CGuiMgr(){}

void CGuiMgr::init(){
  _basePanel=new CGuiPanel(vec2d(0.,0.),vec2d(SCREENWIDTH,SCREENHEIGHT));

  //basePanel->addChild(new TestPanel(vec2d(170., 50.), vec2d(SCREENWIDTH-180, 330.)));
  _basePanel->addChild(new CMainMenu());

  //basePanel->addChild(new CCenteredWindow(vec2d(300, 250), L"Okno"));
  /*
  basePanel->addChild(new CButton(vec2d(10.,50.), vec2d(150.,30.), std::wstring(L"Button 1!")));
  basePanel->addChild(new CButton(vec2d(10.,90.), vec2d(150.,30.), std::wstring(L"Button 2!")));
  basePanel->addChild(new CButton(vec2d(10.,130.), vec2d(150.,30.), std::wstring(L"Button 3!")));
  */
  _keyboardReceiver=NULL;
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
    std::wstring input = engine->input->getString();
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
