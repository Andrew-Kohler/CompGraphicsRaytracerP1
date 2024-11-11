#pragma once
#include "Triangle.h"
#include <vector>

class Tetrahedron : public Object {
private:
	glm::vec3 baseCoord1;
	glm::vec3 baseCoord2;
	glm::vec3 baseCoord3;
	glm::vec3 topCoord;

	Triangle tri1;
	Triangle tri2;
	Triangle tri3;
	Triangle tri4;

	std::vector<Triangle*> triList;

public:
	Tetrahedron();
	Tetrahedron(ObjMaterial m, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 pTop);
	HitReport objHit(Ray ray, float t0, float t1) override;
};
