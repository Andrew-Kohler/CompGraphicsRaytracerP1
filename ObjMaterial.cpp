#include "ObjMaterial.h"

ObjMaterial::ObjMaterial() {
	diffuseCoeff = .2;
	ambientCoeff = .2;
	specularCoeff = .6;

	diffuseColor = glm::vec3(255, 0, 0);
	specularColor = glm::vec3(.2, .2, .2);
	ambientColor = diffuseColor;

	reflectiveness = glm::vec3(.2, .2, .2);
	glazed = false;

	phongExp = 100;
}

ObjMaterial::ObjMaterial(float kd, float ka, float ks, glm::vec3 diffCol, glm::vec3 specCol, glm::vec3 ambColor, bool mirror, glm::vec3 reflective, int phong) {
	diffuseCoeff = kd;
	ambientCoeff = ka;
	specularCoeff = ks;

	diffuseColor = diffCol;
	specularColor = specCol;
	ambientColor = ambColor;

	reflectiveness = reflective;
	glazed = mirror;
	phongExp = phong;
}

//glm::vec3 ObjMaterial::evaluateColor(glm::vec3 lightDir, glm::vec3 viewDir, glm::vec3 surfaceNormal) {
//
//}