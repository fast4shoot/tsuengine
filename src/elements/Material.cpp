#include "Material.h"

#include <fstream>
#include <streambuf>
#include <string>
#include "typedefs.h"
#include "json/json.h"
#include "il/ilut.h"
#include "utils/stringUtils.h"
#include "CBaseEngine.h"


Material::Material(const String& name):
  m_persistent(false)
{
  std::ifstream jsonFile(("materials/"+name+".json").c_str());

  json::mValue data;
  json::read(jsonFile, data);
  jsonFile.close();

  modifiers::PropertyMgr properties(data);

  _name = value_cast<String>(properties.getValuePointer("texture"));

  m_transparent = value_cast<bool>(properties.getValuePointer("transparent", false));

  m_offset = properties.getValuePointer("offset", vec2d(0., 0.));
  m_rotationCenter = properties.getValuePointer("rotationCenter", vec2d(.5, .5));
  m_rotation = properties.getValuePointer("rotation", 0.);
  m_scale = properties.getValuePointer("scale", vec2d(1., 1.));

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

void Material::bind(){
  glBindTexture(GL_TEXTURE_2D,_glName);
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  vec2d temp = value_cast<vec2d>(m_scale);
  glScalef(temp.x, temp.y, 1.);
  temp = modifiers::value_cast< vec2d >(m_offset);
  glTranslatef(temp.x, temp.y, 0.);
  double rotation = value_cast<double>(m_rotation);
  glRotatef(rotation, 0., 0., 1.);


  glMatrixMode(GL_MODELVIEW);

}

void Material::unbind(){
  glBindTexture(GL_TEXTURE_2D,0);
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}
