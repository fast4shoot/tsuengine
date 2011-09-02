#version 120

varying vec3 lightPos;
varying vec3 viewRay;

uniform vec3 lightPositionIn;


void main() {
  gl_Position = gl_Vertex;
  gl_TexCoord[0]  = gl_MultiTexCoord0;
  vec4 pos = gl_ModelViewMatrix * vec4(lightPositionIn, 1.);
  lightPos = -pos.xyz;
  gl_FrontColor = gl_Color;
  
  //data for fragment shader position reconstruction
  vec3 position = (gl_ProjectionMatrixInverse * gl_Vertex).xyz;
  viewRay = vec3(position.xy / position.z, 1.0f);
  
  //ProjectionA = gl_DepthRange.far / gl_DepthRange.diff;
  //ProjectionB = (-gl_DepthRange.far * gl_DepthRange.near) / gl_DepthRange.diff;
  
}