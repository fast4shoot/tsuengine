#include "CLabel.h"
#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "GLFT_Font.hpp"

CLabel::CLabel(const vec2d& position, const vec2d& size):
CGuiPanel(position,size)
{
  init();
}

CLabel::CLabel(const vec2d& position, const vec2d& size, const std::string& text):
CGuiPanel(position,size)
{
  init();
  _text=text;
}

void CLabel::init(){
  _text="";
  _height=16;
  _font=new GLFT_Font("arial.TTF",_height);
}

void CLabel::draw(){
  glEnable(GL_TEXTURE_2D);
  glColor4f(fgColor);
  _font->drawText(0,0,_text);
  glDisable(GL_TEXTURE_2D);
}

void CLabel::updateFont(){
  _font->release();
  _font->open("arial.TTF",_height);
}

