#version 120

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform float ProjectionA, ProjectionB;
varying vec4 viewVec;
varying vec2 ssPos;

void main(){
  //this doesn't work
  /*
  vec3 pos;
  pos.z = ProjectionB / ( texture2D(depthMap,gl_TexCoord[0].st).x - ProjectionA);
  pos.xy = viewVec.xy / viewVec.z * pos.z;
  /*gl_FragColor = texture2D(diffuseMap,gl_TexCoord[0].st);
  gl_FragColor.xyz *= (1. - clamp((length(pos)-1.)/1., 0., 1.));*/
  gl_FragColor = texture2D(diffuseMap,gl_TexCoord[0].st);
  
  
}