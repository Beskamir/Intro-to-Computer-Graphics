#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 customColor;
layout(location = 2) in vec2 textureCoord;

out vec3 vertexColor;
out vec2 TexCoord;

void main() {
  gl_Position = vec4(position, 1.0);
  vertexColor = customColor;

  TexCoord = vec2(textureCoord.x,1.0-textureCoord.y);
}
