#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#define _USE_MATH_DEFINES
#include <cmath>

struct PlaneData;
class Sphere {
public:
	Sphere(Vector3 centerPos,float radius);
	~Sphere();
	void Update();
	void Draw(
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color
	);

	bool IsCollision(const PlaneData& plane);

private:
	Vector3 centerPos_;
	float radius_;
	Matrix4x4 worldMatrix_;
};

