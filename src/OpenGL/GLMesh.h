#pragma once

#include <cmath>
#include <gl3w/gl3w.h>

enum Attribute
{
	POSITION = 0,
	UVCOORD = 1,
	NORMAL = 2,
	TRANSFORM = 3,
	JOINT_WEIGHTS = 7,
	JOINT_INDEXES = 9,
	NUM_JOINTS = 11,
};


class GLMesh
{
public:
	GLMesh(void* vertexData, int vertexDataByteSize, int numVertices, bool containsPositions, bool containsNormals, bool containsUVs, bool containsJointData, unsigned short* elementArrayData, int numElements, GLenum drawPrimitive);
	~GLMesh();
	void initializeVAO(GLuint vertexDataBufferObject, GLuint elementArrayBufferObject, int startIndex, int baseVertex);
	void render();
	
	void* vertexData; //will be deleted during initializeVAO
	int vertexDataByteSize;
	int numVertices;
	bool containsPositions;
	bool containsNormals;
	bool containsUVs;
	bool containsJointData;

	unsigned short* elementArrayData; //will be deleted during initializeVAO
	
	
	/**
	*	necessary information for the draw call
	*/
	GLenum drawPrimitive;
	GLuint vertexArrayObject;
	int firstIndex; //start index in the element array buffer
	int baseVertex; //start index in the vertex data buffer
	int count; //number of elements in this mesh

	//GLuint texture;
};