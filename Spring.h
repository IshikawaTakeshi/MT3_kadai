#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct Spring {

	Vector3 anchorPos; //アンカー。バネの固定点
	float naturalLength; //自然長
	float stiffness; //ばね定数
	float dampingCoefficient; //減衰係数
	Matrix4x4 worldMatrix; //ワールド座標

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,const Vector3& diff);
};