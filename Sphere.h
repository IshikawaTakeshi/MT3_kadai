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
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix
	);

	/// <summary>
	/// 平面との当たり判定
	/// </summary>
	/// <param name="plane"></param>
	/// <returns></returns>
	bool IsCollision(const PlaneData& plane);

	//getter
	Matrix4x4 GetWorldMatrix() { return worldMatrix_; }
	Vector3 GetTransform() { return centerPos_; }
	float GetRadius() { return radius_; }

	//setter
	void SetTransform(Vector3 transform) { centerPos_ = transform; }
	void SetColor(uint32_t color) { color_ = color; }
	void SetRadius(float radius) { radius_ = radius; }
	void SetWorldMatrix(Matrix4x4 worldMatrix) { worldMatrix_ = worldMatrix; }

private:
	Vector3 centerPos_;
	float radius_;
	Matrix4x4 worldMatrix_;
	uint32_t color_;
};

