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

	bool IsCollision(const PlaneData& plane);

	//getter
	Matrix4x4 GetWorldMatrix() { return worldMatrix_; }
	//setter
	void SetRotation(Vector3 rotation) { rotation_ = rotation; }
	void SetScale(Vector3 scale) { scale_ = scale; }
	void SetColor(uint32_t color) { color_ = color; }
	void SetWorldMatrix(Matrix4x4 worldMatrix) { worldMatrix_ = worldMatrix; }
private:
	// 球の中心座標
	Vector3 centerPos_;
	//球の回転
	Vector3 rotation_;
	//球の拡縮
	Vector3 scale_;
	// 球の半径
	float radius_;
	//ワールド行列
	Matrix4x4 worldMatrix_;
	//カラー
	uint32_t color_;
};

