#include "CText.h"
#include "CBaseEngine.h"

CText::CText(const vec2d& pos, const vec2d& size, const double height, CLabel::ALIGN align):
  CGuiPanel(pos,size),
  _textContainer(new CGuiPanel(vec2d(),size)),
  _height(height),
  _font(engine->fonts->getFont("ARIALUNI.TTF", height)),
  _text(),
  m_align(align)
{
  invalidate();
  addChild(_textContainer);
}

void CText::update(){
  _textContainer->deleteChildren();
  int labelCount=0;
  String line;
  std::vector<String> linebreaks= explode(_text,"\n");


  for(std::vector<String>::iterator it=linebreaks.begin();it!=linebreaks.end();++it){
    std::vector<String> words=explode(*it," ");
    line.clear();
    for(std::vector<String>::iterator it=words.begin();it!=words.end();++it){
      if(_font->width(line+(*it)+" ",_height)>getW()){
        _textContainer->addChild(new CLabel(vec2d(0., 1.1*_height*labelCount), vec2d(getW(), _height), line, false, m_align));
        labelCount++;
        line.clear();
      }
      line.append(*it);
      line.append(" ");
    }
    _textContainer->addChild(new CLabel(vec2d(0., 1.1*_height*labelCount), vec2d(getW(), _height), line, false, m_align));
    labelCount++;
  }
  setH(1.1*_height*labelCount);
  _valid=true;
}
