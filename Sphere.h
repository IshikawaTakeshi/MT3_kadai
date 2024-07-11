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

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	/// <summary>
	/// 平面との当たり判定
	/// </summary>
	/// <param name="plane"></param>
	/// <returns></returns>
	bool IsCollision(const PlaneData& plane);

	//getter
	Matrix4x4 GetWorldMatrix() { return worldMatrix_; }
	Vector3 GetTransform() { return centerPos_; }
	Vector3 GetRotation() { return rotation_; }
	float GetRadius() { return radius_; }

	//setter
	void SetTransform(Vector3 transform) { centerPos_ = transform; }
	void SetRotation(Vector3 rotation) { rotation_ = rotation; }
	void SetScale(Vector3 scale) { scale_ = scale; }
	void SetColor(uint32_t color) { color_ = color; }
	void SetRadius(float radius) { radius_ = radius; }
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

