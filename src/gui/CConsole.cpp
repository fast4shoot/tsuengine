#include "CConsole.h"
#include "CText.h"
#include "CScrollable.h"
#include "CBox.h"
#include "CBaseEngine.h"

CConsole::CConsole():
  CWindow(vec2d(engine->getScreenWidth()-480.,20.),vec2d(450.,450.),"Konzole")
{
  CBox* box = new CBox(vec2d(8.,8.), vec2d(getW()-16., 404. ));
  CText* text=new CText(vec2d(0.,0.), vec2d(getW()-40., 250. ), 12);
  CScrollable* scroll=new CScrollable(vec2d(2., 2.), vec2d(getW()-20.,400) );
  scroll->setScrolledItem(text);
  box->addChild(scroll);
  getContent()->addChild(box);

  engine->setConsoleOutput(text);
}

CConsole::~CConsole()
{}
