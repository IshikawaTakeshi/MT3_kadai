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
	void Update(const PlaneData& plane);
	void Draw(
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix
	);

	bool IsCollision(const PlaneData& plane);
	void SetColor(uint32_t color) { color_ = color; }

private:
	Vector3 centerPos_;
	float radius_;
	Matrix4x4 worldMatrix_;
	uint32_t color_;
};

