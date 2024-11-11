#include "Sphere.h"
#include<iostream>

Sphere::Sphere(ObjMaterial m, float r, glm::vec3 c) : Object(m){
	radius = r;
	center = c;
}

HitReport Sphere::objHit(Ray ray, float t0, float t1){
	// d = direction of ray
	// e = origin of ray
	// c = center of sphere

	float t = t1;
	ObjMaterial m = ObjMaterial();
	glm::vec3 n(0, 0, 0);

	glm::vec3 originMinusCenter = ray.getOrigin() - center;

	float frontTerm = dot((-1.0f * ray.getDir()), originMinusCenter);
	float discriminant = pow((dot(ray.getDir(), originMinusCenter)), 2) - (dot(originMinusCenter, originMinusCenter)-pow(radius,2));
	//float frontTerm = dot((-1.0f * ray.getDir()), ray.getOrigin());
	//float discriminant = pow(dot(ray.getDir(), ray.getOrigin()), 2) - (dot(ray.getOrigin(), ray.getOrigin())) + radius;
	//if (discriminant < 0) {
	//	//std::cout << "no luck\n";
	//}
	if (discriminant == 0) {	// If we get a valid discriminant, we work out which hit was the first one, and return that in the report
		m = material;
		t = frontTerm / dot(ray.getDir(), ray.getDir());
	}
	else if(discriminant > 0){

		m = material;
		float solnOne = (frontTerm + sqrt(discriminant))/ dot(ray.getDir(), ray.getDir());
		float solnTwo = (frontTerm - sqrt(discriminant)) / dot(ray.getDir(), ray.getDir());
		//std::cout << solnOne << "\n";
		//std::cout << solnTwo << "\n\n";

		if (solnOne < solnTwo) {	// If the smaller solution is within the interval
			if (t0 < solnOne && solnOne < t1) {
				t = solnOne; 
			}
		}
		else { // If the larger solution is in the interval
			if (t0 < solnTwo && solnTwo < t1) {
				t = solnTwo;
			}
			else {	// If the larger sol'n doesn't fall within bounds, we do need to check the smaller one anyway
				if (t0 < solnOne && solnOne < t1) {
					t = solnOne; 
				}
			}

		}
	}

	if (t < t1) {	// If we have a valid t, calculate the unit normal vector - we're gonna need it!
		//std::cout << "Distance from origin to point of contact = " << t << "\n";
		//std::cout << "Coordinate in 3D space that we found: " << ray.evaluateRay(t).x << " " << ray.evaluateRay(t).y << " " << ray.evaluateRay(t).z << "\n\n";
		n = glm::normalize((ray.evaluateRay(t) - center) / radius);
	}
	return HitReport(m, t, n);
}

glm::vec3 Sphere::getCenter() {
	return center;
}
void Sphere::setCenter(glm::vec3 newCenter) {
	center = newCenter;
}