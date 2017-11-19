#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 customColor;
layout(location = 2) in vec2 textureCoord;

out vec3 vertexColor;
out vec2 uvCoord;

//uniform mat4 transformation;

uniform mat4 modelTransformation;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * modelTransformation * vec4(position, 1.0);
//    vertexColor=customColor; //Pass on vertex colors even though they aren't used
    vertexColor=vec3(0.5f,0.2f,0.1f); //Pass on vertex colors even though they aren't used
    uvCoord = vec2(textureCoord.x,1.0-textureCoord.y);
}
