#include "Tetrahedron.h"
#include <iostream>

Tetrahedron::Tetrahedron() : Object() {
	baseCoord1 = glm::vec3(0, 0, 1);
	baseCoord2 = glm::vec3(1, 0, 0);
	baseCoord3 = glm::vec3(0, 0, -1);
	topCoord = glm::vec3(.5, 1, 0);

	ObjMaterial basicMaterial = ObjMaterial(0.3f, 0.3f, 0.4f, glm::vec3(255, 255, 0), glm::vec3(255, 255, 255), glm::vec3(255, 255, 0), false, glm::vec3(.2,.2,.2), 500);
	ObjMaterial basicMaterial2 = ObjMaterial(0.3f, 0.3f, 0.4f, glm::vec3(0, 255, 0), glm::vec3(255, 255, 255), glm::vec3(0, 255, 0), false, glm::vec3(.2, .2, .2), 500);
	ObjMaterial basicMaterial3 = ObjMaterial(0.3f, 0.3f, 0.4f, glm::vec3(0, 0, 255), glm::vec3(255, 255, 255), glm::vec3(0, 0, 255), false, glm::vec3(.2, .2, .2), 500);
	tri1 = Triangle(material, baseCoord1, baseCoord2, baseCoord3, true); 
	tri2 = Triangle(basicMaterial, topCoord, baseCoord1, baseCoord2, true);
	tri3 = Triangle(basicMaterial2, baseCoord1, topCoord, baseCoord3, true); //(good?)
	tri4 = Triangle(basicMaterial3, baseCoord2, baseCoord3, topCoord, true); //(good?)

	triList.push_back(&tri1);
	triList.push_back(&tri2);
	triList.push_back(&tri3);
	triList.push_back(&tri4);
}
Tetrahedron::Tetrahedron(ObjMaterial m, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 pTop) : Object(m){
	baseCoord1 = p1;
	baseCoord2 = p2;
	baseCoord3 = p3;
	topCoord = pTop;

	tri1 = Triangle(m, baseCoord1, baseCoord2, baseCoord3, true);
	tri2 = Triangle(m, topCoord, baseCoord1, baseCoord2, true);
	tri3 = Triangle(m, baseCoord1, topCoord, baseCoord3, true); //(good?)
	tri4 = Triangle(m, baseCoord2, baseCoord3, topCoord, true); //(good?)

	triList.push_back(&tri1);
	triList.push_back(&tri2);
	triList.push_back(&tri3);
	triList.push_back(&tri4);
}

HitReport Tetrahedron::objHit(Ray ray, float t0, float t1){
	HitReport hr;
	for (Triangle* tri : triList) {
		
		HitReport check = tri->objHit(ray, t0, t1);
		if (check.t < t1 && check.t > t0) {	// If we get a hit
			t1 = check.t; // Shrink our search window so we only update if we find something closer
			hr = check;
		}
	}

	return hr;

}
