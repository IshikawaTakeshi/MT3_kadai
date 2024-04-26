#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Sphere {
public:
	Sphere(Vector3 centerPos,float radius);
	~Sphere();
	void Update(int id);
	void Draw(
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix
	);

	static bool IsCollision(const Sphere& s1, const Sphere& s2);
	
	//ゲッター
	Vector3 GetPos() const { return centerPos_; }
	float GetRadius() const { return radius_; }

	//セッター
	void SetColor(uint32_t color) { color_ = color; }

private:
	Vector3 centerPos_;
	float radius_;
	uint32_t color_;
	Matrix4x4 worldMatrix_;
};

