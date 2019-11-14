#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

void main() {
    /*float sumX = -0.5 + 0.5 + 0.0;
    float sumY = -0.5 - 0.5 + 0.5;
    float x = sumX/3;
    float y = sumY/3;
    vec2 origin = vec2(x,y);
  //float dist = sqrt(pow(vFragColor.x-origin.x, 2)+pow(vFragColor.y-origin.y, 2));
  float dist = distance(vFragColor.xy, origin);
  float a = 1 * exp(-5.0 * pow(dist, 2));*/

  //fFragColor = vFragColor*length(fract(5.0*vFragColor.xy));
  //fFragColor = vFragColor*length(abs(fract(5.0*vFragColor.xy)*2.0-1.0));
  //fFragColor = vFragColor*mod(floor(10.0*vFragColor.x)+floor(10.0*vFragColor.y), 2.0);
  fFragColor = vFragColor*smoothstep(0.4,0.5,max(abs(fract(8.0*vFragColor.x-0.5*mod(floor(8.0*vFragColor.y), 2.0))-0.5), abs(fract(8.0*vFragColor.y)-0.5)));
};
