#pragma once
#include "Sphere.h"

struct Spring;
class Ball : public Sphere {
public:

	Ball();
	~Ball();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="centerPos"></param>
	/// <param name="radius"></param>
	void Initialize(Vector3 centerPos, float radius);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const Spring& spring);

	void UpdateImGui();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) override;

public:

	/// <summary>
	/// 速度の取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetVelocity() { return velocity_; }

	/// <summary>
	/// 加速度の取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetAcceleration() { return acceleration_; }

	/// <summary>
	/// 質量の取得
	/// </summary>
	/// <returns></returns>
	float GetMass() { return mass_; }

public:

	/// <summary>
	/// 速度の設定
	/// </summary>
	/// <param name="velocity"></param>
	void SetVelocity(Vector3 velocity) { velocity_ = velocity; }

	/// <summary>
	/// 加速度の設定
	/// </summary>
	/// <param name="acceleration"></param>
	void SetAcceleration(Vector3 acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// 質量の設定
	/// </summary>
	/// <param name="mass"></param>
	void SetMass(float mass) { mass_ = mass; }

private:

	//フレーム間の経過時間(デルタタイム)
	static inline const float kDeltaTime_ = 1.0f / 60.0f;

	//速度
	Vector3 velocity_; 
	//加速度
	Vector3 acceleration_; 
	//質量
	float mass_; 



};