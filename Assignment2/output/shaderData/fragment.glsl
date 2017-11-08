#version 410

in vec3 vertexColor;
//in vec4 testColors;
in vec2 uvCoord;

out vec4 FragmentColour;

// Texture samplers
uniform sampler2D texture1;
uniform int imageStyle;
uniform int controlPoints;

void main() {
    //sample image texture and store color data in colarData vector
    vec4 imageData = texture(texture1, uvCoord);

    // Convert to grayscale using NTSC conversion weights
//    if(imageStyle==1){
//        // Convert to grayscale using NTSC conversion weights
//        vec3 greyScaleWieghting={0.299,0.587,0.114};
//        float luminance = dot(imageData.rgb,vec3(0.299,0.587,0.114));
//        imageData = vec4(luminance,luminance,luminance,imageData.a);
//    }
//    //Quantize the image
//    if(imageStyle==2){
//        vec3 colorData = imageData.rgb;
//        colorData = vec3(floor(colorData*3)/3);
//        imageData=vec4(colorData,1.0);
//    }

    //Check if drawing points and either use vertex colors or use the image colors
    if(controlPoints==1){
        FragmentColour=vec4(vertexColor,1.0f);
    }
    else{
       FragmentColour = imageData;
    }
}
