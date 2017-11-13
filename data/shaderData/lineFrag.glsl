#version 410
///Copied code from https://vicrucann.github.io/tutorials/osg-shader-3dlines/ since it
/// was a much better implmentation of lines to thin triangles than what I did in
/// the previous assignment and this assignment isn't testing our ability to draw
/// thin rectangles so as long as I give proper credit (which I currently am) it
/// should be okay. Also I've left all of her comments untampered with even if I
/// made slight alterations to her code.

/* \brief Fragment GLSL shader that demonstrates how perform pass through fragment shader.
 * This file is a part of shader-3dcurve example (https://github.com/vicrucann/shader-3dcurve).
 * \author Victoria Rudakova
 * \date January 2017
 * \copyright MIT license
*/

in VertexData{
    vec2 mTexCoord;
    vec4 mColor;
} VertexIn;

out vec4 FragmentColour;

//// Texture samplers
//uniform sampler2D texture1;
//uniform int imageStyle=0;
//uniform int useTexture=1;

void main() {
    //sample image texture and store color data in colarData vector
//    vec4 imageData = texture(texture1, uvCoord);
//    gl_FragColor = VertexIn.mColor;
    FragmentColour = VertexIn.mColor;
//    FragmentColour =  vec4(0,1,0,1);
//    gl_FragColor = vec4(0,0,0,0);


//    FragmentColour=vec4(vertexColor,1.0f);
}
