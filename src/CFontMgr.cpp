#include <cmath>

#include "CFontMgr.h"
#include "Font.h"
#include "macros.h"
Font* CFontMgr::getFont(const wstring& name){
  FontList::iterator it=_fonts.find(name);
  if(it!=_fonts.end()){
    return it->second;
  }else{
    return (_fonts[name]=new Font(this, name));
  }
}

Font* CFontMgr::loadFont(const wstring& name, double size){
  size=ceil(size);
  FontList::iterator it=_fonts.find(name);
  Font* font;
  if(it!=_fonts.end()){
    font=it->second;
  }else{
    font=_fonts[name]=new Font(this, name);
  }

  if(font->_size==-1){
    font->_font=createFTGLFont(name);
    font->setSize(size);
  }else if(font->_size<size){
    font->setSize(size);
  }

  return font;
}

FTGLTextureFont* CFontMgr::createFTGLFont(const wstring& name){
  string path="C:\\Windows\\Fonts\\"+string(name.begin(),name.end());
  FTGLTextureFont* tf=new FTGLTextureFont(path.c_str());
  return tf;
}
