#pragma once
#include "Ray.h"
#include "HitReport.h"
#include "Object.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>

class Light {
public:
	float intensity;
	glm::vec3 worldPos;
	
	Light();
	Light(float i);
	Light(float i, glm::vec3 worldPos);
	virtual glm::vec3 illuminateRay(Ray ray, HitReport hr, std::vector<Object*> objList);	// Virtual function for how illumination works for each light type

};