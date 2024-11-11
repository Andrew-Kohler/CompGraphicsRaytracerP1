#include "Triangle.h"

#include <iostream>

Triangle::Triangle() : Object() {
	coord1 = glm::vec3(0, 0, 0);
	coord2 = glm::vec3(1, 0, 0);
	coord3 = glm::vec3(0, 1, 0);
	oneSided = true;
}

Triangle::Triangle(ObjMaterial m, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, bool oneSided) : Object(m) {
	coord1 = p1;
	coord2 = p2;
	coord3 = p3;
	this->oneSided = oneSided;
}

HitReport Triangle::objHit(Ray ray, float t0, float t1) {
	// Set up the data we'll be giving the hit report
	float t = t1;
	ObjMaterial m = ObjMaterial();
	glm::vec3 n(0, 0, 0);

	glm::vec3 edgeOne = coord2 - coord1;
	glm::vec3 edgeTwo = coord3 - coord2;
	glm::vec3 edgeThree = coord1 - coord3;
	glm::vec3 tempNormal = glm::normalize(cross(edgeOne, edgeTwo));

	if (dot(tempNormal, ray.getDir()) != 0) { // We don't want to go dividing by 0, now, do we
		float d = dot(tempNormal, coord1);
		float tExp = (-dot(tempNormal, ray.getOrigin()) + d) / dot(tempNormal, ray.getDir());
		if (tExp >= 0) {	// If t is negative, we are trying to evaluate a triangle behind the camera, so we stop here
			glm::vec3 p = ray.evaluateRay(tExp);

			glm::vec3 check1 = cross((edgeOne), (p - coord1));
			glm::vec3 check2 = cross((edgeTwo), (p - coord2));
			glm::vec3 check3 = cross((edgeThree), (p - coord3));
			if (dot(check1, tempNormal) >= 0 && dot(check2, tempNormal) >= 0 && dot(check3, tempNormal) >= 0) {
				// We have now confirmed p is a valid point within the triangle.
				// However, for my own sanity, we're doing backface culling.
				if ((dot(tempNormal, ray.getDir()) <= 0 && oneSided) || !oneSided) {
					m = material;
					t = tExp;
					n = tempNormal;
				}
			}
		}
	}
	
	return HitReport(m, t, n);

	}

	// Let these comments stand as a monument to my hubris.

//glm::vec3 edgeOne = coord2 - coord1;
	//glm::vec3 edgeTwo = coord3 - coord2;
	//glm::vec3 tempNormal = cross(edgeOne, edgeTwo);

	//float parallelCheck = dot(ray.getDir(), tempNormal);
	//if (!parallelCheck == 0) { // If the triangle and ray are NOT parallel
	//	float temp = (dot(tempNormal, coord1) - dot(tempNormal, ray.getOrigin())) / parallelCheck;
	//	glm::vec3 point = ray.evaluateRay(temp);

	//	glm::vec3 check1 = cross((coord2 - coord1), (point - coord1));
	//	glm::vec3 check2 = cross((coord3 - coord2), (point - coord2));
	//	glm::vec3 check3 = cross((coord1 - coord3), (point - coord3));
	//	if (dot(check1, tempNormal) >= 0) {
	//		if (dot(check2, tempNormal) >= 0) {
	//			if (dot(check3, tempNormal) >= 0) {
	//				m = material;
	//				t = temp;


	//				//			glm::vec3 normalOne = glm::cross((twoMOne), (threeMOne));
	//				//			glm::vec3 normalTwo = glm::cross((coord1-coord2), (coord3-coord2));
	//				//			glm::vec3 normalThree = glm::cross((coord1-coord3), (coord2-coord3));

	//				//			float denom = dot(cross(twoMOne, threeMOne), tempNormal);
	//				//			float alpha = dot(cross(threeMTwo, pointMinusTwo), tempNormal) / denom;
	//				//			float beta = dot(cross(oneMThree, pointMinusThree), tempNormal) / denom;
	//				//			float chi = dot(cross(twoMOne, pointMinusOne), tempNormal) / denom;
	//				//			//std::cout << alpha << " " << beta << " " << chi << "\n";

	//				//			glm::vec3 finalNumerator = alpha * tempNormal + beta * tempNormal + chi * tempNormal;
	//				//			glm::vec3 finalNormal = finalNumerator / glm::length(finalNumerator);

	//				n = tempNormal;
	//			}
	//		}
	//	}
	//}
	

	//glm::vec3 twoMOne(coord2 - coord1);
	//glm::vec3 threeMTwo(coord3 - coord2);
	//glm::vec3 threeMOne(coord3 - coord1);
	//glm::vec3 oneMThree(coord1 - coord3);

	////We'll be using the slide implementation, doing 3 different checks, rather than the Cramer Chaos of the textbook
	//glm::vec3 tempNormal = glm::cross((twoMOne), (threeMOne)); // Note - we may need to examine this later
	////std::cout << tempNormal.x << " " << tempNormal.y << " " << tempNormal.z << "\n";
	//float temp = (dot(tempNormal, coord1) - dot(tempNormal, ray.getOrigin())) / dot(ray.getDir(), tempNormal);
	////std::cout << (coord1 - ray.getOrigin()).x << " " << (coord1 - ray.getOrigin()).y << " " << (coord1 - ray.getOrigin()).z << "\n";
	//glm::vec3 point = ray.evaluateRay(temp);
	////std::cout << point.x << " " << point.y << " " << point.z << "\n";

	//glm::vec3 pointMinusTwo(point - coord2);
	//glm::vec3 pointMinusThree(point - coord3);
	//glm::vec3 pointMinusOne(point - coord1);
	// 

	//// Check that the ray is inside the edge vectors of the triangle
	//glm::vec3 check1 = cross((coord2 - coord1), (point - coord1));
	//glm::vec3 check2 = cross((coord3 - coord2), (point - coord2));
	//glm::vec3 check3 = cross((coord1 - coord3), (point - coord3));
	//if (dot(check1, tempNormal) >= 0) {
	//	if (dot(check2, tempNormal) >= 0) {
	//		if (dot(check3, tempNormal) >= 0){
	//			m = material;
	//			t = temp;
	//			

	//			glm::vec3 normalOne = glm::cross((twoMOne), (threeMOne));
	//			glm::vec3 normalTwo = glm::cross((coord1-coord2), (coord3-coord2));
	//			glm::vec3 normalThree = glm::cross((coord1-coord3), (coord2-coord3));

	//			float denom = dot(cross(twoMOne, threeMOne), tempNormal);
	//			float alpha = dot(cross(threeMTwo, pointMinusTwo), tempNormal) / denom;
	//			float beta = dot(cross(oneMThree, pointMinusThree), tempNormal) / denom;
	//			float chi = dot(cross(twoMOne, pointMinusOne), tempNormal) / denom;
	//			//std::cout << alpha << " " << beta << " " << chi << "\n";

	//			glm::vec3 finalNumerator = alpha * tempNormal + beta * tempNormal + chi * tempNormal;
	//			glm::vec3 finalNormal = finalNumerator / glm::length(finalNumerator);

	//			n = finalNormal;
	//		}
	//	}
	//}

	
