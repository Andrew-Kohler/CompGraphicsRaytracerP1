#pragma once
#include "Object.h"

class Sphere : public Object {
private:
	float radius;
	glm::vec3 center;
public:
	Sphere(ObjMaterial m, float r, glm::vec3 c);	// Constructor takes a radius and center along with material properties
	HitReport objHit(Ray ray, float t0, float t1) override;	// Implementation of hit checking specific to sphere
	glm::vec3 getCenter();
	void setCenter(glm::vec3 newCenter);
};