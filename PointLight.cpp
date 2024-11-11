#define _USE_MATH_DEFINES

#include "PointLight.h"
#include "Object.h"
#include <iostream>
#include <cmath>

PointLight::PointLight() : Light(){
	worldPos = glm::vec3(0, 0, 0);
}

PointLight::PointLight(glm::vec3 pos, float i) : Light(i, worldPos) {
	worldPos = pos;
}

glm::vec3 PointLight::illuminateRay(Ray ray, HitReport hr, std::vector<Object*> objList) {
	int phongExp = hr.material.phongExp;
	glm::vec3 lightFromPt(0, 0, 0);

	// Setting up all the values we'll need
	glm::vec3 shadingPt = ray.evaluateRay(hr.t);			// Find the point we'll be doing shading at that the raycaster found
	float dist = glm::length(worldPos - shadingPt);			// Find the distance between worldPos and the shadingPt
	glm::vec3 lightDir = (worldPos - shadingPt) / dist;		// Find the light direction
	glm::vec3 objNormal = hr.n;								// Get the normal at the shading pt. from the hit report

	Ray shadowRay = Ray(shadingPt, lightDir);
	HitReport shadowHr = objHit(shadowRay, 0.01f, dist, objList);
	
	// Does it hit anything?
     if (!(shadowHr.t < std::numeric_limits<float>::infinity())) {
		// Calculations for irradiance
		float incidenceAng = (0 > dot(lightDir, objNormal)) ? 0 : dot(lightDir, objNormal);	// Angle that the light ray is hitting the point
		float pointIrradiance = incidenceAng * (intensity) / (float)pow(dist, 2);		// Evaluate the irradiance of the light

		glm::vec3 diffuseLight = (hr.material.diffuseColor / (4.0f * (float)M_PI)) * pointIrradiance;// *hr.material.diffuseCoeff;

		// Calculating mirror configuration
		glm::vec3 mirrorVector = lightDir - 2.0f * (glm::dot(lightDir, objNormal)) * objNormal;
		glm::vec3 viewingVector = ray.getDir() / glm::length(ray.getDir());
		float specularAng = (0 > dot(mirrorVector, viewingVector)) ? 0 : dot(mirrorVector, viewingVector);

		glm::vec3 halfVector = (-viewingVector + lightDir) / glm::length((-viewingVector + lightDir));
		float blinnPhongAng = (0 > dot(halfVector, objNormal)) ? 0 : dot(halfVector, objNormal);

		glm::vec3 specularLight = pointIrradiance * hr.material.specularColor * intensity * (float)pow(blinnPhongAng, phongExp); //hr.material.specularCoeff *
		// L (final) = L (diff) + L (amb) + L (spec)

		lightFromPt = specularLight + diffuseLight; // Ambient is somewhere else suckers!
	}
	else {
		lightFromPt = glm::vec3(0, 0, 0);
	}
	//std::cout << dist << "\n";
	//std::cout << dot(lightDir, objNormal) << "\n";
	//std::cout << "Light direction: " << lightDir.x << " " << lightDir.y << " " << lightDir.z << "\n";
	//std::cout << "Object normal: " << objNormal.x << " " << objNormal.y << " " << objNormal.z << "\n";
	//std::cout << lightFromPt.x << " " << lightFromPt.y << " " << lightFromPt.z << "\n\n";
	//std::cout << "\n";
	return lightFromPt;	
}

const HitReport& PointLight::objHit(Ray ray, float t0, float t1, std::vector<Object*> objList) const {
	HitReport hr;
	for (Object* object : objList) {
		HitReport check = object->objHit(ray, t0, t1);
		//std::cout << abs(check.t) << "\n";
		if (abs(check.t) < t1 && abs(check.t) > t0) {	// If we get a hit
			t1 = abs(check.t); // Shrink our search window so we only update if we find something closer
			hr = check;
			hr.setT(abs(check.t));
			//std::cout << check.t << "\n";
		}
	}
	//std::cout << "\n";
	return hr;
}

