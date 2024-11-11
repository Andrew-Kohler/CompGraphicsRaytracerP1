#include "Light.h"

Light::Light() {
	intensity = .5f;
	worldPos = glm::vec3(0, 0, 0);
}

Light::Light(float i) {
	intensity = i;
	worldPos = glm::vec3(0, 0, 0);
}

Light::Light(float i, glm::vec3 worldPos) {
	intensity = i;
	this->worldPos = worldPos;
}

glm::vec3 Light::illuminateRay(Ray ray, HitReport hr, std::vector<Object*> objList) {
	return glm::vec3(0, 0, 0);
}