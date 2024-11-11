#pragma once
#include "Object.h"
#include "Light.h"

#include<vector>

class Scene{
private:
	std::vector<Object*> objList;
	std::vector<Light*> lightList;
	glm::vec3 bgColor;
	int bounceCount;
public:
	Scene(std::vector<Object*> ol, std::vector<Light*> ll);
	const HitReport& objHit(Ray ray, float t0, float t1) const;
	const glm::vec3& lightColor(Ray ray, float t0, float t1, int bounceCount) const;
};