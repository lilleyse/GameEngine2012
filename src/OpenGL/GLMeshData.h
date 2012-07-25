#pragma once

#include <vector>

#include "GLMesh.h"
#include "../Utils.h"

class GLMeshData
{
public:
	GLMeshData(std::vector<GLMesh>& meshes, GLenum bufferUsage);
	~GLMeshData();

private:

	GLuint vertexDataBufferObject;
    GLuint elementArrayBufferObject;

};