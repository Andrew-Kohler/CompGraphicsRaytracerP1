#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera {
private:
	float focalLength;
public:
	PerspectiveCamera(glm::vec3 e, glm::vec3 d, glm::vec3 upDir, int width, int height, float imgWidth, float imgHeight, float focalLength);
	Ray generateRay(float iPixel, float jPixel) override;
};