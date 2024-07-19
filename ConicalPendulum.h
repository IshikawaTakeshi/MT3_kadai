#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct ConicalPendulum {

	Vector3 anchorPos; //錘の位置
	float length; //糸の長さ
	float harfApexAngle; //円錐の半頂角
	float angle; //角度
	float anglerVelocity; //角速度
	Matrix4x4 worldMatrix; //ワールド行列
	float radius; //円錐の半径
	float height; //円錐の高さ

	//更新処理
	void Update(float deltaTime);
	//描画処理
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& diff);
};