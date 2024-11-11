#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	glm::vec3 worldPos;		// Worldspace coordinate of the point light

	PointLight();
	PointLight(glm::vec3 pos, float i);
	glm::vec3 illuminateRay(Ray ray, HitReport hr, std::vector<Object*> objList) override;
	const HitReport& objHit(Ray ray, float t0, float t1, std::vector<Object*> objList) const;
};