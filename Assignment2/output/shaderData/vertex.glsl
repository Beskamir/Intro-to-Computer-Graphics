#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 customColor;
layout(location = 2) in vec2 textureCoord;

out vec3 vertexColor;
out vec2 uvCoord;

out vec2 TCposition;
out float TCdistance;

out mat4 transformationPass;

uniform mat4 transformation;
uniform int drawLines = 0;

void main() {
    gl_Position = transformation * vec4(position, 1.0);
    TCposition = position.xy;
    TCdistance = position.z;
    transformationPass = transformation;
//    if(drawLines==1){
//        TCposition = position.xy;
//        TCdistance = position.z;
//    }

    vertexColor=customColor; //Pass on vertex colors even though they aren't used
    uvCoord = vec2(textureCoord.x,1.0-textureCoord.y);
    gl_PointSize = 20.0f;
}
