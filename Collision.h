#pragma once
#include "Vector3.h"

class Segment;
class Plane;
class Triangle;
class Ball;
class Plane;
namespace Collision {

	bool Segment2PlaneIsCollision(Segment* segment, Plane* plane);
	bool Segment2TriangleIsCollision(Segment* segment, Triangle* triangle);

	bool Ball2PlaneIsCollision(Ball* ball,Plane* plane,float deltaTime);
};

