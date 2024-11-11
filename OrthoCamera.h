#pragma once
#include "Camera.h"
#include "Ray.h"

// Different origins, same direction
class OrthoCamera : public Camera {
public:
	OrthoCamera(glm::vec3 e, glm::vec3 d, glm::vec3 upDir, int width, int height, float imgWidth, float imgHeight);
	Ray generateRay(float iPixel, float jPixel);
};