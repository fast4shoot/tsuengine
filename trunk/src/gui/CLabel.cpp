#include "CLabel.h"
#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "macros.h"
#include "CBaseEngine.h"
#include <gl/gl.h>


CLabel::CLabel(const vec2d& position, const vec2d& size):
CGuiPanel(position,size)
{
  init();
}

CLabel::CLabel(const vec2d& position, const vec2d& size, const std::wstring& text):
CGuiPanel(position,size)
{
  init();
  _text=text;
}

void CLabel::init(){
  _text=L"";
  _font=engine->fonts->loadFont(L"ARIALUNI.TTF",getH());
}

void CLabel::draw(){
  _font->render(getH(),_text,fgColor);
}

void CLabel::updateFont(){
}

