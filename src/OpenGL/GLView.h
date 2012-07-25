#pragma once

#include <glm/glm.hpp>

const float DEG_TO_RAD = 3.14159f * 2.0f / 360.0f;
const float RAD_TO_DEG = 360.0f / (3.14159f * 2.0f);

class GLView
{
public:
	GLView();
	~GLView();

	void setCameraToClipMatrix(float near, float far, float fieldOfViewDegrees);

	glm::mat4& getCameraToClipMatrix();

private:
	glm::mat4 cameraToClipMatrix;
};