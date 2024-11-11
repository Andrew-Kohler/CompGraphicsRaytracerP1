#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 e, glm::vec3 d, glm::vec3 upDir, int width, int height, float imgWidth, float imgHeight) {
	worldPos = e;
	l = (-width) / 2;
	r = (width) / 2;
	b = -height / 2;
	t = height / 2;
	w = -d; // w = -d
	u = cross(upDir,w);	// u is perpendicular to both w and the up direction
	//std::cout << u.x << " " << u.y << " " << u.z << "\n";
	v = cross(u, w);	// v is perpendiular to both u and w
	//std::cout << l << " " << r << " " << b << " " << t << "\n";
}

Ray Camera::generateRay(float iPixel, float jPixel) {
	//float uScalar = (l + (r - l) * (iPixel + .5f)) / (2 * r);
	//float vScalar = (l + (r - l) * (iPixel + .5f)) / (2 * r);
	glm::vec3 origin = worldPos;// +uScalar * u + vScalar * v;
	glm::vec3 dir = -w;
	
	return Ray(origin, dir);
}

void Camera::setPos(glm::vec3 newPos) {
	worldPos = newPos;
}

glm::vec3 Camera::getPos() {
	return worldPos;
}

void Camera::setDir(glm::vec3 newDir, glm::vec3 newUpDir) {
	w = -newDir;
	u = cross(newUpDir, w);	// u is perpendicular to both w and the up direction
	////std::cout << u.x << " " << u.y << " " << u.z << "\n";
	v = cross(u, w);	// v is perpendiular to both u and w
}

glm::vec3 Camera::getDir() {
	return -w;
}