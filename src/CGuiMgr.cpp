#include "CGuiMgr.h"
#include "CGuiPanel.h"
#include "TestPanel.h"
#include "const.h"
#include "macros.h"
#include "CBaseEngine.h"
CGuiMgr::CGuiMgr(){}

void CGuiMgr::init(){
  basePanel=new CGuiPanel(0.,0.,SCREENWIDTH,SCREENHEIGHT);

  basePanel->addChild(new TestPanel(50.,50.,540.,380.));
  /*basePanel->addChild(new TestPanel(150.,150.,200.,200.));
  basePanel->addChild(new TestPanel(200.,200.,200.,200.));
  basePanel->addChild(new TestPanel(250.,250.,200.,200.));
  basePanel->addChild(new TestPanel(300.,300.,200.,200.));*/
}

void CGuiMgr::update(){
  for(int i=0;i<NUMBUTTONS;i++){
    if(engine->input->buttonPressed((MouseButton)i)){
      basePanel->handleMouseClick(engine->input->getCursor(),(MouseButton) i,false);
    }
    if(engine->input->buttonDepressed((MouseButton)i)){
      basePanel->handleMouseClick(engine->input->getCursor(),(MouseButton) i,true);
    }
  }
  basePanel->handleMouseMove(engine->input->getCursor(),true);
}

void CGuiMgr::drawElements(){
  glDisable(GL_TEXTURE_2D);
  basePanel->draw();
  basePanel->drawChildren();
}
