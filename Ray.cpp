#include "Ray.h"
#include <iostream>

Ray::Ray(glm::vec3 o, glm::vec3 dir) {
	origin = o;
	direction = dir;
}

glm::vec3 Ray::evaluateRay(float t) {
	//std::cout << "Origin: " << origin.x << " " << origin.y << " " << origin.z << "\n";
	//std::cout << "Direction:" << direction.x << " " << direction.y << " " << direction.z << "\n";
	//glm::vec3 hmm = direction - origin;
	//std::cout << "Dir - Or" << hmm.x << " " << hmm.y << " " << hmm.z << "\n";
	return (origin)+ t*direction; // glm::normalize(direction - origin)
}

glm::vec3 Ray::getOrigin() {
	return origin;
}

glm::vec3 Ray::getDir() {
	return direction;
}