#pragma once
#include "ObjMaterial.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/ext/vector_float3.hpp>

class HitReport {
public:
	ObjMaterial material;	// The object material hit by the ray
	float t;				// The coordinate of the hit point along the ray
	glm::vec3 n;			// The surface normal at the hit pt

	HitReport();
	HitReport(ObjMaterial m, float t, glm::vec3 n);
	void setT(float newT);
};