#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

class Camera {
public:
	Camera();
	~Camera();
	void Update();
	void Draw();

	//getter
	Matrix4x4 GetViewProjectionMatrix() { return viewProjectionMatrix_; };
	Matrix4x4 GetViewportMatrix() { return viewportMatrix_; }
	const Vector3& GetTranslate() { return cameraTranslate_; };
	const Vector3& GetRotate() { return cameraRotate_; };

	//setter
	
private:

	//カメラの移動
	Vector3 cameraTranslate_;

	//カメラの回転
	Vector3 cameraRotate_;
	
	//world座標
	Matrix4x4 worldMatrix_;

	//ビュー行列
	Matrix4x4 viewMatrix_;

	//射影行列
	Matrix4x4 projectionMatrix_;
	Matrix4x4 viewProjectionMatrix_;
	//ビューポート変換行列
	Matrix4x4 viewportMatrix_;
	//法線
	//Vector3 normal_;
	//ワールド原点との距離
	//float distance_;
};

