#include "Scene.h"

#include<vector>
#include <iostream>

Scene::Scene(std::vector<Object*> ol, std::vector<Light*> ll) {
	objList = ol;
	lightList = ll;
	bgColor = glm::vec3(0, 0, 50);
}

const HitReport& Scene::objHit(Ray ray, float t0, float t1) const {
	HitReport hr;
	for (Object* object : objList) {
		HitReport check = object->objHit(ray, t0, t1);
		if (check.t < t1 && check.t > t0) {	// If we get a hit
			t1 = check.t; // Shrink our search window so we only update if we find something closer
			hr = check;
		}
	}
	
	return hr;
}

const glm::vec3& Scene::lightColor(Ray ray, float t0, float t1, int bounceCount) const {
	HitReport hr = objHit(ray, t0, t1);
	
	if (hr.t < std::numeric_limits<float>::infinity()) {	// If we hit something...
		glm::vec3 finalColor(0, 0, 0);
		
		for (Light* light : lightList) {
			// Get the position of the light
			//glm::vec3 shadingPt = ray.evaluateRay(hr.t);			// Find the point we'll be doing shading at that the raycaster found
			//float dist = glm::length(light->worldPos - shadingPt);			// Find the distance between worldPos and the shadingPt
			//glm::vec3 lightDir = (light->worldPos - shadingPt) / dist;		// Find the light direction

		    finalColor = finalColor + light->illuminateRay(ray, hr, objList);
			if (bounceCount > 0 && hr.material.glazed) {
				Ray newRay = Ray(ray.evaluateRay(hr.t), hr.n);
				finalColor = finalColor + (hr.material.reflectiveness)*lightColor(newRay, .01, t1, bounceCount - 1);
			}
			
		}
		return finalColor;
	}
	else {
		return bgColor;
	}
}
