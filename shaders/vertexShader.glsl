#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable is at index 0
layout (location = 1) in vec3 aColor; // the color variable is at index 1

out vec3 myColor; // output a color to the fragmebnt shader

void main()
{
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  myColor = aColor;
}
