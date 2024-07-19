#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
struct Pendulum {

	Vector3 anchorPos; // 原点
	float length; // 振り子の長さ
	float angle; // 角度
	float anglerVelocity; // 角速度
	float angleAcceleration; // 角加速度
	Matrix4x4 worldMatrix; // ワールド行列

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& diff);
};