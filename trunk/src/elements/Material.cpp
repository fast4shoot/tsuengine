#include "Material.h"

#include <fstream>
#include <streambuf>
#include <string>
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

  _name = data.get_obj().find("texture")->second.get_str();



  ILuint ImageName; // The image name to return.
  ilGenImages(1, &ImageName);
  ilBindImage(ImageName);

  std::ifstream dataFile(("materials/"+_name).c_str(),std::ifstream::binary);
  std::string imgData;

  dataFile.seekg(0, std::ios::end);
  imgData.reserve(dataFile.tellg());
  dataFile.seekg(0, std::ios::beg);

  imgData.assign((std::istreambuf_iterator<char>(dataFile)), std::istreambuf_iterator<char>());
  dataFile.close();
  ilLoadL(IL_TYPE_UNKNOWN,imgData.c_str(),imgData.size());
  _glName=ilutGLBindTexImage();
  ilDeleteImages(1,&ImageName);

  //for some strange reason, these do not work
  //TODO: make ilutGLLoadImage work
  //ilLoadImage(((const ILstring)"materials/wall1.png"));
  //_glName=ilutGLBindTexImage();
  //_glName=ilutGLLoadImage("D:\\fast4shoot\\programming\\TSUEngine\\release\\wall1.png");
  ILenum Error;
  while ((Error = ilGetError()) != IL_NO_ERROR) {
    engine->log(sformat("DevIL ERROR: 0x%x: %s/n", Error, iluErrorString(Error)).c_str());
  }

}

Material::~Material(){
  glDeleteTextures(1,&_glName);
}
