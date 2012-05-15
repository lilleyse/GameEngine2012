#version 420 core

#define POSITION		0
#define NORMAL			2
#define COLOR			3
#define FRAG_COLOR 		0

/*-------------------------
		Uniforms
---------------------------*/

uniform mat4 modelToClipMatrix;

/*-------------------------
		Inputs
---------------------------*/
layout(location = POSITION) in vec4 position;
layout(location = COLOR) in vec4 color;

/*-------------------------
		Outputs
---------------------------*/

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

out Vertex{
	vec4 color;
} vertexOut;


/*-------------------------
		Main
---------------------------*/

void main()
{
	gl_Position = modelToClipMatrix * position;
	vertexOut.color = color;
}
