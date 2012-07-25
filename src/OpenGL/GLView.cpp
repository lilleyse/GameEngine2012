#include "GLView.h"

GLView::GLView()
{
	setCameraToClipMatrix(.10f, 1000.0f, 45.0f);
}

GLView::~GLView()
{

}

void GLView::setCameraToClipMatrix(float near, float far, float fieldOfViewDegrees)
{

    float frustumScale = 1.0f / tan(fieldOfViewDegrees * DEG_TO_RAD / 2.0f);

	cameraToClipMatrix = glm::mat4(0.0f);
    cameraToClipMatrix[0].x = frustumScale;
    cameraToClipMatrix[1].y = frustumScale;
    cameraToClipMatrix[2].z = (far + near) / (near - far);
    cameraToClipMatrix[2].w = -1.0f;
    cameraToClipMatrix[3].z = (2 * far * near) / (near - far);
}

glm::mat4& GLView::getCameraToClipMatrix()
{
	return this->cameraToClipMatrix;
}