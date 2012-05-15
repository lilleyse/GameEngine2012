#version 420 core

#define POSITION		0
#define TEXCOORD		1
#define NORMAL			2


/*-------------------------
		Uniforms
---------------------------*/

layout(std140) uniform;

layout(binding = 0) uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;


/*-------------------------
		Inputs
---------------------------*/

layout(location = POSITION) in vec3 position;
layout(location = NORMAL) in vec3 normal;
layout(location = TEXCOORD) in vec2 texcoord;

/*-------------------------
		Outputs
---------------------------*/

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

out Vertex
{
	vec3 vertexNormal;
	vec3 cameraSpacePosition;
	vec2 texcoord;
	
} vertexOut;


/*-------------------------
		Main
---------------------------*/

void main()
{
	vec4 tempCamPosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * tempCamPosition;

	vertexOut.vertexNormal = normalize(normalModelToCameraMatrix * normal);
	vertexOut.cameraSpacePosition = vec3(tempCamPosition);
	vertexOut.texcoord = texcoord;
}

