#version 410

layout(location = 0) in vec2 position;
layout (location = 1) in vec3 customColor;

out vec3 vertexColor;

void main() {
  gl_Position = vec4(position, 0.0, 1.0);
  vertexColor = customColor;
}
