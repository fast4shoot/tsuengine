#include "CLabel.h"
#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "glew/glew.h"
#include "typedefs.h"

CLabel::CLabel(const vec2d& position, const vec2d& size, const String& text, bool shaded, ALIGN align):
CGuiPanel(position,size),
_align(align),
m_shaded(shaded)
{
  _font=engine->fonts->getFont("ARIALUNI.TTF",getH());
  _text = text;
  allowKeyboardInput=false;
  invalidate();

}

void CLabel::draw(){
  if(m_invalid){
    recalculate();
  }

  setDrawColor(fgColor);
  _font->render(_text,getH(), vec2d(m_offset,0.));
  if(m_shaded){
    setDrawColor(bgColor);
    _font->render(_text,getH(), vec2d(m_offset+ceil(getH()/50.), ceil(getH()/50.)));
  }
}

void CLabel::setText(const String& text){
  _text=text;
  invalidate();
}

void CLabel::recalculate(){
  m_offset = 0.;
  if(_align == ALIGN_CENTER)
    m_offset = (getW() - _font->width(_text,getH()))/2;
  if(_align == ALIGN_RIGHT)
    m_offset = getW() - _font->width(_text,getH());
  m_invalid = false;
}
