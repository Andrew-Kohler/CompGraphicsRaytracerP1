#include "Object.h"

Object::Object() {
	material = ObjMaterial();
}

Object::Object(ObjMaterial m) {
	material = m;
}

HitReport Object::objHit(Ray ray, float t0, float t1)
{
	return HitReport();
}

//glm::vec3 Object::getBaseColor() {
//	return material.baseColor;
//}