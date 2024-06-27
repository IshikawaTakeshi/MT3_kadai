﻿#pragma once
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
	void Draw(const Matrix4x4& viewProjection,const Matrix4x4& viewport);

	PlaneData GetPlaneData() { return plane_; }

private:

	//中心点
	Vector3 centerPos_;
	//平面
	PlaneData plane_;
	//カラー
	uint32_t color_;
	//ワールド座標
	Matrix4x4 worldMatrix_;
};
