#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct Pendulum {

	Vector3 anchorPos;
	float length;
	float angle;
	float anglerVelocity;
	float anglerAcceleration;
	Matrix4x4 worldMatrix;

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& diff);
};