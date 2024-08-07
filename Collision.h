#pragma once
#include "Vector3.h"


class AABB;
class Ball;
class Segment;
class Sphere;
class OBB;
class Plane;
class Triangle;


namespace Collision {

	bool Segment2PlaneIsCollision(Segment* segment, Plane* plane);
	bool Segment2TriangleIsCollision(Segment* segment, Triangle* triangle);

	void Ball2PlaneIsCollision(Ball* ball,Plane* plane,float deltaTime);
	bool AABB2SegmentIsCollision(AABB* aabb, Segment* segment);
	bool AABB2SphereIsCollision(AABB* aabb, Sphere* sphere);
	bool OBB2SphereIsCollision(OBB* obb, Sphere* sphere);
};

