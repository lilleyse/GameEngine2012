#version 420 core

#define POSITION		0
#define NORMAL			2
#define COLOR			3
#define FRAG_COLOR 		0

/*-------------------------
		Inputs
---------------------------*/
in Vertex{
	vec4 color;
} vertexIn;


/*-------------------------
		Outputs
---------------------------*/

layout (location = FRAG_COLOR, index = 0) out vec4 fragColor;

/*-------------------------
		Main
---------------------------*/

void main()
{
	fragColor = vertexIn.color;
}
