#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/ext/vector_float3.hpp>

class Ray {
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray(glm::vec3 o, glm::vec3 dir);	// The constructor for a ray
	glm::vec3 evaluateRay(float t);		// Function for evaluating a ray and returning the relevant parametric line
	glm::vec3 getOrigin();
	glm::vec3 getDir();
	// t is the distance we advance along the ray

};