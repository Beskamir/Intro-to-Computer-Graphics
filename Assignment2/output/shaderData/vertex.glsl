#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 customColor;
layout(location = 2) in vec2 textureCoord;

out vec3 vertexColor;
out vec2 uvCoord;

uniform mat4 transformation;

void main() {
  gl_Position = /*transformation * */vec4(position, 1.0);
  vertexColor = customColor;

  uvCoord = vec2(textureCoord.x,1.0-textureCoord.y);
}
