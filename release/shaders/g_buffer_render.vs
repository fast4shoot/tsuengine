#version 120

varying vec4 viewVec;
varying vec2 ssPos;

void main() {
  gl_TexCoord[0]  = gl_MultiTexCoord0;
  viewVec = normalize(gl_Vertex * gl_ProjectionMatrixInverse);
  gl_Position = gl_Vertex;
  ssPos = gl_Vertex.xy;
}