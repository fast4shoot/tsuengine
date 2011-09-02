#version 120

varying vec3 normal;
varying vec4 pos;
uniform sampler2D tex;

void main(){
  gl_FragData[0] = texture2D(tex,gl_TexCoord[0].st);
  gl_FragData[1] = vec4( ( normal/max(abs(normal.x), max(abs(normal.y), abs(normal.z))) )  * .5 + vec3(0.5), 1.); //funky normal packing
  gl_FragData[2] = vec4(1., 1., 1., 1.);
  
}