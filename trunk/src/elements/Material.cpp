#include "Material.h"

#include <fstream>
#include "typedefs.h"
#include "libs/json_spirit/json_spirit.h"
#include "libs/il/ilut.h"
#include "utils/stringUtils.h"
#include "CBaseEngine.h"

namespace json=json_spirit;

Material::Material(String name){
  std::ifstream jsonFile(("materials/"+name+".json").c_str());

  json::mValue data;
  json::read(jsonFile, data);
  jsonFile.close();

  engine->log(sformat("my ass: %d",(int)data.type()));
  _name = data.get_obj().find("texture")->second.get_str();
  String fullPath = "materials/"+_name;
  char* cstr = new char [fullPath.size()+1];
  strcpy(cstr, fullPath.c_str());

  _glName=ilutGLLoadImage(cstr);

  ILenum Error;
  while ((Error = ilGetError()) != IL_NO_ERROR) {
    MSGBOX(sformat("%d: %s/n", Error, iluErrorString(Error)).c_str());
  }

}

Material::~Material(){
  glDeleteTextures(1,&_glName);
}
