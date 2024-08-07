#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
class OBB {
public:

	//////////////////////////////////////////////////////////////////
	///		public 関数
	//////////////////////////////////////////////////////////////////


	/// <summary>
	/// コンストラクタ
	/// </summary>
	OBB() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OBB();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 centerPos,Vector3 orientations[3],Vector3 size);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	void UpdateImGui();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

public:
	//////////////////////////////////////////////////////////////////
	///		getter
	//////////////////////////////////////////////////////////////////

	/// <summary>
	/// 中心点の取得
	///	</summary>
	const Vector3& GetCenterPos() const { return centerPos_; }

	/// <summary>
	/// 座標軸の取得
	/// </summary>
	const Vector3& GetOrientation(int index) const { return orientation_[index]; }

	/// <summary>
	/// サイズの取得
	/// </summary>
	const Vector3& GetSize() const { return size_; }

	const Matrix4x4& GetWorldMatrix() const { return worldMatrix_; }

	const Matrix4x4& GetRotationMatrix() const { return rotationMatrix_; }

public:

	//////////////////////////////////////////////////////////////////
	///		setter
	//////////////////////////////////////////////////////////////////

	void SetCenterPos(Vector3 centerPos) { centerPos_ = centerPos; }

	void SetOrientation(int index, Vector3 orientation) { orientation_[index] = orientation; }

	void SetSize(Vector3 size) { size_ = size; }

	void SetWorldMatrix(Matrix4x4 worldMatrix) { worldMatrix_ = worldMatrix; }

	void SetRotationMatrix(Matrix4x4 rotationMatrix) { rotationMatrix_ = rotationMatrix; }

private:

	//////////////////////////////////////////////////////////////////
	///		private 変数
	//////////////////////////////////////////////////////////////////

	//中心点
	Vector3 centerPos_;
	//座標軸。正規化・直交必須
	Vector3 orientation_[3];
	//座標軸方向の長さの半分
	Vector3 size_;
	//回転
	Vector3 rotation_;
	//ワールド行列
	Matrix4x4 worldMatrix_;
	//回転行列
	Matrix4x4 rotationMatrix_;

	//カラー
	int color_;

};

