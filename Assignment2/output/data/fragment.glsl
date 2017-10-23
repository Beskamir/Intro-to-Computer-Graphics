#version 410

in vec3 vertexColor;
out vec4 FragmentColour;

void main() {
  FragmentColour = vec4(vertexColor,1.0f);
}
