#pragma once
#include "Light.h"

class AmbientLight : public Light {
public:
	AmbientLight();
	AmbientLight(float i);
	glm::vec3 illuminateRay(Ray ray, HitReport hr, std::vector<Object*> objList) override;
};