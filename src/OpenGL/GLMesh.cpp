#include "GLMesh.h"

GLMesh::GLMesh(void* vertexData, int vertexDataByteSize, int numVertices, bool containsPositions, bool containsNormals, bool containsUVs, bool containsJointData, unsigned short* elementArrayData, int numElements, GLenum drawPrimitive)
{
	this->vertexData = vertexData;
	this->vertexDataByteSize = vertexDataByteSize;
	this->numVertices = numVertices;
	this->containsPositions = containsPositions;
	this->containsNormals = containsNormals;
	this->containsUVs = containsUVs;
	this->containsJointData = containsJointData;
	this->elementArrayData = elementArrayData;
	this->count = numElements;
	this->drawPrimitive = drawPrimitive;
}

GLMesh::~GLMesh()
{

}

void GLMesh::initializeVAO(GLuint vertexDataBufferObject, GLuint elementArrayBufferObject, int firstIndex, int baseVertex)
{
	this->firstIndex = firstIndex;
	this->baseVertex = baseVertex;

	//create and bind vao
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //bind array buffer again
    glBindBuffer(GL_ARRAY_BUFFER, vertexDataBufferObject);

	//enable vertex attributes
	if(containsPositions) glEnableVertexAttribArray(POSITION);
	if(containsNormals) glEnableVertexAttribArray(NORMAL);
	if(containsUVs) glEnableVertexAttribArray(UVCOORD);
	if(containsJointData)
	{
		glEnableVertexAttribArray(JOINT_WEIGHTS);
		glEnableVertexAttribArray(JOINT_WEIGHTS+1);
		glEnableVertexAttribArray(JOINT_INDEXES);
		glEnableVertexAttribArray(JOINT_INDEXES+1);
		glEnableVertexAttribArray(NUM_JOINTS);
	}

	/*glEnableVertexAttribArray(TRANSFORM + 0);
	glEnableVertexAttribArray(TRANSFORM + 1);
	glEnableVertexAttribArray(TRANSFORM + 2);
	glEnableVertexAttribArray(TRANSFORM + 3);*/

	int offset = 0;
	int vertexStructSize = this->vertexDataByteSize/this->numVertices;

	//set position attrib pointer
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, vertexStructSize, (void*)(offset));
	offset += sizeof(float)*3;

	//set normals attrib pointer
	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, vertexStructSize, (void*)(offset));
	offset += sizeof(float)*3;

	//set textures attrib pointer
	glVertexAttribPointer(UVCOORD, 2, GL_FLOAT, GL_FALSE, vertexStructSize, (void*)(offset));
	offset += sizeof(float)*2;

	//set jointWeights attrib pointer (part 1)
	glVertexAttribPointer(JOINT_WEIGHTS + 0, 4, GL_FLOAT, GL_FALSE, vertexStructSize, (void*)(offset));
	offset += sizeof(float)*4;

	//set jointWeights attrib pointer (part 2)
	glVertexAttribPointer(JOINT_WEIGHTS + 1, 4, GL_FLOAT, GL_FALSE, vertexStructSize, (void*)(offset));
	offset += sizeof(float)*4;

	//set jointIndexes attrib pointer (part 1)
	glVertexAttribIPointer(JOINT_INDEXES + 0, 4, GL_UNSIGNED_SHORT, vertexStructSize, (void*)(offset));
	offset += sizeof(unsigned short)*4;

	//set jointIndexes attrib pointer (part 2)
	glVertexAttribIPointer(JOINT_INDEXES + 1, 4, GL_UNSIGNED_SHORT, vertexStructSize, (void*)(offset));
	offset += sizeof(unsigned short)*4;

	//set numJoints attrib pointer
	glVertexAttribIPointer(NUM_JOINTS, 1, GL_UNSIGNED_SHORT, vertexStructSize, (void*)(offset));
	offset += sizeof(unsigned short);


    //bind element array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferObject);

    //unbind vao, vbo, and element array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	delete[] vertexData;
	delete[] elementArrayData;
}

void GLMesh::render()
{
	glBindVertexArray(vertexArrayObject);
    glDrawElementsBaseVertex(drawPrimitive, count, GL_UNSIGNED_SHORT, (void*)(firstIndex*sizeof(unsigned short)), baseVertex);
    glBindVertexArray(0);
}