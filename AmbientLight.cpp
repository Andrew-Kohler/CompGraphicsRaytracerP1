#include "AmbientLight.h"

AmbientLight::AmbientLight() : Light() {}

AmbientLight::AmbientLight(float i) : Light(i) {}

glm::vec3 AmbientLight::illuminateRay(Ray ray, HitReport hr, std::vector<Object*> objList) {
	return intensity * hr.material.ambientCoeff * hr.material.ambientColor;
}

