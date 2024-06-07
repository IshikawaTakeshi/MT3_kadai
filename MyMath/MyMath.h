﻿#pragma once
#include <Vector3.h>
#include "Lines.h"

struct PlaneData;
class MyMath {
public:
	//加算
	static Vector3 Add(const Vector3& v1, const Vector3& v2);

	//減算
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	//乗算
	static Vector3 Multiply(float scalar, const Vector3& v);

	//乗算
	static Vector3 Multiply(const Vector3& v1, const Vector3& v2);

	//商算
	static Vector3 Divide(float scalar, const Vector3& v);

	//内積
	static float Dot(const Vector3& v1, const Vector3& v2);

	//クロス積
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	//長さ(ノルム)
	static float Length(const Vector3& v);

	//平面と点の距離
	static float Distance(const Vector3& sphereCenter, const PlaneData& plane);

	//正規化
	static Vector3 Normalize(const Vector3& v);

	//数値表示
	static void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

public:

	//ベクトル射影
	static Vector3 Project(const Vector3& v1, const Vector3& v2);

	//最近接点
	static Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

	//垂直なベクトルを求める関数
	static Vector3 Perpendicular(const Vector3& vector);

public:
	
};
