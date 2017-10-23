#version 410

in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragmentColour;

// Texture samplers
uniform sampler2D texture1;

void main() {
    FragmentColour = vec4(vertexColor,1.0f);
  	// Linearly interpolate between both textures (second texture is only slightly combined)
//    FragmentColour = texture(texture1, TexCoord);
}
