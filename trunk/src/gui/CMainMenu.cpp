#include "CMainMenu.h"

#include "CCenteredWindow.h"
#include "CCheckBox.h"
#include "CTextField.h"
#include "CConsole.h"

CMainMenu::CMainMenu():
  CGuiPanel(vec2d(0,0),vec2d(SCREENWIDTH,SCREENHEIGHT))
{
  fgColor.set(1., 1., 1., .7);
  bgColor.set(.25, .25, .25, .4);

  panelWidth=200;

  CGuiPanel* temp;

  addChild(new CLabel(vec2d(20,40),vec2d(15,15),"The"));
  addChild(new CLabel(vec2d(20,55),vec2d(30,30),"TSUEngine"));

  addChild(temp=new CButton(vec2d(20,100),vec2d(160,30),"Nová hra"));
  temp->addActionListener(new CActionListener(this,1));

  addChild(temp=new CButton(vec2d(20,135),vec2d(160,30),"Nastavení"));
  temp->addActionListener(new CActionListener(this,2));

  addChild(temp=new CButton(vec2d(20,170),vec2d(160,30),"Konzole"));
  temp->addActionListener(new CActionListener(this,3));

  temp=new CButton(vec2d(20,SCREENHEIGHT-160),vec2d(160,30),"Ukončit");
  temp->addActionListener(new CActionListener(this,0));
  addChild(temp);

  addChild(_settings=new CCenteredWindow(vec2d(400,300), "Nastavení"));
  _settings->setVisible(false);
  _settings->addChild(new CTextField(vec2d(20, 50), vec2d(160,24)));

  addChild(_newGame=new CCenteredWindow(vec2d(500,230), "Nová hra"));
  _newGame->setVisible(false);

  addChild(_console=new CConsole());
  _console->setVisible(false);


  addChild(new CCheckBox(vec2d(20,210), vec2d(160,16), "Jinej test"));
  addChild(new CCheckBox(vec2d(20,230), vec2d(160,16), "Úplně jinej test"));
  addChild(new CCheckBox(vec2d(20,250), vec2d(160,16), "A ještě něco"));


}

void CMainMenu::draw(){
  drawHorizontalGradient(0,0,panelWidth-1,getH(),fgColor,bgColor);
  setDrawColor(fgColor);
  drawQuad(panelWidth-1,0,1,getH());
}

void CMainMenu::actionPerformed(int id){
  switch(id){
    case 1: displayElement(_newGame); break;
    case 2: displayElement(_settings); break;
    case 3: displayElement(_console); break;
    case 0:
      engine->quit();
      break;
  }
}
