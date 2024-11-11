#pragma once
#include "Ray.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/ext/vector_float3.hpp>

class Camera {
protected:
	glm::vec3 worldPos;	// The position of the viewpoint in worldspace; referred to in the textbook as "e"
	int l;	// Positions of the left and right edges of the camera (e.g. if it was 64 pix wide, they would be -32 and 32)
	int r;
	int b;	// Positions of the bottom and top edges of the camera (e.g. if it was 64 pix tall, they would be -32 and 32)
	int t;
	glm::vec3 u;	// The basis vectors which define our camera frame
	glm::vec3 v;
	glm::vec3 w;

	float imgWidth;	// Pixel dimensions of image
	float imgHeight;

public:
	Camera(glm::vec3 e, glm::vec3 d, glm::vec3 upDir, int width, int height, float imgWidth, float imgHeight);	// Constructor takes worldPos, lookAt dir, upDir, + width and height of frame
	virtual Ray generateRay(float iPixel, float jPixel);	// Virtual method for generating a ray; takes pixel values as input
	void setPos(glm::vec3 newPos);
	glm::vec3 getPos();
	void setDir(glm::vec3 newDir, glm::vec3 newUpDir);
	glm::vec3 getDir();

};