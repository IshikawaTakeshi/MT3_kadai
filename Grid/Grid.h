#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>

class Grid {
public:
	Grid();
	~Grid();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix,const Matrix4x4& viewportMatrix);

	//getter
	Matrix4x4 GetWorldMatrix() { return worldMatrix_; };
private:

	//原点
	Vector3 pos_;

	//グリッド線の回転
	Vector3 rotate_;

	//ワールド座標
	Matrix4x4 worldMatrix_;

	
};

