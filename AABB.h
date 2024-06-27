#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <string>

class AABB {
public:

	AABB() = default;
	~AABB() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 min,Vector3 max);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void UpdateImGui(std::string name);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	/// <summary>
	/// 当たり判定
	/// </summary>
	bool IsCollision(const AABB& aabb2);

	void SetColor(int color) { color_ = color; }

private:

	Vector3 min_;
	Vector3 max_;
	int color_;
};

