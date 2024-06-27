#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

class Segment;
class Triangle {
public:

	Triangle() = default;
	~Triangle() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,Segment* seg);

	//ゲッター
	Vector3 GetVertices(int index) { return vertices_[index]; }
	Vector3 GetNormal() { return normal_; }
private:

	//ワールド行列
	Matrix4x4 worldMatrix_;

	//頂点
	Vector3 vertices_[3];
	//中心点
	Vector3 centerPos_;
	//法線
	Vector3 normal_;
	//移動距離
	float distance_;
};