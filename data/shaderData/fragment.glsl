#version 410

in vec3 vertexColor;
in vec2 uvCoord;

out vec4 FragmentColour;

// Texture samplers
//uniform sampler2D texture1;
//uniform int imageStyle=0;
//uniform int useTexture=1;

void main() {
    //sample image texture and store color data in colarData vector
//    FragmentColour=vec4(vertexColor,1.0f);
//    vec4 imageData = texture(texture1, uvCoord);
//    FragmentColour = imageData;
    FragmentColour=vec4(vertexColor,1.0f);


    //Check whether to use the texture or not.
    // If points or line then use vertex colors if image then use the image colors
//    if(useTexture==1){
//        FragmentColour = imageData;
//    }
//    else{
//    }
}
