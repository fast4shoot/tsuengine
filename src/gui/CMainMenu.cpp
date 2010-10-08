#include "CMainMenu.h"

#include "CCenteredWindow.h"
#include "CCheckBox.h"

CMainMenu::CMainMenu():
  CGuiPanel(vec2d(0,0),vec2d(SCREENWIDTH,SCREENHEIGHT))
{
  fgColor.set(1., 1., 1., .7);
  bgColor.set(.25, .25, .25, .4);

  panelWidth=200;

  CGuiPanel* temp;

  addChild(new CLabel(vec2d(20,40),vec2d(15,15),L"The"));
  addChild(new CLabel(vec2d(20,55),vec2d(30,30),L"TSUEngine"));

  temp=new CButton(vec2d(20,100),vec2d(160,30),L"Nová hra");
  temp->addActionListener(new CActionListener(this,1));
  addChild(temp);

  temp=new CButton(vec2d(20,135),vec2d(160,30),L"Nastavení");
  temp->addActionListener(new CActionListener(this,2));
  addChild(temp);

  temp=new CButton(vec2d(20,SCREENHEIGHT-160),vec2d(160,30),L"Ukončit");
  temp->addActionListener(new CActionListener(this,0));
  addChild(temp);

  addChild(settings=new CCenteredWindow(vec2d(400,300), L"Nastavení"));
  settings->setVisible(false);

  addChild(newGame=new CCenteredWindow(vec2d(500,230), L"Nová hra"));
  newGame->setVisible(false);
  newGame->addChild(new CLabel(vec2d(50,70), vec2d(150,70),L"THE GAME!"));

  addChild(new CCheckBox(vec2d(20,170), vec2d(160,16), L"Test"));
  addChild(new CCheckBox(vec2d(20,190), vec2d(160,16), L"Další test"));
  addChild(new CCheckBox(vec2d(20,210), vec2d(160,16), L"Jinej test"));
  addChild(new CCheckBox(vec2d(20,230), vec2d(160,16), L"Úplně jinej test"));
}

void CMainMenu::draw(){
  drawHorizontalGradient(0,0,panelWidth-1,getH(),fgColor,bgColor);
  setDrawColor(fgColor);
  drawQuad(panelWidth-1,0,1,getH());
}

void CMainMenu::actionPerformed(int id){
  switch(id){
    case 1:
      newGame->setVisible(true);
      newGame->requestFocus();
      break;
    case 2:
      settings->setVisible(true);
      settings->requestFocus();
      break;
    case 0:
      engine->quit();
      break;
  }
}
