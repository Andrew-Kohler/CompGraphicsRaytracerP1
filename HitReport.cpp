#include "HitReport.h"

HitReport::HitReport() {
	material = ObjMaterial();
	t = std::numeric_limits<float>::infinity();
	n = glm::vec3(0, 0, 0);
}

HitReport::HitReport(ObjMaterial m, float t, glm::vec3 n) {
	material = m;
	this->t = t;
	this->n = n;
}

void HitReport::setT(float newT) {
	t = newT;
}