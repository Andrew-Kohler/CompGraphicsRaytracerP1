#pragma once
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/ext/vector_float3.hpp>

class ObjMaterial {
public:
	float diffuseCoeff;		// kd, the diffuse coefficient; how matte an object is
	float ambientCoeff;		// ka, the ambient coefficient; how strongly the object is affected by ambient lighting
	float specularCoeff;	// ks, the specular coefficient

	glm::vec3 diffuseColor;	// The color of the object when interacting with diffuse scenarios (the base color that we want brightened)
	glm::vec3 specularColor;	// The color of the object when interacting with specular scenarios (the color of the 'shine')
	glm::vec3 ambientColor;	// The color of the object when interacting with ambient scenarios (also the base color normally)
	glm::vec3 reflectiveness;	// How reflective the object is

	bool glazed;		// Whether or not this surface is glazed
	int phongExp;

	ObjMaterial();	// Constructors
	ObjMaterial(float kd, float ka, float ks, glm::vec3 diffCol, glm::vec3 specCol, glm::vec3 ambColor, bool mirror, glm::vec3 reflective, int phong);
	//glm::vec3 evaluateColor(glm::vec3 lightDir, glm::vec3 viewDir, glm::vec3 surfaceNormal);	// Evaluates the correct color of the pixel based on given parameters
};