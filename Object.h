#pragma once
#include "Ray.h"
#include "Camera.h"
#include "HitReport.h"
#include "ObjMaterial.h"

class Object {
protected:
	//glm::vec3 color; // We're just gonna start out with a single color
	ObjMaterial material; // Moving up in the world to materials

public:
	Object();
	Object(ObjMaterial m);
	virtual HitReport objHit(Ray ray, float t0, float t1);
	//glm::vec3 getBaseColor();
};