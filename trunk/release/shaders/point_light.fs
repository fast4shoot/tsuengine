#version 120

varying vec3 lightPos;
varying vec3 viewRay;
uniform sampler2D depthMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform float ProjectionA;
uniform float ProjectionB;
uniform float lightSize;

void main() {

  // Sample the depth and convert to linear view space Z (assume it gets sampled as
  // a floating point value of the range [0,1])
  float depth = texture2D(depthMap, gl_TexCoord[0].st).x; 
  depth = ProjectionB / (depth - ProjectionA);
  vec3 fragPos = viewRay * depth;
  
  // sample and unpack normal from texture
  vec3 normal = texture2D(normalMap, gl_TexCoord[0].st).xyz;
  normal = normalize(normal * 2. + vec3(-1.));
   
  vec3 lightDir = normalize(fragPos - lightPos); 
  
  // sample and unpack specular color and intensity 
  vec4 specComponent = texture2D(specularMap, gl_TexCoord[0].st);
  vec3 reflectedVector = normalize(reflect(-lightDir, normal));
  float specIntensity = max(0.0, dot(normalize(viewRay), reflectedVector));
   
  // calculate distance based attenuation modifier 
  float distanceMod = distance(fragPos, lightPos) / lightSize;
  distanceMod = clamp(1. - distanceMod, 0., 1.);
  
  float lightIntensity = pow(distanceMod, 2.0) * max(0.0, dot(normal, lightDir));
   
  gl_FragColor = vec4(lightIntensity * gl_Color.xyz, 0.);
  
  if(lightIntensity > 0.0){    
    specIntensity = pow(specIntensity, specComponent.a * 500.0);
    gl_FragColor.rgb += clamp(gl_Color.xyz * 2.0, 0.0, 2.0) * specComponent.xyz * specIntensity * pow(distanceMod, 0.9);
  }
  
}