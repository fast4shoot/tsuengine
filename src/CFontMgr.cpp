#include <cmath>
#include "utils/stringUtils.h"
#include "CFontMgr.h"
#include "Font.h"
#include "macros.h"
#include <stdexcept>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

Font* CFontMgr::getFont(const String& name, const double size){
  int sizeGroup=ceil(size/10.);
  String nameFinal=sformat("%s%d",name.c_str(),sizeGroup);

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

FTGLTextureFont* CFontMgr::loadFont(const String& name,double size){
  FTGLTextureFont* font;
  font=createFTGLFont(name);
  font->FaceSize((int)ceil(size));
  return font;
}

FTGLTextureFont* CFontMgr::createFTGLFont(const String& name){
  String path = "fonts/"+name;
  if(!fs::exists(path)){
    path="C:\\Windows\\Fonts\\"+name;
    if(!fs::exists(path)){
      throw std::runtime_error("Cannot load font file "+name);
    }
  }
  FTGLTextureFont* tf=new FTGLTextureFont(path.c_str());
  tf->UseDisplayList(true);
  return tf;
}
