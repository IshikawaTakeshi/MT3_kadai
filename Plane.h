#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <cstdint>



struct PlaneData {
	Vector3 normal; //法線
	float distance; //距離
};

class Plane {
public:

	Plane();
	~Plane();

	//更新処理
	void Update();
	//描画処理
	void Draw(const PlaneData& plane,const Matrix4x4& viewPrjection,
		const Matrix4x4& viewport);

private:

	Vector3 centerPos_;
	//平面
	PlaneData plane_;
	//カラー
	uint32_t color_;
	//ワールド座標
	Matrix4x4 worldMatrix_;
};
