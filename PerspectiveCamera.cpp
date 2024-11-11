// Different directions, same origin
#include "PerspectiveCamera.h"
PerspectiveCamera::PerspectiveCamera(glm::vec3 e, glm::vec3 d, glm::vec3 upDir, int width, int height, float imgWidth, float imgHeight, float focalLength) : Camera(e, d, upDir, width, height, imgWidth, imgHeight) {
	this->focalLength = focalLength;
}

Ray PerspectiveCamera::generateRay(float iPixel, float jPixel) { // Given the relative location of a point on the camera plane, generate a ray for it
	float uScalar = ((iPixel) / (2*r)) - .5f;
	float vScalar = ((jPixel) / (2*t)) - .5f;
	glm::vec3 origin = worldPos;
	glm::vec3 dir = glm::normalize(-focalLength * w + u * uScalar + v * vScalar);
	return Ray(origin, dir);
}