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
	Matrix4x4 GetViewMatrix() { return viewMatrix_; };
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
};

