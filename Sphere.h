#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#define _USE_MATH_DEFINES
#include <cmath>

struct PlaneData;
class Sphere {
public:
	/////////////////////////////////////////////////////////////////////////
	///		public 関数
	/////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="centerPos"></param>
	/// <param name="radius"></param>
	Sphere();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sphere();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="centerPos"></param>
	/// <param name="radius"></param>
	virtual void Initialize(Vector3 centerPos, float radius);

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	void UpdateImGui();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	virtual void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	/// <summary>
	/// 平面との当たり判定
	/// </summary>
	/// <param name="plane"></param>
	/// <returns></returns>
	bool IsCollision(const PlaneData& plane);

public:
	/////////////////////////////////////////////////////////////////////////
	///		getter
	/////////////////////////////////////////////////////////////////////////

	virtual const Matrix4x4& GetWorldMatrix() { return worldMatrix_; }
	virtual const Vector3& GetCenterPos() { return centerPos_; }
	virtual const float& GetRadius() { return radius_; }

public:
	/////////////////////////////////////////////////////////////////////////
	//		setter
	/////////////////////////////////////////////////////////////////////////

	void SetCenterPos(Vector3 transform) { centerPos_ = transform; }
	void SetColor(uint32_t color) { color_ = color; }
	void SetRadius(float radius) { radius_ = radius; }
	void SetWorldMatrix(Matrix4x4 worldMatrix) { worldMatrix_ = worldMatrix; }

protected:
	/////////////////////////////////////////////////////////////////////////
	///		protected 変数
	/////////////////////////////////////////////////////////////////////////

	//中心座標
	Vector3 centerPos_;
	//半径
	float radius_;
	//ワールド行列
	Matrix4x4 worldMatrix_;
	//カラー
	uint32_t color_;
};

