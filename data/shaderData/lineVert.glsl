#version 410
///Copied code from https://vicrucann.github.io/tutorials/osg-shader-3dlines/ since it
/// was a much better implmentation of lines to thin triangles than what I did in
/// the previous assignment and this assignment isn't testing our ability to draw
/// thin rectangles so as long as I give proper credit (which I currently am) it
/// should be okay. Also I've left all of her comments untampered with even if I
/// made slight alterations to her code.

/* \brief Vertex GLSL shader that demonstrates how to draw basic thick and smooth lines in 3D.
 * This file is a part of shader-3dcurve example (https://github.com/vicrucann/shader-3dcurve).
 *
 * \author Victoria Rudakova
 * \date January 2017
 * \copyright MIT license
*/

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 customColor;
layout(location = 2) in vec2 textureCoord;

uniform mat4 transformation;

out VertexData{
    vec4 mColor;
} VertexOut;

void main(void){
//    VertexOut.mColor = vec4(0,0,0,0);
    VertexOut.mColor = vec4(customColor,1.0f);
    gl_Position = transformation * vec4(position, 1.0f);
}