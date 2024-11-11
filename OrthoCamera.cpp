#include "OrthoCamera.h"
#include <iostream>
OrthoCamera::OrthoCamera(glm::vec3 e, glm::vec3 d, glm::vec3 upDir, int width, int height, float imgWidth, float imgHeight) : Camera (e, d, upDir, width, height, imgWidth, imgHeight) {

}

Ray OrthoCamera::generateRay(float iPixel, float jPixel) { // Given the relative location of a point on the camera plane, generate a ray for it
	float uScalar = ((iPixel) / (2 * r)) - .5f;
	float vScalar = ((jPixel) / (2 * t)) - .5f;
	glm::vec3 origin = worldPos + uScalar * u + vScalar * v;
	glm::vec3 dir = -w;
	return Ray(origin, dir);
}