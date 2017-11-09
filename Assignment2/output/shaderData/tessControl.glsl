#version 410

in vec2 TCposition[];		// incoming vertex data. Note the array!
in float TCdistance[];
in mat4 transformationPass[];

layout (vertices = 2) out;	// two outgoing verticies
out vec2 TEposition[];		// outgoing vertex data
out float TEdistance[];		//  attributes are also in array form
out mat4 TEtransPass[];

uniform int maxDivs = 2;	// how many subdivisions?

void main() {

	gl_TessLevelOuter[0] = 1;		// how to tesselate the patch
	gl_TessLevelOuter[1] = 1 << maxDivs;	

						// pass these through
	TEposition[gl_InvocationID] = TCposition[gl_InvocationID];
	TEdistance[gl_InvocationID] = TCdistance[gl_InvocationID];
    TEtransPass[gl_InvocationID]=transformationPass[gl_InvocationID];
}
