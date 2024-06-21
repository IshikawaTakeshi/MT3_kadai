#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <cstdint>

class Plane;
class Segment {
public:	

	Segment() = default;
	~Segment() = default;

	void Initialize();
	void Update(Plane* plane);
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	//線分と平面の当たり判定
	bool IsCollision(Plane& plane);

	Vector3 GetOrigin() { return origin_; }
	Vector3 GetDiff() { return diff_; }
	
private:

	Vector3 origin_; //原点
	Vector3 diff_; //終点との差分ベクトル
	Vector3 rotate_; //回転
	Matrix4x4 worldMatrix_; //行列
	uint32_t color_; //カラー
};

