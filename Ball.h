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



private:

	//フレーム間の経過時間(デルタタイム)
	static inline const float kDeltaTime_ = 1.0f / 60.0f;
	//重力加速度
	static inline const Vector3 kGravity_ = { 0.0f,-9.8f,0.0f };

	//速度
	Vector3 velocity_; 
	//加速度
	Vector3 acceleration_; 
	//質量
	float mass_; 



};