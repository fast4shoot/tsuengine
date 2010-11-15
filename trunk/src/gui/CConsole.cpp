#include "CConsole.h"
#include "CText.h"
CConsole::CConsole():
  CWindow(vec2d(SCREENWIDTH-320.,20.),vec2d(300.,400.),L"Console")
{
  CText* text=new CText(vec2d(10.,30.), vec2d(280., 200. ), 14);
  //text->setText(L"Toto je multiline text na otestovani CTextu, obsahuje nejenom dlouhé řádky, diakritiku a \n line breaky, ale i spoustu dalších nepotřebných slov, která, upřímně, nikoho nezajímají.");
  text->setText(L"Toto je multiline text na otestovani CTextu. Obsahuje nejenom dlouhé řádky, diakritiku a line breaky, ale i spoustu dalsich veci ktery.");
  addChild(text);
}

CConsole::~CConsole()
{}
