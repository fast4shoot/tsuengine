#version 120

uniform sampler2D diffuseMap;
uniform sampler2D lightMap;

void main() {
  vec4 light = texture2D(lightMap,gl_TexCoord[0].st);
  vec4 color = texture2D(diffuseMap,gl_TexCoord[0].st);
  gl_FragColor = vec4((color.rgb * light.rgb) * (light.a * 2. + 1.), color.a);
}