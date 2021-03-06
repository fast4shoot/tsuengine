#version 120

varying vec3 normal;
varying vec4 pos;

void main() {
  gl_TexCoord[0]  = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  normal = gl_NormalMatrix * gl_Normal;
  pos = gl_ModelViewMatrix * gl_Vertex ;
  gl_Position = ftransform();
}