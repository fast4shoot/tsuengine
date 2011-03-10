#ifndef CTEXT_H
#define CTEXT_H

#include "typedefs.h"
#include "CGuiPanel.h"
#include "CLabel.h"
#include "macros.h"
#include "utils/stringUtils.h"


class CText : public CGuiPanel
{
  public:
                    CText(const vec2d& pos, const vec2d& size, const double height);
    virtual         ~CText();
    virtual void    draw();
    void            setText(const String& text);
    String          getText() const;
    void            invalidate(){_valid=false;}
    void            sizeChanged();
  private:
    void            update();
    Font*           _font;
    String          _text;
    double          _height;
    CGuiPanel*      _textContainer;
    bool            _valid;

};



inline CText::~CText(){}

inline void CText::draw(){
  if(!_valid){
    update();
  }
}

inline void CText::setText(const String& text){
  _text=text;
  invalidate();
}

inline String CText::getText() const {
  return _text;
}

inline void CText::update(){
  _textContainer->deleteChildren();
  int labelCount=0;
  String line;
  std::vector<String> linebreaks= explode(_text,"\n");

  for(std::vector<String>::iterator it=linebreaks.begin();it!=linebreaks.end();++it){
    std::vector<String> words=explode(*it," ");
    line.clear();
    for(std::vector<String>::iterator it=words.begin();it!=words.end();++it){
      if(_font->width(line+(*it)+" ",_height)>getW()){
        _textContainer->addChild(new CLabel(vec2d(0., 1.1*_height*labelCount), vec2d(getW(), _height), line));
        labelCount++;
        line.clear();
      }
      line.append(*it);
      line.append(" ");
    }
    _textContainer->addChild(new CLabel(vec2d(0., 1.1*_height*labelCount), vec2d(getW(), _height), line));
    labelCount++;
  }
  setH(1.1*_height*labelCount);
  _valid=true;
}

inline void CText::sizeChanged(){
  invalidate();
}

#endif // CTEXT_H
