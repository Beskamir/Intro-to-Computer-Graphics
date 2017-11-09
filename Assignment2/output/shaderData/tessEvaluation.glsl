#version 410

layout (isolines) in;		// are we dealing with lines?

// in vec3 gl_TessCoord;	// where on the abstract patch this eval is located
in vec2 TEposition[];		// incoming vertex data (again in an array)
in float TEdistance[];		//  and curve distance
in mat4 TEtransPass[];

out gl_PerVertex {		// stuck with old-style position data :'(
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
	};
out float fragDistance;		// but other attributes are different


uniform int maxDivs = 2;	// number of divisions

void main()
{

}
