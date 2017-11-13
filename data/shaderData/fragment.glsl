#version 410

in vec3 vertexColor;
in vec2 uvCoord;

out vec4 FragmentColour;

// Texture samplers
uniform sampler2D texture1;
uniform int imageStyle=0;
uniform int useTexture=1;

void main() {
    //sample image texture and store color data in colarData vector
//    FragmentColour=vec4(vertexColor,1.0f);
    vec4 imageData = texture(texture1, uvCoord);
    FragmentColour = imageData;
    // Convert to grayscale using NTSC conversion weights
    if(imageStyle==1){
        // Convert to grayscale using NTSC conversion weights
        vec3 greyScaleWieghting=vec3(0.299,0.587,0.114);
        float luminance = dot(imageData.rgb,vec3(0.299,0.587,0.114));
        imageData = vec4(luminance,luminance,luminance,imageData.a);
    }
    //Quantize the image
    if(imageStyle==2){
        vec3 colorData = imageData.rgb;
        colorData = vec3(floor(colorData*3)/3);
        imageData=vec4(colorData,1.0);
    }
    else{

    }

    //Check whether to use the texture or not.
    // If points or line then use vertex colors if image then use the image colors
    if(useTexture==1){
        FragmentColour = imageData;
    }
    else{
        FragmentColour=vec4(vertexColor,1.0f);
        if(useTexture==0){
            // Circular points thanks to: https://stackoverflow.com/questions/27098315/render-large-circular-points-in-modern-opengl
            vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
            if (dot(circCoord, circCoord) > 1.0) {
                discard;
            }
        }
    }
}
