#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Sphere {
public:
	Sphere();
	~Sphere();
	void Update();
	void Draw(
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color
	);
private:
	Vector3 centerPos_;
	float radius_;
	Matrix4x4 worldMatrix_;
};

