#pragma once
#include "Object.h"

class Triangle : public Object {
private:
	glm::vec3 coord1;
	glm::vec3 coord2;
	glm::vec3 coord3;
	bool oneSided;

public:
	Triangle();
	Triangle(ObjMaterial m, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, bool oneSided);
	HitReport objHit(Ray ray, float t0, float t1) override;
};