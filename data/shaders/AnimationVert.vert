#version 420 core

#define POSITION		0
#define TEXCOORD		1
#define NORMAL			2
#define COLOR			3
#define JOINT_WEIGHTS	3
#define JOINT_INDEXES	5
#define NUM_JOINTS		7


#define MAX_JOINTS 50

/*-------------------------
		Uniforms
---------------------------*/

layout(std140) uniform;

layout(binding = 0) uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform mat4 worldToCameraMatrix;
uniform mat3 normalWorldToCameraMatrix;
uniform mat4 jointMatrices[MAX_JOINTS];


/*-------------------------
		Attributes
---------------------------*/
layout(location = POSITION) in vec3 position;
layout(location = NORMAL) in vec3 normal;
layout(location = TEXCOORD) in vec2 texcoord;
layout(location = JOINT_WEIGHTS) in vec4[2] jointWeights;
layout(location = JOINT_INDEXES) in ivec4[2] jointIndexes; 
layout(location = NUM_JOINTS) in int numJoints;



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
	vec4 modelSpacePos = vec4(position, 1.0);
	mat4 skinningMatrix = mat4(0);
	for(int i = 0; i < numJoints; i++)
	{
		int jointIndex = jointIndexes[int(i>3)][i%4];
		float jointWeight = jointWeights[int(i>3)][i%4];
		skinningMatrix += jointWeight * jointMatrices[jointIndex];
	}

	//tempPosition.w = 1;
	
	vec4 tempCamPosition = worldToCameraMatrix * skinningMatrix * modelSpacePos;
	gl_Position = cameraToClipMatrix * tempCamPosition;
	
	vertexOut.vertexNormal = normalize(normalWorldToCameraMatrix * mat3(skinningMatrix) * normal);
	vertexOut.cameraSpacePosition = vec3(tempCamPosition);
	vertexOut.texcoord = texcoord;
}
