#version 410

layout(location = 0) in vec2 position;
//layout(location = 1) in vec3 FragmentColor;

out vec3 vertexColor;

void main() {
  gl_Position = vec4(position, 0.0, 1.0);
//  vertexColor = vec3(0.0f,0.7f,1.0f);
  vertexColor = vec3(0.9f,0.4f,0.1f);
}
