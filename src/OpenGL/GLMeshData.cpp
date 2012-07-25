#include "GLMeshData.h"

GLMeshData::GLMeshData(std::vector<GLMesh>& meshes, GLenum bufferUsage)
{
	//TODO: setting up the drawCall buffer needs to be done at another time and elsewhere since as of now there is no data on the types of objects actually in the scene or how many instances they have
	int vertexDataBufferSize = 0;
	int elementArrayBufferSize = 0;
	unsigned int numMeshes = meshes.size();
	
	for(unsigned int i = 0; i < numMeshes; i++)
	{
		vertexDataBufferSize += meshes[i].vertexDataByteSize;
		elementArrayBufferSize += meshes[i].count;
	}

	vertexDataBufferSize = Utils::nextPowerOf2(vertexDataBufferSize);
	elementArrayBufferSize *= sizeof(unsigned short);
	elementArrayBufferSize = Utils::nextPowerOf2(elementArrayBufferSize);

	//create vertex buffer
    glGenBuffers(1, &vertexDataBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexDataBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexDataBufferSize, NULL, bufferUsage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	//create element array buffer
	glGenBuffers(1, &elementArrayBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferSize, NULL, bufferUsage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//loop over the meshes again now that the buffers are created and fill the buffers.
	int vertexCount = 0;
	int vertexDataBufferOffset = 0;
	int elementCount = 0;
	int elementArrayBufferOffset = 0;

	for(unsigned int i = 0; i < numMeshes; i++)
	{
		
		int meshVertexDataByteSize = meshes[i].vertexDataByteSize;
		int meshElementArrayByteSize = meshes[i].count*sizeof(unsigned short);
		
		glBufferSubData(GL_ARRAY_BUFFER, vertexDataBufferOffset, meshVertexDataByteSize, meshes[i].vertexData);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferOffset, meshElementArrayByteSize, meshes[i].elementArrayData);
		meshes[i].initializeVAO(vertexDataBufferObject, elementArrayBufferSize, elementCount, vertexCount);  
		
		vertexCount += meshes[i].numVertices;
		vertexDataBufferOffset += meshVertexDataByteSize;
		elementCount += meshes[i].count;
		elementArrayBufferOffset += meshElementArrayByteSize;
	}




}

GLMeshData::~GLMeshData()
{
	glDeleteBuffers(1, &vertexDataBufferObject);
	glDeleteBuffers(1, &elementArrayBufferObject);
}