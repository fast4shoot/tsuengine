#include <cmath>
#include "utils/stringUtils.h"
#include "CFontMgr.h"
#include "Font.h"
#include "macros.h"

Font* CFontMgr::getFont(const wstring& name, const double size){
  int sizeGroup=ceil(size/10.);
  wstring nameFinal=swformat(L"%s%d",name.c_str(),sizeGroup);

  FontList::iterator it=_fonts.find(nameFinal);
  if(it!=_fonts.end()){
    if(size > (it->second->_size)){
      delete it->second->_font;
      it->second->_font=loadFont(name,size);
    }else{
      return it->second;
    }
  }else{
    return (_fonts[nameFinal]=new Font(loadFont(name,size), name, size));
  }
}

FTGLTextureFont* CFontMgr::loadFont(const wstring& name,double size){
  FTGLTextureFont* font;
  font=createFTGLFont(name);
  font->FaceSize((int)ceil(size));
  return font;
}

FTGLTextureFont* CFontMgr::createFTGLFont(const wstring& name){
  string path="C:\\Windows\\Fonts\\"+string(name.begin(),name.end());
  FTGLTextureFont* tf=new FTGLTextureFont(path.c_str());
  tf->UseDisplayList(true);
  return tf;
}
